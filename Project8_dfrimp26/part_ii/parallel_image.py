"""
parallel_image.py

Reads a P6 PPM image, applies a pixel-wise color operator, and compares
serial processing with multiprocessing versions using 1, 2, and 4 workers.

Usage examples:
    python3 parallel_image.py input.ppm --out output.ppm --threads 4 --iterations 25
    python3 parallel_image.py input.ppm --benchmark --iterations 25
"""

from __future__ import annotations

import argparse
import csv
import multiprocessing as mp
import os
import time
from dataclasses import dataclass
from typing import Iterable, List, Tuple

from pyppmIO import PPM


@dataclass
class BenchmarkResult:
    version: str
    threads: int
    seconds: float
    speedup: float


def pixel_operator(r: int, g: int, b: int) -> Tuple[int, int, int]:
    """Pixel-wise operator: invert colors and slightly boost contrast.

    This is intentionally arithmetic-heavy enough to make parallel timing visible
    when repeated many times. The final values are clamped into [0, 255].
    """
    nr = 255 - r
    ng = 255 - g
    nb = 255 - b

    # mild contrast adjustment around midpoint 128
    nr = int((nr - 128) * 1.15 + 128)
    ng = int((ng - 128) * 1.15 + 128)
    nb = int((nb - 128) * 1.15 + 128)

    return max(0, min(255, nr)), max(0, min(255, ng)), max(0, min(255, nb))


def process_chunk(chunk: bytes, iterations: int) -> bytes:
    """Apply the pixel operator to a byte chunk containing RGB triples."""
    data = bytearray(chunk)

    for _ in range(iterations):
        for i in range(0, len(data), 3):
            data[i], data[i + 1], data[i + 2] = pixel_operator(
                data[i], data[i + 1], data[i + 2]
            )

    return bytes(data)


def split_rgb_data(data: bytearray, threads: int) -> List[bytes]:
    """Split image bytes into nearly equal pixel-aligned chunks."""
    total_pixels = len(data) // 3
    chunks: List[bytes] = []

    for tid in range(threads):
        start_pixel = tid * total_pixels // threads
        end_pixel = (tid + 1) * total_pixels // threads
        start_byte = start_pixel * 3
        end_byte = end_pixel * 3
        chunks.append(bytes(data[start_byte:end_byte]))

    return chunks


def apply_serial(data: bytearray, iterations: int) -> bytearray:
    return bytearray(process_chunk(bytes(data), iterations))


def apply_parallel(data: bytearray, threads: int, iterations: int) -> bytearray:
    chunks = split_rgb_data(data, threads)
    with mp.Pool(processes=threads) as pool:
        processed = pool.starmap(process_chunk, [(chunk, iterations) for chunk in chunks])
    return bytearray().join(processed)


def write_output_like(ppm: PPM, new_data: bytearray, output_filename: str) -> None:
    out = PPM()
    out.rows = ppm.rows
    out.cols = ppm.cols
    out.colors = ppm.colors
    out.data = new_data
    out.write(output_filename)


def time_function(func, *args) -> Tuple[bytearray, float]:
    start = time.perf_counter()
    result = func(*args)
    end = time.perf_counter()
    return result, end - start


def run_benchmark(ppm: PPM, iterations: int, output_csv: str) -> List[BenchmarkResult]:
    print(f"Benchmarking with {iterations} repeated passes per image...")

    serial_data, serial_time = time_function(apply_serial, ppm.data, iterations)
    results = [BenchmarkResult("serial", 0, serial_time, 1.0)]
    print(f"serial: {serial_time:.4f} seconds")

    for threads in (1, 2, 4):
        par_data, par_time = time_function(apply_parallel, ppm.data, threads, iterations)

        # Correctness check: parallel output must equal serial output.
        if par_data != serial_data:
            raise RuntimeError(f"Parallel result with {threads} threads differs from serial output")

        speedup = serial_time / par_time if par_time > 0 else 0.0
        results.append(BenchmarkResult("parallel", threads, par_time, speedup))
        print(f"parallel {threads} thread(s): {par_time:.4f} seconds, speedup {speedup:.2f}x")

    with open(output_csv, "w", newline="") as fp:
        writer = csv.writer(fp)
        writer.writerow(["version", "threads", "seconds", "speedup"])
        for r in results:
            writer.writerow([r.version, r.threads, f"{r.seconds:.6f}", f"{r.speedup:.4f}"])

    return results


def plot_results(csv_filename: str, output_png: str) -> None:
    """Create a bar chart from the benchmark CSV."""
    import matplotlib.pyplot as plt

    labels = []
    times = []

    with open(csv_filename, newline="") as fp:
        reader = csv.DictReader(fp)
        for row in reader:
            if row["version"] == "serial":
                labels.append("serial")
            else:
                labels.append(f"{row['threads']} thread")
            times.append(float(row["seconds"]))

    plt.figure(figsize=(7, 4.5))
    plt.bar(labels, times)
    plt.ylabel("Computation time (seconds)")
    plt.title("Serial vs. parallel pixel-wise image processing")
    plt.tight_layout()
    plt.savefig(output_png, dpi=160)
    plt.close()


def main() -> None:
    parser = argparse.ArgumentParser(description="Parallel PPM pixel-wise image processor")
    parser.add_argument("input", help="input P6 PPM image")
    parser.add_argument("--out", default="output.ppm", help="output PPM filename")
    parser.add_argument("--threads", type=int, choices=[1, 2, 4], default=4,
                        help="number of worker processes for normal parallel run")
    parser.add_argument("--iterations", type=int, default=20,
                        help="number of repeated processing passes for timing")
    parser.add_argument("--benchmark", action="store_true",
                        help="compare serial, 1-thread, 2-thread, and 4-thread versions")
    parser.add_argument("--csv", default="benchmark_results.csv", help="benchmark CSV output")
    parser.add_argument("--graph", default="benchmark_graph.png", help="benchmark graph output")
    args = parser.parse_args()

    ppm = PPM(args.input)

    if args.benchmark:
        run_benchmark(ppm, args.iterations, args.csv)
        plot_results(args.csv, args.graph)
        print(f"Wrote {args.csv} and {args.graph}")
    else:
        new_data, seconds = time_function(apply_parallel, ppm.data, args.threads, args.iterations)
        write_output_like(ppm, new_data, args.out)
        print(f"Wrote {args.out}")
        print(f"Parallel processing with {args.threads} thread(s) took {seconds:.4f} seconds")


if __name__ == "__main__":
    main()
