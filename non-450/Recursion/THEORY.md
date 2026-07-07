# Recursion - Complete Guide

Not a standalone category in Love Babbar's DSA-450 sheet (the sheet has BackTracking as its own topic instead — see [BackTracking](../../theory/BackTracking/THEORY.md)), but recursion is the base technique backtracking, divide & conquer, and tree/graph traversal all build on.

## Introduction

**Recursion** is a technique where a function calls itself to solve smaller instances of the same problem.

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
3. **Graphics:** Fractal generation

## Tips for Mastering Recursion

1. **Identify base case first**
2. **Trust the recursion** (don't trace in head)
3. **Draw recursion tree** for understanding
4. **Convert to iteration** for optimization
5. **Add memoization** to avoid recomputation
6. **Practice, practice, practice!**

## Summary

Recursion is essential for:
- Tree and graph problems
- Divide and conquer
- Mathematical computations
- Backtracking (see [BackTracking](../../theory/BackTracking/THEORY.md))

**Key Takeaway:** Recursion is powerful but use wisely. Consider stack space and optimization.
