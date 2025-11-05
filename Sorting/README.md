# Sorting Algorithms - Complete Guide

## Table of Contents
1. [Introduction](#introduction)
2. [Why Sorting Matters](#why-sorting-matters)
3. [Classification of Sorting Algorithms](#classification-of-sorting-algorithms)
4. [Comparison-Based Sorts](#comparison-based-sorts)
5. [Non-Comparison-Based Sorts](#non-comparison-based-sorts)
6. [Time & Space Complexity Summary](#time--space-complexity-summary)
7. [Choosing the Right Sorting Algorithm](#choosing-the-right-sorting-algorithm)
8. [Real-World Applications](#real-world-applications)
9. [Problem Statements](#problem-statements)
10. [Related Topics](#related-topics)

---

## Introduction

**Sorting** is the process of arranging elements in a specific order (ascending or descending). It's one of the most fundamental operations in computer science and a building block for many algorithms.

---

## Why Sorting Matters

### Benefits of Sorted Data:
- **Faster Searching:** Binary search (O(log n)) vs linear search (O(n))
- **Efficient Algorithms:** Many algorithms work better on sorted data
- **Data Organization:** Makes data easier to understand and process
- **Duplicate Detection:** Adjacent elements make duplicates obvious
- **Database Operations:** Efficient joins, merges, and grouping

---

## Classification of Sorting Algorithms

### 1. By Time Complexity:
- **O(n²):** Bubble, Selection, Insertion Sort
- **O(n log n):** Merge, Quick, Heap Sort
- **O(n):** Counting, Radix, Bucket Sort (under specific conditions)

### 2. By Space Complexity:
- **In-place:** Use O(1) extra space (Bubble, Selection, Insertion, Quick, Heap)
- **Out-of-place:** Use O(n) extra space (Merge, Counting, Radix)

### 3. By Stability:
- **Stable:** Preserve relative order of equal elements (Bubble, Insertion, Merge, Counting, Radix)
- **Unstable:** May change relative order (Selection, Quick, Heap)

### 4. By Method:
- **Comparison-based:** Compare elements (most sorts)
- **Non-comparison-based:** Use other properties (Counting, Radix, Bucket)

### 5. By Adaptivity:
- **Adaptive:** Faster on partially sorted data (Insertion, Bubble)
- **Non-adaptive:** Same performance regardless of input (Selection, Merge)

---

## Comparison-Based Sorts

### 1. Bubble Sort

**Concept:** Repeatedly swap adjacent elements if they're in wrong order.

**Visual:**
```
Pass 1: [5, 2, 8, 1, 9] → [2, 5, 1, 8, 9]
Pass 2: [2, 5, 1, 8, 9] → [2, 1, 5, 8, 9]
Pass 3: [2, 1, 5, 8, 9] → [1, 2, 5, 8, 9]
Pass 4: [1, 2, 5, 8, 9] → [1, 2, 5, 8, 9] (sorted)
```

**Pseudocode:**
```
Function bubbleSort(array):
    n = array.length

    for i from 0 to n-1:
        swapped = false

        for j from 0 to n-i-2:
            if array[j] > array[j+1]:
                swap(array[j], array[j+1])
                swapped = true

        if not swapped:
            break  // already sorted
```

**Complexity:**
- Time: O(n²) average/worst, O(n) best (already sorted)
- Space: O(1)
- Stable: Yes
- Adaptive: Yes

**When to Use:**
- ✅ Small datasets
- ✅ Educational purposes
- ❌ Never in production

---

### 2. Selection Sort

**Concept:** Find minimum element and place it at beginning, repeat for remaining.

**Visual:**
```
[5, 2, 8, 1, 9]
 ↓ Find min (1), swap with first
[1, 2, 8, 5, 9]
    ↓ Find min (2), already in place
[1, 2, 8, 5, 9]
       ↓ Find min (5), swap
[1, 2, 5, 8, 9]
          ↓ Find min (8), already in place
[1, 2, 5, 8, 9]
```

**Pseudocode:**
```
Function selectionSort(array):
    n = array.length

    for i from 0 to n-1:
        min_index = i

        for j from i+1 to n-1:
            if array[j] < array[min_index]:
                min_index = j

        if min_index != i:
            swap(array[i], array[min_index])
```

**Complexity:**
- Time: O(n²) always
- Space: O(1)
- Stable: No (can be made stable)
- Adaptive: No

**When to Use:**
- ✅ Small datasets
- ✅ Memory writes are expensive (minimum swaps)
- ❌ Large datasets

---

### 3. Insertion Sort

**Concept:** Build sorted array one element at a time by inserting into correct position.

**Visual:**
```
[5, 2, 8, 1, 9]
[5 | 2, 8, 1, 9]  Insert 2
[2, 5 | 8, 1, 9]  Insert 8
[2, 5, 8 | 1, 9]  Insert 1
[1, 2, 5, 8 | 9]  Insert 9
[1, 2, 5, 8, 9]
```

**Pseudocode:**
```
Function insertionSort(array):
    n = array.length

    for i from 1 to n-1:
        key = array[i]
        j = i - 1

        while j >= 0 and array[j] > key:
            array[j + 1] = array[j]
            j = j - 1

        array[j + 1] = key
```

**Complexity:**
- Time: O(n²) average/worst, O(n) best
- Space: O(1)
- Stable: Yes
- Adaptive: Yes

**When to Use:**
- ✅ Small datasets
- ✅ Nearly sorted data
- ✅ Online algorithms (data arriving one at a time)

---

### 4. Merge Sort

**Concept:** Divide array into halves, recursively sort, then merge.

**Visual:**
```
[5, 2, 8, 1, 9, 3, 7, 4]
       ↓ Divide
[5, 2, 8, 1]  [9, 3, 7, 4]
    ↓              ↓
[5, 2] [8, 1]  [9, 3] [7, 4]
  ↓  ↓   ↓  ↓    ↓  ↓   ↓  ↓
[5][2] [8][1]  [9][3] [7][4]
    ↓ Merge ↓
[2, 5] [1, 8]  [3, 9] [4, 7]
    ↓              ↓
[1, 2, 5, 8]  [3, 4, 7, 9]
         ↓ Merge ↓
[1, 2, 3, 4, 5, 7, 8, 9]
```

**Pseudocode:**
```
Function mergeSort(array, left, right):
    if left < right:
        mid = (left + right) / 2

        mergeSort(array, left, mid)
        mergeSort(array, mid + 1, right)
        merge(array, left, mid, right)

Function merge(array, left, mid, right):
    Create temp arrays L and R
    Copy data to L and R

    i = 0, j = 0, k = left

    while i < L.length and j < R.length:
        if L[i] <= R[j]:
            array[k] = L[i]
            i++
        else:
            array[k] = R[j]
            j++
        k++

    Copy remaining elements from L and R
```

**Complexity:**
- Time: O(n log n) always
- Space: O(n)
- Stable: Yes
- Adaptive: No

**When to Use:**
- ✅ Large datasets
- ✅ Need stable sort
- ✅ Linked lists (no random access needed)
- ✅ External sorting (data doesn't fit in memory)

---

### 5. Quick Sort

**Concept:** Choose pivot, partition array, recursively sort partitions.

**Visual:**
```
[5, 2, 8, 1, 9, 3]  pivot = 3
 ↓ Partition (elements < 3 left, >= 3 right)
[2, 1] 3 [5, 8, 9]
  ↓         ↓
[1, 2]   [5, 8, 9]  pivot = 8
          ↓ Partition
       [5] 8 [9]
Final: [1, 2, 3, 5, 8, 9]
```

**Pseudocode:**
```
Function quickSort(array, low, high):
    if low < high:
        pivot_index = partition(array, low, high)
        quickSort(array, low, pivot_index - 1)
        quickSort(array, pivot_index + 1, high)

Function partition(array, low, high):
    pivot = array[high]
    i = low - 1

    for j from low to high-1:
        if array[j] < pivot:
            i++
            swap(array[i], array[j])

    swap(array[i + 1], array[high])
    return i + 1
```

**Complexity:**
- Time: O(n log n) average, O(n²) worst
- Space: O(log n) (recursion stack)
- Stable: No
- Adaptive: No

**When to Use:**
- ✅ Large datasets (fastest average case)
- ✅ In-place sorting needed
- ✅ Cache-friendly access patterns
- ❌ Worst-case guarantee needed

---

### 6. Heap Sort

**Concept:** Build max heap, repeatedly extract maximum.

**Pseudocode:**
```
Function heapSort(array):
    n = array.length

    // Build max heap
    for i from n/2 - 1 down to 0:
        heapify(array, n, i)

    // Extract elements one by one
    for i from n-1 down to 1:
        swap(array[0], array[i])
        heapify(array, i, 0)

Function heapify(array, n, i):
    largest = i
    left = 2*i + 1
    right = 2*i + 2

    if left < n and array[left] > array[largest]:
        largest = left

    if right < n and array[right] > array[largest]:
        largest = right

    if largest != i:
        swap(array[i], array[largest])
        heapify(array, n, largest)
```

**Complexity:**
- Time: O(n log n) always
- Space: O(1)
- Stable: No
- Adaptive: No

**When to Use:**
- ✅ Need O(n log n) worst-case guarantee
- ✅ Limited memory (in-place)
- ❌ Need stable sort

---

## Non-Comparison-Based Sorts

### 7. Counting Sort

**Concept:** Count occurrences of each value, use counts to place elements.

**Visual:**
```
Input: [4, 2, 2, 8, 3, 3, 1]
Count: [0, 1, 2, 2, 1, 0, 0, 0, 1]  (indices 0-8 represent values)
        0  1  2  3  4  5  6  7  8

Cumulative: [0, 1, 3, 5, 6, 6, 6, 6, 7]
Output: [1, 2, 2, 3, 3, 4, 8]
```

**Pseudocode:**
```
Function countingSort(array, max_value):
    count = array of size max_value+1, initialized to 0

    // Count occurrences
    for each element in array:
        count[element]++

    // Reconstruct sorted array
    index = 0
    for value from 0 to max_value:
        while count[value] > 0:
            array[index] = value
            index++
            count[value]--
```

**Complexity:**
- Time: O(n + k) where k is range of input
- Space: O(k)
- Stable: Yes (with cumulative count version)

**When to Use:**
- ✅ Small range of integers
- ✅ Need stable sort
- ✅ Linear time required
- ❌ Large range (too much space)

---

### 8. Radix Sort

**Concept:** Sort digit by digit using stable sort (usually counting sort).

**Visual:**
```
Input: [170, 45, 75, 90, 802, 24, 2, 66]

Sort by ones digit:
[170, 90, 802, 2, 24, 45, 75, 66]

Sort by tens digit:
[802, 2, 24, 45, 66, 170, 75, 90]

Sort by hundreds digit:
[2, 24, 45, 66, 75, 90, 170, 802]
```

**Pseudocode:**
```
Function radixSort(array):
    max_element = find maximum element
    num_digits = number of digits in max_element

    for digit from 0 to num_digits-1:
        countingSortByDigit(array, digit)

Function countingSortByDigit(array, digit):
    // Use counting sort on specific digit
    // Implementation similar to counting sort
```

**Complexity:**
- Time: O(d × (n + k)) where d is number of digits, k is base
- Space: O(n + k)
- Stable: Yes

**When to Use:**
- ✅ Sorting integers or fixed-length strings
- ✅ Linear time needed
- ❌ Variable-length data

---

### 9. Bucket Sort

**Concept:** Distribute elements into buckets, sort each bucket, concatenate.

**Visual:**
```
Input: [0.42, 0.32, 0.23, 0.52, 0.25, 0.47, 0.51]

Create buckets for ranges [0-0.2), [0.2-0.4), [0.4-0.6), ...
Bucket 0: []
Bucket 1: [0.23, 0.25, 0.32]
Bucket 2: [0.42, 0.47, 0.51, 0.52]

Sort each bucket (insertion sort)
Bucket 1: [0.23, 0.25, 0.32]
Bucket 2: [0.42, 0.47, 0.51, 0.52]

Concatenate: [0.23, 0.25, 0.32, 0.42, 0.47, 0.51, 0.52]
```

**Pseudocode:**
```
Function bucketSort(array, num_buckets):
    buckets = array of num_buckets empty lists

    // Distribute elements
    for each element in array:
        bucket_index = floor(element * num_buckets)
        buckets[bucket_index].append(element)

    // Sort each bucket
    for each bucket in buckets:
        insertionSort(bucket)

    // Concatenate buckets
    result = concatenate all buckets
    return result
```

**Complexity:**
- Time: O(n + k) average, O(n²) worst
- Space: O(n + k)
- Stable: Depends on bucket sort used

**When to Use:**
- ✅ Uniformly distributed data
- ✅ Floating-point numbers
- ❌ Non-uniform distribution

---

## Time & Space Complexity Summary

| Algorithm | Best | Average | Worst | Space | Stable |
|-----------|------|---------|-------|-------|--------|
| **Bubble Sort** | O(n) | O(n²) | O(n²) | O(1) | Yes |
| **Selection Sort** | O(n²) | O(n²) | O(n²) | O(1) | No |
| **Insertion Sort** | O(n) | O(n²) | O(n²) | O(1) | Yes |
| **Merge Sort** | O(n log n) | O(n log n) | O(n log n) | O(n) | Yes |
| **Quick Sort** | O(n log n) | O(n log n) | O(n²) | O(log n) | No |
| **Heap Sort** | O(n log n) | O(n log n) | O(n log n) | O(1) | No |
| **Counting Sort** | O(n+k) | O(n+k) | O(n+k) | O(k) | Yes |
| **Radix Sort** | O(d(n+k)) | O(d(n+k)) | O(d(n+k)) | O(n+k) | Yes |
| **Bucket Sort** | O(n+k) | O(n+k) | O(n²) | O(n+k) | Yes* |

---

## Choosing the Right Sorting Algorithm

### Decision Tree:

```
Need stable sort?
├─ Yes:
│  ├─ Small data → Insertion Sort
│  ├─ Large data → Merge Sort
│  └─ Integers, small range → Counting/Radix Sort
│
└─ No:
   ├─ Need O(1) space?
   │  ├─ Yes: Quick Sort (average) or Heap Sort (guaranteed)
   │  └─ No: Merge Sort
   │
   └─ Special cases:
      ├─ Nearly sorted → Insertion Sort
      ├─ Small fixed range → Counting Sort
      ├─ Integers → Radix Sort
      └─ Uniform distribution → Bucket Sort
```

---

## Real-World Applications

### 1. Databases
- **Index creation**
- **JOIN operations**
- **ORDER BY queries**

### 2. Operating Systems
- **Process scheduling**
- **File system organization**
- **Memory management**

### 3. Data Analysis
- **Finding median**
- **Identifying outliers**
- **Ranking systems**

### 4. E-commerce
- **Product listings (price, rating)**
- **Search results ranking**
- **Recommendation sorting**

### 5. Computer Graphics
- **Z-buffer sorting**
- **Render order**
- **Color palette generation**

---

## Problem Statements

### Beginner Level

#### Problem 1: Sort an Array
**Difficulty:** Beginner

**Problem Statement:**
Given an array of integers nums, sort the array in ascending order and return it. You must solve without using built-in sort functions.

**Example:**
```
Input: nums = [5,2,3,1]
Output: [1,2,3,5]

Input: nums = [5,1,1,2,0,0]
Output: [0,0,1,1,2,5]
```

**Constraints:**
- 1 ≤ nums.length ≤ 5 * 10^4
- -5 * 10^4 ≤ nums[i] ≤ 5 * 10^4

**Hints:**
1. Implement any O(n log n) sorting algorithm
2. Merge sort or quick sort recommended
3. Handle edge cases (empty, single element)

**Test Cases:**
```
Test 1: [] → Expected: []
Test 2: [1] → Expected: [1]
Test 3: [2,1] → Expected: [1,2]
Test 4: [1,1,1] → Expected: [1,1,1]
```

**Practice Platform:** LeetCode #912

---

#### Problem 2: Largest Number
**Difficulty:** Medium-Beginner

**Problem Statement:**
Given a list of non-negative integers nums, arrange them such that they form the largest number and return it as a string.

**Example:**
```
Input: nums = [10,2]
Output: "210"

Input: nums = [3,30,34,5,9]
Output: "9534330"
```

**Constraints:**
- 1 ≤ nums.length ≤ 100
- 0 ≤ nums[i] ≤ 10^9

**Hints:**
1. Custom comparator: compare concatenations
2. For numbers a and b, compare "ab" vs "ba"
3. Sort using this custom comparator

**Test Cases:**
```
Test 1: [0,0] → Expected: "0"
Test 2: [1] → Expected: "1"
Test 3: [12,121] → Expected: "12121"
```

**Practice Platform:** LeetCode #179

---

### Easy Level

#### Problem 3: Merge Sorted Array
**Difficulty:** Easy

**Problem Statement:**
You are given two integer arrays nums1 and nums2, sorted in non-decreasing order. Merge nums2 into nums1 in sorted order. nums1 has enough space to hold both arrays.

**Example:**
```
Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
Output: [1,2,2,3,5,6]

Input: nums1 = [1], m = 1, nums2 = [], n = 0
Output: [1]
```

**Constraints:**
- nums1.length == m + n
- nums2.length == n
- 0 ≤ m, n ≤ 200

**Hints:**
1. Start merging from the end
2. Compare elements from end of both arrays
3. Place larger element at end of nums1

**Test Cases:**
```
Test 1: nums1=[0], m=0, nums2=[1], n=1 → Expected: [1]
Test 2: nums1=[2,0], m=1, nums2=[1], n=1 → Expected: [1,2]
```

**Practice Platform:** LeetCode #88

---

### Medium Level

#### Problem 4: Sort Colors
**Difficulty:** Medium

**Problem Statement:**
Given an array nums with n objects colored red (0), white (1), or blue (2), sort them in-place so that objects of the same color are adjacent, in order red, white, blue.

**Example:**
```
Input: nums = [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]

Input: nums = [2,0,1]
Output: [0,1,2]
```

**Constraints:**
- n == nums.length
- 1 ≤ n ≤ 300
- nums[i] is 0, 1, or 2

**Hints:**
1. Dutch National Flag problem
2. Use three pointers: low, mid, high
3. One-pass solution possible

**Test Cases:**
```
Test 1: [0] → Expected: [0]
Test 2: [2,1,0] → Expected: [0,1,2]
Test 3: [1,1,1] → Expected: [1,1,1]
```

**Practice Platform:** LeetCode #75

---

#### Problem 5: Kth Largest Element
**Difficulty:** Medium

**Problem Statement:**
Given an integer array nums and an integer k, return the kth largest element in the array. Note that it is the kth largest element in sorted order, not the kth distinct element.

**Example:**
```
Input: nums = [3,2,1,5,6,4], k = 2
Output: 5

Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
Output: 4
```

**Constraints:**
- 1 ≤ k ≤ nums.length ≤ 10^5
- -10^4 ≤ nums[i] ≤ 10^4

**Hints:**
1. Use QuickSelect algorithm (avg O(n))
2. Or use min heap of size k (O(n log k))
3. Or sort and return nums[n-k] (O(n log n))

**Test Cases:**
```
Test 1: [1], k=1 → Expected: 1
Test 2: [1,2], k=1 → Expected: 2
Test 3: [1,2], k=2 → Expected: 1
```

**Practice Platform:** LeetCode #215

---

### Hard Level

#### Problem 6: Count of Smaller Numbers After Self
**Difficulty:** Hard

**Problem Statement:**
Given an integer array nums, return an integer array counts where counts[i] is the number of smaller elements to the right of nums[i].

**Example:**
```
Input: nums = [5,2,6,1]
Output: [2,1,1,0]
Explanation:
To the right of 5: 2 and 1 are smaller
To the right of 2: only 1 is smaller
To the right of 6: only 1 is smaller
To the right of 1: no smaller elements

Input: nums = [-1,-1]
Output: [0,0]
```

**Constraints:**
- 1 ≤ nums.length ≤ 10^5
- -10^4 ≤ nums[i] ≤ 10^4

**Hints:**
1. Use modified merge sort
2. Count inversions during merge
3. Maintain index mapping

**Test Cases:**
```
Test 1: [1] → Expected: [0]
Test 2: [1,2,3] → Expected: [0,0,0]
Test 3: [3,2,1] → Expected: [2,1,0]
```

**Practice Platform:** LeetCode #315

---

## Related Topics

### Prerequisites:
- Arrays
- Recursion
- Complexity Analysis

### Related Algorithms:
- Binary Search (requires sorted data)
- Two Pointers
- Divide and Conquer

### Advanced Topics:
- External Sorting
- Parallel Sorting
- Distributed Sorting

---

## Summary

Sorting algorithms are fundamental for:
- ✅ Data organization and retrieval
- ✅ Enabling efficient searching
- ✅ Preprocessing for other algorithms
- ✅ Understanding algorithm design paradigms

**Key Takeaways:**
1. No one-size-fits-all sorting algorithm
2. Consider data characteristics when choosing
3. Understand trade-offs: time, space, stability
4. Master at least one O(n log n) algorithm

---

**Happy Learning! 🎓**

*Master sorting, and you'll understand the foundation of algorithmic efficiency!*
