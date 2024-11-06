#!/bin/bash

g++ -std=c++17 -Wall -Wextra -pedantic-errors -Weffc++ -fsanitize=undefined,address *.cpp -o a.out

if [ $? -eq 0 ]; then
    echo "Compilation successful. Running the program..."
    ./a.out
else
    echo "Compilation failed."
fi