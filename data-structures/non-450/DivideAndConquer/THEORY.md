# Divide and Conquer - Complete Guide

## Introduction
**Divide and Conquer** is an algorithm design paradigm that solves problems by:
1. **Divide:** Break problem into subproblems
2. **Conquer:** Solve subproblems recursively
3. **Combine:** Merge solutions of subproblems

## General Template
```
Function divideAndConquer(problem):
    if problem is small enough:
        solve directly (base case)

    divide problem into subproblems
    solve each subproblem recursively
    combine solutions
    return combined solution
```

## Classic Examples

### 1. Merge Sort
```
Divide array into halves
Recursively sort halves
Merge sorted halves
Time: O(n log n)
```

### 2. Quick Sort
```
Choose pivot
Partition around pivot
Recursively sort partitions
Time: O(n log n) average
```

### 3. Binary Search
```
Compare middle element
Search appropriate half
Time: O(log n)
```

### 4. Maximum Subarray (Kadane's)
```
Divide array into halves
Find max subarray in:
- Left half
- Right half
- Crossing middle
Time: O(n log n)
```

### 5. Closest Pair of Points
```
Divide points by x-coordinate
Find closest in each half
Check points near dividing line
Time: O(n log n)
```

### 6. Strassen's Matrix Multiplication
```
Divide matrices into quadrants
7 recursive multiplications
Combine results
Time: O(n^2.807) vs O(n^3) naive
```

## When to Use

✅ Problem can be broken into similar subproblems
✅ Subproblems are independent
✅ Combining solutions is efficient
✅ Base case is simple

❌ Subproblems overlap (use DP instead)
❌ Can't efficiently combine solutions
❌ Problem doesn't decompose naturally

## Divide & Conquer vs Dynamic Programming

| Divide & Conquer | Dynamic Programming |
|-----------------|---------------------|
| Subproblems are independent | Subproblems overlap |
| Top-down approach | Can be bottom-up |
| Examples: Merge Sort, Binary Search | Examples: Fibonacci, LCS |

## Common Problems

### Beginner:
- Merge Sort - Implement sorting
- Binary Search - Basic searching
- Power(x, n) - LeetCode #50

### Medium:
- Maximum Subarray - LeetCode #53
- Kth Largest Element - LeetCode #215 (QuickSelect)
- Different Ways to Add Parentheses - LeetCode #241

### Hard:
- Median of Two Sorted Arrays - LeetCode #4
- Count of Smaller Numbers After Self - LeetCode #315
- Reverse Pairs - LeetCode #493

### Expert:
- Count of Range Sum - LeetCode #327
- Burst Balloons - LeetCode #312

## Time Complexity Analysis

Using **Master Theorem**:
```
T(n) = aT(n/b) + f(n)

where:
a = number of subproblems
b = factor by which problem size reduces
f(n) = time to divide and combine

Examples:
- Merge Sort: T(n) = 2T(n/2) + O(n) = O(n log n)
- Binary Search: T(n) = T(n/2) + O(1) = O(log n)
- Strassen's: T(n) = 7T(n/2) + O(n^2) = O(n^2.807)
```

## Tips for Divide and Conquer Problems

1. **Identify base case** - When to stop dividing?
2. **How to divide?** - Middle? Pivot? Custom?
3. **How to combine?** - Merge? Select? Sum?
4. **Overlapping subproblems?** - If yes, use DP
5. **Can optimize?** - Reduce number of subproblems?

## Real-World Applications

- **Sorting algorithms** - Merge Sort, Quick Sort
- **Searching** - Binary Search
- **Computational geometry** - Closest pair, Convex hull
- **Image processing** - Recursive filtering
- **Parallel computing** - Naturally parallelizable

## Related Topics
- Recursion
- Dynamic Programming
- Greedy Algorithms
- Master Theorem

**Happy Learning! 🎓**
