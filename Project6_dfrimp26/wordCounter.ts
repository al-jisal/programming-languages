/**
 * File: wordCounter.ts -- shows an implementation of a word counter using typescript's map datastructure
 * 
 * Author: Desmond Frimpong
 * Project: 06
 * Date: April 23, 2026
*/

import { readFileSync } from "fs";

function normalizeWords(text: string): string[] {
  return text
    .toLowerCase()
    .replace(/[^a-z0-9\s]/g, " ")
    .split(/\s+/)
    .filter((word) => word.length > 0);
}

function countWords(words: string[]): Map<string, number> {
  const counts = new Map<string, number>();

  for (const word of words) {
    counts.set(word, (counts.get(word) ?? 0) + 1);
  }

  return counts;
}

function printTopWords(counts: Map<string, number>, limit = 20): void {
  const sorted = Array.from(counts.entries()).sort((a, b) => {
    const frequencyDifference = b[1] - a[1];
    if (frequencyDifference !== 0) return frequencyDifference;
    return a[0].localeCompare(b[0]);
  });

  for (const [word, count] of sorted.slice(0, limit)) {
    console.log(`${word.padStart(10)} ${count}`);
  }
}

function main(): void {
  const filename = process.argv[2];

  if (!filename) {
    console.error("Usage: ts-node wordCounter.ts <filename>");
    process.exit(1);
  }

  try {
    const fileContents = readFileSync(filename, "utf8");
    const words = normalizeWords(fileContents);
    const counts = countWords(words);
    printTopWords(counts, 20);
  } catch (error: unknown) {
    if (error instanceof Error) {
      console.error(`Error: ${error.message}`);
    } else {
      console.error("An unknown error occurred.");
    }
    process.exit(1);
  }
}

main();
