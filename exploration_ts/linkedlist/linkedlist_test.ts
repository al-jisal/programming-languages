/**
 *  file: linkedlist_test.ts
 * 
*/
import Linkedlist  from "./Linkedlist.ts";

type IntBox = { value: number };
type StrBox = { value: string };

// function that prints an integer
function printInt(i: IntBox): void {
    console.log(`value: ${i.value}`);
}

// function that squares an integer
function squareInt(i: IntBox): void {
    i.value = i.value * i.value;
}

// function that compares two integers and returns 0 if they are equal
function compInt(i: IntBox, j: IntBox): number {
    return i.value - j.value;
}

// function that prints a string
function printStr(s: StrBox): void {
    console.log(`value: ${s.value}`);
}

// function that converts a string to uppercase
function upperStr(s: StrBox): void {
    s.value = s.value.toUpperCase();
}

// function that compares two strings
function compStr(a: StrBox, b: StrBox): number {
    return a.value.localeCompare(b.value);
}

// test function for the various linked list functions
function main(): void {
    console.log("---------------- INTEGER TESTS ----------------");

    const l = new Linkedlist<IntBox>();

    // append data to the list
    for (let i = 0; i < 20; i += 2) {
        const a: IntBox = { value: i };
        l.ll_append(a);
    }

    // printing the list and testing map
    console.log("After initialization");
    l.ll_map(printInt);

    l.ll_map(squareInt);

    console.log("\nAfter squaring");
    l.ll_map(printInt);

    // testing removing data
    let target: IntBox = { value: 16 };
    let a = l.ll_remove(target, compInt);
    if (a !== null)
        console.log(`\nremoved: ${a.value}`);
    else
        console.log(`\nNo instance of ${target.value}`);

    a = l.ll_remove(target, compInt);
    if (a !== null)
        console.log(`\nremoved: ${a.value}`);
    else
        console.log(`\nNo instance of ${target.value}`);

    target = { value: 11 };
    a = l.ll_find(target, compInt);
    if (a !== null)
        console.log(`\nFound: ${a.value}`);
    else
        console.log(`\nNo instance of ${target.value}`);

    console.log("\nAfter removals");
    l.ll_map(printInt);

    // testing pushing data
    l.ll_push(target);

    console.log("\nAfter push");
    l.ll_map(printInt);

    // test clearing
    l.ll_clear();

    console.log("\nAfter clear");
    l.ll_map(printInt);

    // rebuild and test append and pop
    for (let i = 0; i < 5; i++) {
        const item: IntBox = { value: i };
        l.ll_append(item);
    }

    console.log("\nAfter appending");
    l.ll_map(printInt);

    a = l.ll_pop();
    if (a !== null) {
        console.log(`\npopped: ${a.value}`);
    }

    a = l.ll_pop();
    if (a !== null) {
        console.log(`popped: ${a.value}`);
    }

    console.log("\nAfter popping");
    l.ll_map(printInt);

    console.log(`\nList size: ${l.ll_size()}`);

    console.log("\n---------------- STRING TESTS ----------------");

    const slist = new Linkedlist<StrBox>();
    const words = ["apple", "banana", "mango", "pear", "grape"];

    for (let i = 0; i < words.length; i++) {
        const copy: StrBox = { value: words[i] };
        slist.ll_append(copy);
    }

    console.log("\nAfter string initialization");
    slist.ll_map(printStr);

    slist.ll_map(upperStr);

    console.log("\nAfter converting strings to uppercase");
    slist.ll_map(printStr);

    let wordTarget: StrBox = { value: "GRAPE" };

    let removedWord = slist.ll_remove(wordTarget, compStr);
    if (removedWord !== null) {
        console.log(`\nremoved: ${removedWord.value}`);
    } else {
        console.log(`\nNo instance of ${wordTarget.value}`);
    }

    removedWord = slist.ll_remove(wordTarget, compStr);
    if (removedWord !== null) {
        console.log(`\nremoved: ${removedWord.value}`);
    } else {
        console.log(`\nNo instance of ${wordTarget.value}`);
    }

    const foundWord = slist.ll_find(wordTarget, compStr);
    if (foundWord !== null)
        console.log(`\nFound: ${foundWord.value}`);
    else
        console.log(`\nNo instance of ${wordTarget.value}`);

    console.log("\nAfter string removal");
    slist.ll_map(printStr);

    const newWord: StrBox = { value: "coconunt" };
    slist.ll_push(newWord);

    console.log("\nAfter string push");
    slist.ll_map(printStr);

    const poppedWord = slist.ll_pop();
    if (poppedWord !== null) {
        console.log(`\npopped: ${poppedWord.value}`);
    }

    console.log("\nAfter popping a string");
    slist.ll_map(printStr);

    console.log(`\nString list size: ${slist.ll_size()}`);

    slist.ll_clear();
}

main();