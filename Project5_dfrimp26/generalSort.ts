/**
 * File: generalSort.ts -- A generic merge sort implementation. It does not use
 *                         JavaScript/TypeScript's built-in Array.sort().
 *                         
 * Author: Desmond Frimpong
 * Project: 05
 * Date: April 9, 2026
*/

export type SortCompareFunction<T> = (a: T, b: T) => number;

export function mergeSort<T>(items: T[], compare: SortCompareFunction<T>): T[] {
  if (items.length <= 1) return [...items];

  const middle = Math.floor(items.length / 2);
  const left = mergeSort(items.slice(0, middle), compare);
  const right = mergeSort(items.slice(middle), compare);

  return merge(left, right, compare);
}

function merge<T>(left: T[], right: T[], compare: SortCompareFunction<T>): T[] {
  const result: T[] = [];
  let i = 0;
  let j = 0;

  while (i < left.length && j < right.length) {
    if (compare(left[i], right[j]) <= 0) {
      result.push(left[i]);
      i += 1;
    } else {
      result.push(right[j]);
      j += 1;
    }
  }

  while (i < left.length) {
    result.push(left[i]);
    i += 1;
  }

  while (j < right.length) {
    result.push(right[j]);
    j += 1;
  }

  return result;
}
