import { performance, PerformanceObserver } from "node:perf_hooks";

type Result = {
  iteration: number;
  timeMs: number;
};

const results: Result[] = [];
const gcEvents: number[] = [];

const observer = new PerformanceObserver((list) => {
  for (const entry of list.getEntries()) {
    if (entry.entryType === "gc") {
      gcEvents.push(entry.duration);
    }
  }
});

observer.observe({ entryTypes: ["gc"], buffered: true });

function createAndDeleteMemory(): void {
  const data: object[] = [];

  for (let i = 0; i < 100000; i++) {
    data.push({
      id: i,
      name: `Object ${i}`,
      values: [i, i + 1, i + 2, i + 3]
    });
  }

  // When this function ends, "data" is no longer reachable.
  // The garbage collector can reclaim this memory later.
}

function average(values: number[]): number {
  return values.reduce((sum, value) => sum + value, 0) / values.length;
}

function standardDeviation(values: number[], avg: number): number {
  const variance =
    values.reduce((sum, value) => sum + Math.pow(value - avg, 2), 0) /
    values.length;

  return Math.sqrt(variance);
}

for (let i = 1; i <= 100; i++) {
  const start = performance.now();

  createAndDeleteMemory();

  const end = performance.now();
  const duration = end - start;

  results.push({
    iteration: i,
    timeMs: duration
  });
}

const times = results.map((result) => result.timeMs);
const avg = average(times);
const std = standardDeviation(times, avg);
const threshold = avg + std * 2;

console.log("Average time:", avg.toFixed(3), "ms");
console.log("Standard deviation:", std.toFixed(3), "ms");
console.log("Possible GC threshold:", threshold.toFixed(3), "ms");
console.log();

console.log("Slow calls that may indicate garbage collection:");

for (const result of results) {
  if (result.timeMs > threshold) {
    console.log(
      `Iteration ${result.iteration}: ${result.timeMs.toFixed(3)} ms`
    );
  }
}

console.log();
console.log("GC events observed by Node:", gcEvents.length);

for (let i = 0; i < gcEvents.length; i++) {
  console.log(`GC event ${i + 1}: ${gcEvents[i].toFixed(3)} ms`);
}