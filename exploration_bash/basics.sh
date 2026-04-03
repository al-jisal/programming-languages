#!/bin/bash

factorial () {
    echo "Enter a positive number:"
    read power
    local result=1

    while [ $power -gt 1 ]; do
        result=$((result * power))
        power=$((power - 1))
    done

    echo "factorial is: $result"
}

factorial