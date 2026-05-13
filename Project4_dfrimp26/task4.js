/**
 * Filename: task4.js -- demonstrates javascript control flow statements
 *                        
 * Author: Desmond Frimpong
 * Project: 04
 * Date: March 20, 2026
*/

function controlFlowDemo(input) {
  console.log("=== if / else if / else ===");
  if (input > 0) {
    console.log(`${input} is positive`);
  } else if (input < 0) {
    console.log(`${input} is negative`);
  } else {
    console.log("input is zero");
  }

  console.log("\n=== switch ===");
  const day = "Monday";
  switch (day) {
    case "Monday":
      console.log("Start of the school/work week");
      break;
    case "Friday":
      console.log("Almost weekend");
      break;
    default:
      console.log("Regular day");
  }

  console.log("\n=== while ===");
  let count = 0;
  while (count < 3) {
    console.log(`while count = ${count}`);
    count++;
  }

  console.log("\n=== do...while ===");
  let attempts = 0;
  do {
    console.log(`do...while attempt = ${attempts}`);
    attempts++;
  } while (attempts < 2);

  console.log("\n=== for ===");
  for (let i = 0; i < 3; i++) {
    console.log(`for i = ${i}`);
  }

  console.log("\n=== for...of ===");
  const names = ["Ada", "Grace", "Linus"];
  for (const name of names) {
    console.log(name);
  }

  console.log("\n=== for...in ===");
  const student = { name: "Desmond", major: "CS", year: "Senior" };
  for (const key in student) {
    console.log(`${key}: ${student[key]}`);
  }

  console.log("\n=== break and continue ===");
  for (let i = 0; i < 6; i++) {
    if (i === 1) continue;
    if (i === 4) break;
    console.log(i);
  }

  console.log("\n=== labeled break ===");
  outerLoop:
  for (let row = 0; row < 3; row++) {
    for (let col = 0; col < 3; col++) {
      if (row === 1 && col === 1) {
        console.log("Breaking out of both loops");
        break outerLoop;
      }
      console.log(`row=${row}, col=${col}`);
    }
  }

  console.log("\n=== try / catch / finally ===");
  try {
    if (typeof input !== "number") {
      throw new TypeError("input must be a number");
    }
    console.log("No error thrown");
  } catch (error) {
    console.log(`Caught error: ${error.message}`);
  } finally {
    console.log("finally always runs");
  }

  console.log("\n=== conditional / ternary operator ===");
  const result = input % 2 === 0 ? "even" : "odd";
  console.log(`${input} is ${result}`);

  console.log("\n=== return ===");
  return "controlFlowDemo finished";
}

console.log(controlFlowDemo(5));