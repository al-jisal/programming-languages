/**
 * File: my_linkedlist.ts -- A generic doubly linked list implementation in TypeScript. This mirrors 
 *                           the C API from my_linkedlist.h, but uses TypeScript generics instead of void * pointers.
 * 
 * Author: Desmond Frimpong
 * Project: 05
 * Date: April 9, 2026
*/

export type CompareFunction<T> = (target: T, data: T) => number;
export type MapFunction<T> = (data: T) => void;

class Node<T> {
  data: T;
  next: Node<T> | null;
  prev: Node<T> | null;

  constructor(data: T) {
    this.data = data;
    this.next = null;
    this.prev = null;
  }
}

export class LinkedList<T> {
  private head: Node<T> | null;
  private tail: Node<T> | null;
  private length: number;

  constructor() {
    this.head = null;
    this.tail = null;
    this.length = 0;
  }

  /** Same idea as ll_push: insert at the front of the list. */
  push(data: T): void {
    const node = new Node<T>(data);
    node.next = this.head;

    if (this.head !== null) {
      this.head.prev = node;
    } else {
      this.tail = node;
    }

    this.head = node;
    this.length += 1;
  }

  /** Same idea as ll_pop: remove and return the item at the front. */
  pop(): T | undefined {
    if (this.head === null) return undefined;

    const node = this.head;
    const data = node.data;

    this.head = node.next;
    this.length -= 1;

    if (this.head !== null) {
      this.head.prev = null;
    } else {
      this.tail = null;
    }

    return data;
  }

  /** Same idea as ll_append: insert at the end of the list. */
  append(data: T): void {
    const node = new Node<T>(data);
    node.prev = this.tail;

    if (this.tail !== null) {
      this.tail.next = node;
    } else {
      this.head = node;
    }

    this.tail = node;
    this.length += 1;
  }

  /** Same idea as ll_remove: remove the first matching item. */
  remove(target: T, compare: CompareFunction<T>): T | undefined {
    let current = this.head;

    while (current !== null) {
      if (compare(target, current.data) === 0) {
        const data = current.data;

        if (current.prev !== null) {
          current.prev.next = current.next;
        } else {
          this.head = current.next;
        }

        if (current.next !== null) {
          current.next.prev = current.prev;
        } else {
          this.tail = current.prev;
        }

        this.length -= 1;
        return data;
      }

      current = current.next;
    }

    return undefined;
  }

  /** Same idea as ll_find: return the first matching item without removing it. */
  find(target: T, compare: CompareFunction<T>): T | undefined {
    let current = this.head;

    while (current !== null) {
      if (compare(target, current.data) === 0) {
        return current.data;
      }
      current = current.next;
    }

    return undefined;
  }

  /** Same idea as ll_size. */
  size(): number {
    return this.length;
  }

  /** Same idea as ll_clear. JavaScript garbage collection handles deallocation. */
  clear(): void {
    this.head = null;
    this.tail = null;
    this.length = 0;
  }

  /** Same idea as ll_map: apply a function to each item. */
  map(mapFunction: MapFunction<T>): void {
    let current = this.head;

    while (current !== null) {
      mapFunction(current.data);
      current = current.next;
    }
  }

  /** Helper for testing and printing. */
  toArray(): T[] {
    const result: T[] = [];
    this.map((data) => result.push(data));
    return result;
  }
}
