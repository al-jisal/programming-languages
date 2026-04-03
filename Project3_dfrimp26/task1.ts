/**
 * Filename: task1.ts -- Demonstrates:
 *                      1. Identifier naming rules
 *                      2. Variable declarations (let, const, var)
 *                      3. Identifier scoping in TypeScript
 * Author: Desmond Frimpong
 * Project: 03
 * Date: March 12, 2026
*/

// -----------------------------
// Identifier Naming Rules
// -----------------------------

// Valid identifiers
let _name: string;
_name = "Desmond"; 
let $dollar: number = 100;
let birth_date: string = "02/27/1990";

// Identifiers cannot start with numbers
// let 1value = 10;

// Identifiers cannot use reserved keywords
// let class = "Math"; 
// let import = 73;

console.log("User: ", _name);
console.log("Price: ", $dollar);
console.log("Date of birth: ", birth_date);


// -----------------------------
// Variable Declarations
// -----------------------------

// let → block-scoped and can be reassigned
let score: number = 50;
score = 75;

// const → block-scoped and cannot be reassigned
const MAX_USERS: number = 100;

// var → function-scoped (older JavaScript style)
var globalMessage: string = "Hello from var";

console.log("Score:", score);
console.log("Max users:", MAX_USERS);
console.log(globalMessage);


// -----------------------------
// Block Scope Example
// -----------------------------

function demonstrateScope() {
    let blockVar: string = "Inside function";

    if (true) {
        let blockOnly: string = "Inside block";
        console.log(blockOnly); // Accessible here
    }

    // console.log(blockOnly); Error: blockOnly not defined here

    console.log(blockVar); // Accessible in function
}
// console.log(blockVar); Error: blockVar not defined here
demonstrateScope();


// -----------------------------
// var vs let Scope Difference
// -----------------------------
function scopeDifference() {

    if (true) {
        var functionScoped = "I am var";
        let blockScoped = "I am let";
    }

    console.log(functionScoped); // Accessible (var is function-scoped)

    // console.log(blockScoped); Error: blockScoped only exists in block
}
scopeDifference();


// -----------------------------
// Shadowing Example
// -----------------------------

let value: number = 10;

function shadowExample() {
    let value: number = 20; // Shadows the outer variable
    console.log("Inside function:", value);
}

shadowExample();
console.log("Outside function:", value);