# Searching Algorithms - Complete Guide

## Introduction

**Searching** is the process of finding a particular element in a collection of elements. It's one of the most fundamental operations in computer science.

## Types of Searching Algorithms

### 1. Linear Search

**Concept:** Check each element sequentially until found or end reached.

**Pseudocode:**
```
Function linearSearch(array, target):
    for i from 0 to array.length-1:
        if array[i] == target:
            return i
    return -1  // not found
```

**Complexity:**
- Time: O(n)
- Space: O(1)

**When to Use:**
- ✅ Small datasets
- ✅ Unsorted data
- ✅ Single search operation
- ❌ Large datasets with multiple searches

### 2. Binary Search

**Concept:** Repeatedly divide sorted array in half, compare middle element.

**Visual:**
```
Array: [1, 3, 5, 7, 9, 11, 13, 15]
Target: 7

Step 1: mid=9 (too high), search left half [1,3,5,7]
Step 2: mid=5 (too low), search right half [7]
Step 3: mid=7 (found!)
```

**Pseudocode:**
```
Function binarySearch(array, target):
    left = 0
    right = array.length - 1

    while left <= right:
        mid = left + (right - left) / 2

        if array[mid] == target:
            return mid
        else if array[mid] < target:
            left = mid + 1
        else:
            right = mid - 1

    return -1  // not found
```

**Complexity:**
- Time: O(log n)
- Space: O(1) iterative, O(log n) recursive

**When to Use:**
- ✅ Sorted data
- ✅ Large datasets
- ✅ Multiple searches
- ❌ Unsorted data (sorting cost O(n log n))

### 3. Binary Search Variants

#### A. Find First Occurrence
```
Function findFirst(array, target):
    left = 0, right = array.length - 1
    result = -1

    while left <= right:
        mid = left + (right - left) / 2

        if array[mid] == target:
            result = mid
            right = mid - 1  // Continue searching left
        else if array[mid] < target:
            left = mid + 1
        else:
            right = mid - 1

    return result
```

#### B. Find Last Occurrence
```
Similar but: left = mid + 1 when found
```

#### C. Find Insert Position
```
Return left pointer when loop ends
```

### 4. Ternary Search

**Concept:** Divide into three parts, used for unimodal functions.

**Complexity:**
- Time: O(log₃ n)
- Less efficient than binary search for most cases

**When to Use:**
- Finding maximum/minimum in unimodal function
- Not for standard sorted array search

### 5. Exponential Search

**Concept:** Find range where element exists, then binary search.

**Steps:**
1. Find range: check positions 1, 2, 4, 8, 16, ...
2. Binary search in found range

**Complexity:**
- Time: O(log n)
- Better for unbounded/infinite arrays

### 6. Interpolation Search

**Concept:** Like binary search but calculates position based on value.

**Formula:**
```
pos = left + ((target - array[left]) * (right - left)) / (array[right] - array[left])
```

**Complexity:**
- Time: O(log log n) for uniformly distributed data, O(n) worst case
- Space: O(1)

**When to Use:**
- ✅ Uniformly distributed sorted data
- ❌ Non-uniform distribution

### 7. Jump Search

**Concept:** Jump ahead by fixed steps, then linear search back.

**Optimal jump size:** √n

**Complexity:**
- Time: O(√n)
- Space: O(1)

**When to Use:**
- Sorted array
- Costs of jumping and comparing are different

## Binary Search Problem Patterns

### Pattern 1: Find Exact Value
Standard binary search.

### Pattern 2: Find First/Last Occurrence
Modify binary search to continue searching after finding.

### Pattern 3: Find Boundary
Find transition point in boolean array (FFFTTT...).

### Pattern 4: Minimize/Maximize
Binary search on answer range.

**Example:** "Minimum capacity to ship packages in D days"
```
Binary search on capacity range [max(weights), sum(weights)]
Check if capacity allows shipping in D days
```

### Pattern 5: Search in 2D Matrix
Treat as 1D array or search row then column.

### Pattern 6: Search in Rotated Array
Find pivot, then binary search appropriate half.

## Problem Statements

### Beginner: Binary Search
**Problem:** Search for target in sorted array.
**Constraints:** -10⁴ ≤ nums[i], target ≤ 10⁴
**Hints:** Classic binary search template
**Platform:** LeetCode #704

### Easy: First Bad Version
**Problem:** Find first bad version in versions 1 to n.
**Hints:** Binary search with API call
**Platform:** LeetCode #278

### Easy: Search Insert Position
**Problem:** Find index to insert target in sorted array.
**Hints:** Return left pointer when not found
**Platform:** LeetCode #35

### Medium: Find First and Last Position
**Problem:** Find starting and ending position of target.
**Hints:** Two binary searches (find first, find last)
**Platform:** LeetCode #34

### Medium: Search in Rotated Sorted Array
**Problem:** Search in rotated sorted array.
**Hints:** Find which half is sorted, then search
**Platform:** LeetCode #33

### Medium: Find Peak Element
**Problem:** Find peak element in array.
**Hints:** Binary search, go towards increasing side
**Platform:** LeetCode #162

### Medium: Find Minimum in Rotated Sorted Array
**Problem:** Find minimum in rotated array.
**Hints:** Compare mid with right, adjust accordingly
**Platform:** LeetCode #153

### Hard: Median of Two Sorted Arrays
**Problem:** Find median of two sorted arrays.
**Hints:** Binary search on smaller array for partition
**Platform:** LeetCode #4

### Hard: Split Array Largest Sum
**Problem:** Split array into m subarrays minimizing largest sum.
**Hints:** Binary search on answer range
**Platform:** LeetCode #410

### Expert: Koko Eating Bananas
**Problem:** Minimum eating speed to finish bananas in h hours.
**Hints:** Binary search on speed range
**Platform:** LeetCode #875

## Comparison of Searching Algorithms

| Algorithm | Time (Avg) | Space | Requires Sorted | Best Use Case |
|-----------|-----------|-------|----------------|---------------|
| Linear | O(n) | O(1) | No | Small/unsorted data |
| Binary | O(log n) | O(1) | Yes | Sorted data |
| Jump | O(√n) | O(1) | Yes | Special cost models |
| Interpolation | O(log log n) | O(1) | Yes | Uniform distribution |
| Exponential | O(log n) | O(1) | Yes | Unbounded arrays |

## Binary Search Tips

### Common Mistakes:
1. ❌ `mid = (left + right) / 2` → may overflow
   ✅ `mid = left + (right - left) / 2`

2. ❌ `while left < right` vs `while left <= right`
   - Use `<=` for finding exact value
   - Use `<` for finding boundary

3. ❌ Infinite loops
   - Ensure left or right always changes

### Binary Search Template:
```
left = 0, right = n-1
while left <= right:
    mid = left + (right - left) / 2
    if condition:
        return mid
    else if ...:
        left = mid + 1
    else:
        right = mid - 1
return -1
```

## Real-World Applications

1. **Databases:** Index searching
2. **Version Control:** Finding bug introduction
3. **Networking:** IP routing
4. **File Systems:** Directory searching
5. **Machine Learning:** Hyperparameter tuning

## Related Topics

- Sorting (prerequisite for binary search)
- Divide and Conquer
- Two Pointers

## Summary

Searching algorithms are essential for:
- ✅ Data retrieval
- ✅ Decision making
- ✅ Optimization problems

**Key Takeaway:** Binary search is the most important searching algorithm to master. It's applicable far beyond just searching in arrays.

**Happy Learning! 🎓**
