import { LinkedList } from "./my_linkedlist.ts";
import { mergeSort } from "./generalSort.ts";

type Student = {
  id: number;
  name: string;
};

function printSection(title: string): void {
  console.log(`\n=== ${title} ===`);
}

function testNumberList(): void {
  printSection("LinkedList<number>");

  const numbers = new LinkedList<number>();
  numbers.append(10);
  numbers.append(20);
  numbers.push(5);
  numbers.append(30);

  console.log("After push/append:", numbers.toArray());
  console.log("Size:", numbers.size());

  const found = numbers.find(20, (target, data) => target - data);
  console.log("Find 20:", found);

  const removed = numbers.remove(10, (target, data) => target - data);
  console.log("Remove 10:", removed);
  console.log("After remove:", numbers.toArray());

  const popped = numbers.pop();
  console.log("Pop:", popped);
  console.log("After pop:", numbers.toArray());

  console.log("Map output:");
  numbers.map((value) => console.log(`number item = ${value}`));

  numbers.clear();
  console.log("After clear size:", numbers.size());
}

function testStringList(): void {
  printSection("LinkedList<string>");

  const names = new LinkedList<string>();
  names.append("Ama");
  names.append("Kofi");
  names.push("Akosua");

  console.log("Names:", names.toArray());
  console.log("Find Kofi:", names.find("Kofi", (target, data) => target.localeCompare(data)));
  console.log("Remove Ama:", names.remove("Ama", (target, data) => target.localeCompare(data)));
  console.log("After remove:", names.toArray());
}

function testObjectList(): void {
  printSection("LinkedList<Student object>");

  const students = new LinkedList<Student>();
  students.append({ id: 1, name: "Desmond" });
  students.append({ id: 2, name: "Maya" });
  students.append({ id: 3, name: "Eli" });

  console.log("Students:", students.toArray());

  const target = { id: 2, name: "" };
  const found = students.find(target, (a, b) => a.id - b.id);
  console.log("Find student with id 2:", found);

  const removed = students.remove({ id: 1, name: "" }, (a, b) => a.id - b.id);
  console.log("Remove student with id 1:", removed);
  console.log("After remove:", students.toArray());
}

function testGenericSort(): void {
  printSection("Generic mergeSort<T>");

  const nums = [7, 2, 9, 1, 5];
  console.log("Numbers ascending:", mergeSort(nums, (a, b) => a - b));
  console.log("Numbers descending:", mergeSort(nums, (a, b) => b - a));

  const words = ["pear", "apple", "banana", "kiwi"];
  console.log("Words alphabetical:", mergeSort(words, (a, b) => a.localeCompare(b)));

  const students: Student[] = [
    { id: 3, name: "Eli" },
    { id: 1, name: "Desmond" },
    { id: 2, name: "Maya" },
  ];
  console.log("Students by id:", mergeSort(students, (a, b) => a.id - b.id));
}

function timingTest(): void {
  printSection("Timing test: built-in Array search behavior");

  const sizes = [10_000, 100_000, 500_000];

  for (const size of sizes) {
    const array = Array.from({ length: size }, (_, index) => index);
    const target = size - 1;

    const start = performance.now();
    const found = array.includes(target);
    const end = performance.now();

    console.log(`Array.includes on ${size} items: found=${found}, time=${(end - start).toFixed(4)} ms`);
  }

  console.log("Observation: searching with includes() grows roughly with N, so it behaves like linear search.");
  console.log("However, TypeScript/JavaScript arrays are not linked lists; they are optimized indexed arrays.");
}

testNumberList();
testStringList();
testObjectList();
testGenericSort();
timingTest();
