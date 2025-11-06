# Recursion & Backtracking - Complete Guide

## Introduction

**Recursion** is a technique where a function calls itself to solve smaller instances of the same problem. **Backtracking** is a refinement of recursion used to solve constraint satisfaction problems.

## What is Recursion?

A recursive function has two components:
1. **Base Case:** Condition to stop recursion
2. **Recursive Case:** Function calls itself with smaller input

**Simple Example:**
```
Function factorial(n):
    if n <= 1:           // Base case
        return 1
    return n * factorial(n-1)  // Recursive case
```

## Types of Recursion

### 1. Direct Recursion
Function calls itself directly.
```
Function f():
    f()  // Direct call
```

### 2. Indirect Recursion
Function A calls B, B calls A.
```
Function A():
    B()

Function B():
    A()
```

### 3. Tail Recursion
Recursive call is last operation.
```
Function factorial(n, accumulator=1):
    if n <= 1:
        return accumulator
    return factorial(n-1, n*accumulator)  // Tail call
```

### 4. Head Recursion
Operations before recursive call.
```
Function print(n):
    if n > 0:
        print(n-1)  // Recursive call first
        output(n)   // Then operation
```

### 5. Tree Recursion
Multiple recursive calls.
```
Function fibonacci(n):
    if n <= 1:
        return n
    return fibonacci(n-1) + fibonacci(n-2)  // Two calls
```

## Recursion vs Iteration

| Recursion | Iteration |
|-----------|-----------|
| Function calls itself | Uses loops |
| More elegant/readable | More efficient |
| Stack space O(n) | Space O(1) |
| May cause stack overflow | No stack issues |
| Good for trees, graphs | Good for arrays |

## Common Recursive Patterns

### 1. Linear Recursion
```
Process current element + recurse on rest

Function sum(array, n):
    if n == 0:
        return 0
    return array[n-1] + sum(array, n-1)
```

### 2. Divide and Conquer
```
Divide problem, solve subproblems, combine

Function mergeSort(array, left, right):
    if left >= right:
        return

    mid = (left + right) / 2
    mergeSort(array, left, mid)
    mergeSort(array, mid+1, right)
    merge(array, left, mid, right)
```

### 3. Decrease and Conquer
```
Reduce problem size by constant

Function binarySearch(array, target, left, right):
    if left > right:
        return -1

    mid = (left + right) / 2
    if array[mid] == target:
        return mid
    else if array[mid] < target:
        return binarySearch(array, target, mid+1, right)
    else:
        return binarySearch(array, target, left, mid-1)
```

## Backtracking

**Concept:** Try all possibilities, backtrack when constraint violated.

**Template:**
```
Function backtrack(state):
    if isValid(state) and isGoal(state):
        add state to results
        return

    for each choice in possibleChoices:
        if isValid(choice):
            makeChoice(choice)
            backtrack(newState)
            undoChoice(choice)  // Backtrack
```

### Classic Backtracking Problems:

1. **N-Queens:** Place N queens on N×N board
2. **Sudoku Solver:** Fill 9×9 grid with constraints
3. **Permutations:** Generate all permutations
4. **Combinations:** Generate all combinations
5. **Subset Sum:** Find subsets with target sum
6. **Word Search:** Find word in 2D grid
7. **Maze Problems:** Find path through maze

## Problem Statements

### Beginner: Fibonacci Number
**Problem:** Calculate nth Fibonacci number.
**Hints:** Base cases: F(0)=0, F(1)=1. Use memoization!
**Platform:** LeetCode #509

### Easy: Reverse Linked List
**Problem:** Reverse singly linked list recursively.
**Hints:** Reverse rest, adjust pointers
**Platform:** LeetCode #206

### Easy: Power of Two/Three/Four
**Problem:** Check if number is power of x.
**Hints:** Divide by x recursively until 1 or non-divisible
**Platform:** LeetCode #231, #326, #342

### Medium: Generate Parentheses
**Problem:** Generate all valid n pairs of parentheses.
**Hints:** Backtrack with count of open and close parens
**Platform:** LeetCode #22

### Medium: Permutations
**Problem:** Generate all permutations of array.
**Hints:** Swap elements, recurse, backtrack
**Platform:** LeetCode #46

### Medium: Subsets
**Problem:** Generate all possible subsets.
**Hints:** Include or exclude each element
**Platform:** LeetCode #78

### Medium: Letter Combinations of Phone Number
**Problem:** Generate letter combinations from phone digits.
**Hints:** Backtrack through digits, build combination
**Platform:** LeetCode #17

### Hard: N-Queens
**Problem:** Place N queens on N×N board (no attacks).
**Hints:** Try placing queen in each row, check validity
**Platform:** LeetCode #51

### Hard: Sudoku Solver
**Problem:** Solve Sudoku puzzle.
**Hints:** Try digits 1-9, backtrack if invalid
**Platform:** LeetCode #37

### Expert: Word Search II
**Problem:** Find all words from dictionary in board.
**Hints:** Build trie, DFS with backtracking
**Platform:** LeetCode #212

## Optimization Techniques

### 1. Memoization
Store results of subproblems.
```
memo = {}

Function fib(n):
    if n in memo:
        return memo[n]

    if n <= 1:
        return n

    memo[n] = fib(n-1) + fib(n-2)
    return memo[n]
```

### 2. Tail Call Optimization
Convert to tail recursion for optimization.

### 3. Iterative Conversion
Convert recursion to iteration for efficiency.

## Common Mistakes

1. **Missing Base Case:** Infinite recursion
2. **Wrong Base Case:** Incorrect results
3. **Not Making Progress:** State doesn't change
4. **Stack Overflow:** Too deep recursion
5. **Not Backtracking:** Wrong results in backtracking

## Recursion Tree Visualization

```
fibonacci(4)
├─ fibonacci(3)
│  ├─ fibonacci(2)
│  │  ├─ fibonacci(1) = 1
│  │  └─ fibonacci(0) = 0
│  └─ fibonacci(1) = 1
└─ fibonacci(2)
   ├─ fibonacci(1) = 1
   └─ fibonacci(0) = 0

Note: fibonacci(2) computed twice! → Use memoization
```

## Real-World Applications

1. **File Systems:** Directory traversal
2. **Compilers:** Expression parsing
3. **Game AI:** Minimax algorithm
4. **Graphics:** Fractal generation
5. **Puzzle Solvers:** Sudoku, chess

## Tips for Mastering Recursion

1. **Identify base case first**
2. **Trust the recursion** (don't trace in head)
3. **Draw recursion tree** for understanding
4. **Convert to iteration** for optimization
5. **Add memoization** to avoid recomputation
6. **Practice, practice, practice!**

## Summary

Recursion is essential for:
- ✅ Tree and graph problems
- ✅ Divide and conquer
- ✅ Backtracking problems
- ✅ Mathematical computations

**Key Takeaway:** Recursion is powerful but use wisely. Consider stack space and optimization.

**Happy Learning! 🎓**
