/**
 * Filename: task5.js -- demonstrates how JavaScript treats functions as values/data.
 *                        
 * Author: Desmond Frimpong
 * Project: 04
 * Date: March 20, 2026
*/

// Named function declaration
function square(x) {
  return x * x;
}

// Assign a function to a variable
const operation = square;
console.log("operation(5) =", operation(5));

// Anonymous function assigned to a variable
const cube = function (x) {
  return x * x * x;
};
console.log("cube(3) =", cube(3));

// Arrow function assigned to a variable
const double = (x) => x * 2;
console.log("double(10) =", double(10));

// Function passed to another function
function applyToArray(array, func) {
  const results = [];
  for (const item of array) {
    results.push(func(item)); // execute function using the reference
  }
  return results;
}

const numbers = [1, 2, 3, 4, 5];
console.log("squares:", applyToArray(numbers, square));
console.log("doubles:", applyToArray(numbers, double));

// Function returned from another function
function makeMultiplier(factor) {
  return function (value) {
    return value * factor;
  };
}

const triple = makeMultiplier(3);
console.log("triple(7) =", triple(7));

// Function does not have to be named
console.log(
  "anonymous function result:",
  applyToArray(numbers, function (n) {
    return n + 100;
  })
);
