/**
 * Filename: task3.ts -- demonstrates:
 *                      1. Built-in TypeScript types
 *                      2. Aggregate types (arrays, records, classes)
 *                      3. Operators (+ - * / %) and the resulting types
 * Author: Desmond Frimpong
 * Project: 03
 * Date: March 12, 2026
*/

// -----------------------------
// Basic Built-in Types
// -----------------------------

let num: number = 10;
let floatNum: number = 3.5;
let str: string = "Hello";
let bool: boolean = true;
let big: bigint = 9007199254740991n;
let nothing: null = null;
let notDefined: undefined = undefined;

// Type inference
let inferredNumber = 42; // TypeScript infers type: number


// -----------------------------
// Operators on Numbers
// -----------------------------

let a: number = 10;
let b: number = 3;

let addition: number = a + b;       // number
let subtraction: number = a - b;    // number
let multiplication: number = a * b; // number
let division: number = a / b;       // number
let modulus: number = a % b;        // number

console.log("Addition:", addition);
console.log("Subtraction:", subtraction);
console.log("Multiplication:", multiplication);
console.log("Division:", division);
console.log("Modulus:", modulus);


// -----------------------------
// Operator with Strings
// -----------------------------
let greeting: string = str + " World"; // string concatenation
console.log(greeting);

// -----------------------------
// Boolean Operators
// -----------------------------
let x: boolean = true;
let y: boolean = false;

let andResult: boolean = x && y;
let orResult: boolean = x || y;
let notResult: boolean = !x;

console.log(andResult, orResult, notResult);

// -----------------------------
// Arrays (Aggregate Type)
// -----------------------------
let numbers: number[] = [1, 2, 3, 4];
let names: Array<string> = ["Derrick", "Desmond", "Dennis"];

console.log(numbers);
console.log(names);

// -----------------------------
// Record Type (Object Structure)
// -----------------------------
type Person = {
    name: string;
    age: number;
};

let student: Person = {
    name: "Dennis",
    age: 21
};

console.log(student);

// -----------------------------
// Class Example (Aggregate Type)
// -----------------------------
class Rectangle {
    width: number;
    height: number;

    constructor(width: number, height: number) {
        this.width = width;
        this.height = height;
    }

    area(): number {
        return this.width * this.height; // multiplication returns number
    }
}

let rect = new Rectangle(5, 10);
console.log("Rectangle area:", rect.area());

// -----------------------------
// Tuple Type
// -----------------------------
let coordinate: [number, number] = [10, 20];
console.log("Coordinate:", coordinate);

// -----------------------------
// Any Type (dynamic)
// -----------------------------
let flexible: any = 5;
flexible = "Now I'm a string";
flexible = true;

console.log("Flexible value:", flexible);