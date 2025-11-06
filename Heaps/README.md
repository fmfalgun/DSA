# Heaps - Complete Guide

## Table of Contents
1. [Introduction](#introduction)
2. [What is a Heap?](#what-is-a-heap)
3. [Types of Heaps](#types-of-heaps)
4. [Heap Properties](#heap-properties)
5. [Visual Representation](#visual-representation)
6. [Implementation Guidelines](#implementation-guidelines)
7. [Core Operations](#core-operations)
8. [Time & Space Complexity](#time--space-complexity)
9. [When to Use Heaps](#when-to-use-heaps)
10. [Real-World Applications](#real-world-applications)
11. [Problem Statements](#problem-statements)
12. [Related Topics](#related-topics)

---

## Introduction

A **Heap** is a specialized tree-based data structure that satisfies the **heap property**. It is a complete binary tree where each parent node has a specific ordering relationship with its children. Heaps are primarily used to implement **priority queues** and for efficient sorting (Heap Sort).

---

## What is a Heap?

A heap is a **complete binary tree** (all levels are fully filled except possibly the last level, which is filled from left to right) that maintains a specific ordering property between parent and child nodes.

### Key Characteristics:
- **Complete Binary Tree** - All levels filled except possibly the last
- **Heap Property** - Parent-child relationship follows specific ordering
- **Array Representation** - Efficiently stored as an array
- **Efficient Operations** - Insertion and deletion in O(log n) time
- **Root Access** - Minimum or maximum element accessible in O(1) time

---

## Types of Heaps

### 1. **Min Heap**
- **Property:** Parent node ≤ all its children
- **Root:** Contains the minimum element
- **Use Case:** Get minimum element quickly

### 2. **Max Heap**
- **Property:** Parent node ≥ all its children
- **Root:** Contains the maximum element
- **Use Case:** Get maximum element quickly

### 3. **Specialized Heaps**
- **Binary Heap:** Most common, uses complete binary tree
- **Fibonacci Heap:** More efficient for certain operations (amortized O(1) for insert and decrease-key)
- **Binomial Heap:** Collection of binomial trees
- **d-ary Heap:** Each node has d children instead of 2

---

## Heap Properties

### Complete Binary Tree Property
```
Valid Complete Binary Tree (Heap):
       10
      /  \
     20   15
    / \   /
   30 25 40

Invalid (Not Complete):
       10
      /  \
     20   15
    /      \
   30      40   (Gap in level)
```

### Heap Order Property

**Min Heap Example:**
```
        1
       / \
      3   2
     / \ / \
    7  5 4  6
```
Every parent ≤ its children

**Max Heap Example:**
```
        100
        / \
       80  90
      / \ / \
     40 60 70 50
```
Every parent ≥ its children

---

## Visual Representation

### Array Representation of Heap

For a node at index `i`:
- **Left child:** `2*i + 1`
- **Right child:** `2*i + 2`
- **Parent:** `(i - 1) / 2`

**Example Max Heap:**
```
Visual Tree:
        50
       /  \
      30   40
     / \   /
    10 20 35

Array Representation:
Index:  0   1   2   3   4   5
Value: [50, 30, 40, 10, 20, 35]

Relationships:
- 50 (index 0): children at indices 1(30) and 2(40)
- 30 (index 1): children at indices 3(10) and 4(20)
- 40 (index 2): children at indices 5(35) and 6(none)
```

---

## Implementation Guidelines

### Basic Structure (Language-Agnostic Pseudocode)

```
Class Heap:
    Array heap
    Integer size
    String heap_type  // "min" or "max"

    Function Constructor(type):
        heap = empty array
        size = 0
        heap_type = type

    Function parent(i):
        return (i - 1) / 2

    Function leftChild(i):
        return 2 * i + 1

    Function rightChild(i):
        return 2 * i + 2

    Function swap(i, j):
        temp = heap[i]
        heap[i] = heap[j]
        heap[j] = temp
```

### Heapify Operation

**Heapify Down (Bubble Down):** Used after deletion
```
Function heapifyDown(index):
    while index has at least one child:
        if heap_type is "min":
            smallerChild = index of child with smaller value
            if heap[index] > heap[smallerChild]:
                swap(index, smallerChild)
                index = smallerChild
            else:
                break
        else:  // max heap
            largerChild = index of child with larger value
            if heap[index] < heap[largerChild]:
                swap(index, largerChild)
                index = largerChild
            else:
                break
```

**Heapify Up (Bubble Up):** Used after insertion
```
Function heapifyUp(index):
    while index > 0:
        parentIndex = parent(index)
        if heap_type is "min":
            if heap[index] < heap[parentIndex]:
                swap(index, parentIndex)
                index = parentIndex
            else:
                break
        else:  // max heap
            if heap[index] > heap[parentIndex]:
                swap(index, parentIndex)
                index = parentIndex
            else:
                break
```

---

## Core Operations

### 1. Insert (Push)
```
Function insert(value):
    heap.append(value)
    size = size + 1
    heapifyUp(size - 1)
```
**Time Complexity:** O(log n)

### 2. Extract Min/Max (Pop)
```
Function extractTop():
    if size == 0:
        return error or null

    topValue = heap[0]
    heap[0] = heap[size - 1]
    heap.remove_last()
    size = size - 1

    if size > 0:
        heapifyDown(0)

    return topValue
```
**Time Complexity:** O(log n)

### 3. Peek (Get Top)
```
Function peek():
    if size == 0:
        return error or null
    return heap[0]
```
**Time Complexity:** O(1)

### 4. Build Heap
```
Function buildHeap(array):
    heap = copy of array
    size = array.length

    // Start from last non-leaf node
    for i from (size/2 - 1) down to 0:
        heapifyDown(i)
```
**Time Complexity:** O(n)

### 5. Heap Sort
```
Function heapSort(array):
    buildHeap(array)

    for i from (size - 1) down to 1:
        swap(0, i)
        size = size - 1
        heapifyDown(0)

    return array
```
**Time Complexity:** O(n log n)

---

## Time & Space Complexity

| Operation | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| Insert | O(log n) | O(1) |
| Extract Min/Max | O(log n) | O(1) |
| Peek (Get Top) | O(1) | O(1) |
| Delete arbitrary element | O(log n) | O(1) |
| Build Heap | O(n) | O(1) |
| Heapify | O(log n) | O(1) |
| Heap Sort | O(n log n) | O(1) |
| Search | O(n) | O(1) |

**Note:** Heaps are not optimized for search operations.

---

## When to Use Heaps

### ✅ Use Heaps When:
- You need to repeatedly find and remove the min/max element
- Implementing a priority queue
- Need efficient access to kth largest/smallest elements
- Implementing algorithms like Dijkstra's, Prim's, or Huffman coding
- Streaming data where you need to maintain top k elements
- Merge k sorted arrays/lists

### ❌ Avoid Heaps When:
- You need to search for arbitrary elements (use hash table)
- You need to maintain sorted order of all elements (use balanced BST)
- You need both min and max frequently (consider min-max heap)
- Memory is extremely limited and operations are infrequent

---

## Real-World Applications

1. **Operating Systems**
   - Process scheduling (priority queue)
   - Memory management

2. **Networking**
   - Bandwidth management
   - Load balancing
   - Packet routing

3. **Data Processing**
   - Finding median in streaming data
   - Top K most frequent items
   - Event-driven simulation

4. **Algorithms**
   - Dijkstra's shortest path
   - Prim's minimum spanning tree
   - Huffman encoding
   - A* pathfinding

5. **Real-Time Systems**
   - Task scheduling
   - Timer management

---

## Problem Statements

### Beginner Level

#### Problem 1: Kth Largest Element in an Array
**Difficulty:** Beginner

**Problem Statement:**
Find the kth largest element in an unsorted array. Note that it is the kth largest element in sorted order, not the kth distinct element.

**Example:**
```
Input: nums = [3,2,1,5,6,4], k = 2
Output: 5

Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
Output: 4
```

**Constraints:**
- 1 ≤ k ≤ array length ≤ 10^5
- -10^4 ≤ nums[i] ≤ 10^4

**Hints:**
1. Use a min heap of size k
2. Keep only k largest elements in the heap
3. The root of the heap will be the kth largest

**Test Cases:**
```
Test 1: [1], k=1 → Expected: 1
Test 2: [5,4,3,2,1], k=3 → Expected: 3
Test 3: [1,1,1,1], k=2 → Expected: 1
```

**Practice Platform:** LeetCode #215

---

#### Problem 2: Last Stone Weight
**Difficulty:** Beginner

**Problem Statement:**
You are given an array of integers `stones` where `stones[i]` is the weight of the ith stone. On each turn, we choose the two heaviest stones and smash them together. Suppose the stones have weights x and y with x ≤ y:
- If x == y, both stones are destroyed
- If x != y, the stone of weight x is destroyed, and the stone of weight y has new weight y-x

Return the weight of the last remaining stone, or 0 if none remain.

**Example:**
```
Input: stones = [2,7,4,1,8,1]
Output: 1
Explanation:
- Combine 7 and 8 → 1, stones = [2,4,1,1,1]
- Combine 2 and 4 → 2, stones = [2,1,1,1]
- Combine 2 and 1 → 1, stones = [1,1,1]
- Combine 1 and 1 → 0, stones = [1]
- Return 1
```

**Constraints:**
- 1 ≤ stones.length ≤ 30
- 1 ≤ stones[i] ≤ 1000

**Hints:**
1. Use a max heap to always get the two heaviest stones
2. Extract two elements, compute difference, insert back if non-zero
3. Repeat until 0 or 1 stone remains

**Test Cases:**
```
Test 1: [1] → Expected: 1
Test 2: [1,1] → Expected: 0
Test 3: [2,2] → Expected: 0
Test 4: [5,3] → Expected: 2
```

**Practice Platform:** LeetCode #1046

---

### Easy Level

#### Problem 3: Kth Smallest Element in a Sorted Matrix
**Difficulty:** Easy

**Problem Statement:**
Given an n x n matrix where each row and column is sorted in ascending order, find the kth smallest element in the matrix.

**Example:**
```
Input: matrix = [[1,5,9],
                 [10,11,13],
                 [12,13,15]], k = 8
Output: 13
```

**Constraints:**
- n == matrix.length == matrix[i].length
- 1 ≤ n ≤ 300
- -10^9 ≤ matrix[i][j] ≤ 10^9
- 1 ≤ k ≤ n^2

**Hints:**
1. Use a min heap with elements from the first row
2. Extract min and add the next element from that column
3. Repeat k times

**Test Cases:**
```
Test 1: [[1,2],[3,4]], k=2 → Expected: 2
Test 2: [[-5]], k=1 → Expected: -5
```

**Practice Platform:** LeetCode #378

---

#### Problem 4: Minimum Cost to Connect Sticks
**Difficulty:** Easy

**Problem Statement:**
You have some sticks with positive integer lengths. You can connect any two sticks of lengths X and Y into one stick by paying a cost of X + Y. Return the minimum cost to connect all sticks into one.

**Example:**
```
Input: sticks = [2,4,3]
Output: 14
Explanation:
- Connect 2 and 3 for cost 5, sticks = [5,4]
- Connect 5 and 4 for cost 9, sticks = [9]
- Total cost = 5 + 9 = 14
```

**Constraints:**
- 1 ≤ sticks.length ≤ 10^4
- 1 ≤ sticks[i] ≤ 10^4

**Hints:**
1. Always connect the two smallest sticks first (greedy approach)
2. Use a min heap to efficiently get the smallest sticks
3. Add the combined stick back to the heap

**Test Cases:**
```
Test 1: [1,8,3,5] → Expected: 30
Test 2: [1] → Expected: 0
Test 3: [5,5,5,5] → Expected: 40
```

**Practice Platform:** LeetCode #1167 (Premium)

---

### Medium Level

#### Problem 5: Top K Frequent Elements
**Difficulty:** Medium

**Problem Statement:**
Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.

**Example:**
```
Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]

Input: nums = [1], k = 1
Output: [1]
```

**Constraints:**
- 1 ≤ nums.length ≤ 10^5
- -10^4 ≤ nums[i] ≤ 10^4
- k is in the range [1, number of unique elements]

**Hints:**
1. First count frequency of each element (use hash map)
2. Use a min heap of size k based on frequency
3. The heap will contain k most frequent elements

**Test Cases:**
```
Test 1: [4,4,4,1,1,2], k=2 → Expected: [4,1]
Test 2: [1,2,3], k=1 → Can be any one element
```

**Practice Platform:** LeetCode #347

---

#### Problem 6: Find Median from Data Stream
**Difficulty:** Medium

**Problem Statement:**
Design a data structure that supports the following operations:
- `addNum(int num)` - Add an integer from the data stream
- `findMedian()` - Return the median of all elements so far

**Example:**
```
Input: ["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
       [[], [1], [2], [], [3], []]
Output: [null, null, null, 1.5, null, 2.0]
```

**Constraints:**
- -10^5 ≤ num ≤ 10^5
- At most 5 * 10^4 calls to addNum and findMedian

**Hints:**
1. Use two heaps: a max heap for the smaller half, min heap for the larger half
2. Keep heaps balanced (sizes differ by at most 1)
3. Median is the top of larger heap (if sizes differ) or average of both tops

**Test Cases:**
```
Test 1: Add [1,2,3,4,5], medians: 1, 1.5, 2, 2.5, 3
Test 2: Add [5,4,3,2,1], medians: 5, 4.5, 4, 3.5, 3
```

**Practice Platform:** LeetCode #295

---

#### Problem 7: Merge K Sorted Lists
**Difficulty:** Medium

**Problem Statement:**
You are given an array of k linked lists, each linked list is sorted in ascending order. Merge all the linked-lists into one sorted linked-list and return it.

**Example:**
```
Input: lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
```

**Constraints:**
- k == lists.length
- 0 ≤ k ≤ 10^4
- 0 ≤ lists[i].length ≤ 500
- -10^4 ≤ lists[i][j] ≤ 10^4

**Hints:**
1. Use a min heap to keep track of the smallest current element from each list
2. Extract min, add to result, and push the next element from that list
3. Continue until all lists are exhausted

**Test Cases:**
```
Test 1: [[]] → Expected: []
Test 2: [[1],[2],[3]] → Expected: [1,2,3]
Test 3: [[1,4,7],[2,5,8],[3,6,9]] → Expected: [1,2,3,4,5,6,7,8,9]
```

**Practice Platform:** LeetCode #23

---

### Hard Level

#### Problem 8: Sliding Window Median
**Difficulty:** Hard

**Problem Statement:**
Given an array of integers and a window size k, return the median of each sliding window.

**Example:**
```
Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [1.0,-1.0,-1.0,3.0,5.0,6.0]
Explanation:
Window [1,3,-1] → median 1
Window [3,-1,-3] → median -1
...
```

**Constraints:**
- 1 ≤ k ≤ nums.length ≤ 10^5
- -2^31 ≤ nums[i] ≤ 2^31 - 1

**Hints:**
1. Use two heaps (like Find Median from Stream)
2. When sliding window, remove outgoing element and add incoming element
3. Removing arbitrary element from heap requires tracking positions

**Test Cases:**
```
Test 1: [1,2,3,4], k=2 → Expected: [1.5,2.5,3.5]
Test 2: [1,4,2,3], k=4 → Expected: [2.5]
```

**Practice Platform:** LeetCode #480

---

#### Problem 9: IPO
**Difficulty:** Hard

**Problem Statement:**
You are given n projects where the ith project has a pure profit profits[i] and minimum capital capital[i] needed to start it. Initially, you have w capital. When you finish a project, you gain its profit and the profit is added to your total capital. Pick k distinct projects from given projects to maximize final capital.

**Example:**
```
Input: k = 2, w = 0, profits = [1,2,3], capital = [0,1,1]
Output: 4
Explanation:
- Start project 0 (capital 0, profit 1), total capital = 1
- Start project 2 (capital 1, profit 3), total capital = 4
```

**Constraints:**
- 1 ≤ k ≤ 10^5
- 0 ≤ w ≤ 10^9
- n == profits.length == capital.length
- 1 ≤ n ≤ 10^5

**Hints:**
1. Use a min heap to store projects by capital requirement
2. Use a max heap to store available projects by profit
3. At each step, move all affordable projects to max heap and pick highest profit

**Test Cases:**
```
Test 1: k=1, w=0, profits=[1,2,3], capital=[0,1,2] → Expected: 1
Test 2: k=3, w=0, profits=[1,2,3], capital=[0,0,0] → Expected: 6
```

**Practice Platform:** LeetCode #502

---

### Expert Level

#### Problem 10: Trapping Rain Water II
**Difficulty:** Expert

**Problem Statement:**
Given an m x n integer matrix heightMap representing the height of each unit cell, return the volume of water it can trap after raining.

**Example:**
```
Input: heightMap = [[1,4,3,1,3,2],
                     [3,2,1,3,2,4],
                     [2,3,3,2,3,1]]
Output: 4
```

**Constraints:**
- m == heightMap.length
- n == heightMap[i].length
- 1 ≤ m, n ≤ 200
- 0 ≤ heightMap[i][j] ≤ 2 * 10^4

**Hints:**
1. Process cells from outside to inside (like Dijkstra's)
2. Use min heap to always process the cell with minimum height
3. Water level at each cell is determined by the minimum height on path to boundary

**Test Cases:**
```
Test 1: [[1,1,1],[1,0,1],[1,1,1]] → Expected: 1
Test 2: [[3,3,3],[3,0,3],[3,3,3]] → Expected: 3
```

**Practice Platform:** LeetCode #407

---

#### Problem 11: Minimum Number of Refueling Stops
**Difficulty:** Expert

**Problem Statement:**
A car travels from a starting position to a destination distance away. There are gas stations along the way. The car starts with startFuel liters of fuel. Return the minimum number of refueling stops needed to reach destination, or -1 if impossible.

**Example:**
```
Input: target = 100, startFuel = 10, stations = [[10,60],[20,30],[30,30],[60,40]]
Output: 2
Explanation:
- Drive to station at position 10, refuel 60 liters (total: 60)
- Drive to station at position 60, refuel 40 liters (total: 40)
- Reach target at position 100
```

**Constraints:**
- 1 ≤ target, startFuel ≤ 10^9
- 0 ≤ stations.length ≤ 500
- 0 ≤ position[i] < target
- 1 ≤ fuel[i] < 10^9

**Hints:**
1. Use a max heap to keep track of fuel capacities of passed stations
2. Drive as far as possible with current fuel
3. When can't reach next station/target, refuel from the station with most fuel passed so far

**Test Cases:**
```
Test 1: target=1, startFuel=1, stations=[] → Expected: 0
Test 2: target=100, startFuel=1, stations=[[10,100]] → Expected: -1
```

**Practice Platform:** LeetCode #871

---

### Advanced Level

#### Problem 12: Super Ugly Number
**Difficulty:** Advanced

**Problem Statement:**
A super ugly number is a positive integer whose prime factors are in the array primes. Given an integer n and an array of integers primes, return the nth super ugly number.

**Example:**
```
Input: n = 12, primes = [2,7,13,19]
Output: 32
Explanation: [1,2,4,7,8,13,14,16,19,26,28,32] are first 12 super ugly numbers
```

**Constraints:**
- 1 ≤ n ≤ 10^5
- 1 ≤ primes.length ≤ 100
- 2 ≤ primes[i] ≤ 1000

**Hints:**
1. Use a min heap to generate ugly numbers in sorted order
2. Start with 1, multiply with each prime and add to heap
3. Use a set to avoid duplicates

**Test Cases:**
```
Test 1: n=1, primes=[2,3,5] → Expected: 1
Test 2: n=10, primes=[2,3,5] → Expected: 12
```

**Practice Platform:** LeetCode #313

---

#### Problem 13: Find K Pairs with Smallest Sums
**Difficulty:** Advanced

**Problem Statement:**
You are given two integer arrays nums1 and nums2 sorted in ascending order and an integer k. Define a pair (u, v) which consists of one element from nums1 and one element from nums2. Return the k pairs (u1,v1), (u2,v2), ..., (uk,vk) with the smallest sums.

**Example:**
```
Input: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
Output: [[1,2],[1,4],[1,6]]
Explanation: First 3 pairs: [1,2], [1,4], [1,6]
```

**Constraints:**
- 1 ≤ nums1.length, nums2.length ≤ 10^5
- -10^9 ≤ nums1[i], nums2[i] ≤ 10^9
- 1 ≤ k ≤ 10^4

**Hints:**
1. Use min heap to keep pairs with smallest sums
2. Start with pairs of first element of nums1 with all elements of nums2
3. When extracting a pair, add the next pair with incremented index from nums1

**Test Cases:**
```
Test 1: nums1=[1,2], nums2=[3,4], k=4 → Expected: [[1,3],[1,4],[2,3],[2,4]]
Test 2: nums1=[1,1,2], nums2=[1,2,3], k=10 → Expected: all 9 pairs
```

**Practice Platform:** LeetCode #373

---

### Master Level

#### Problem 14: The Skyline Problem
**Difficulty:** Master

**Problem Statement:**
Given the locations and heights of buildings, return the skyline formed by these buildings collectively. A skyline is a list of "key points" where the height changes.

**Example:**
```
Input: buildings = [[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]
Output: [[2,10],[3,15],[7,12],[12,0],[15,10],[20,8],[24,0]]
```

**Constraints:**
- 1 ≤ buildings.length ≤ 10^4
- 0 ≤ left[i] < right[i] ≤ 2^31 - 1
- 1 ≤ height[i] ≤ 2^31 - 1

**Hints:**
1. Create events for building start and end points
2. Use a max heap to track active building heights
3. When height changes at a position, add a key point

**Test Cases:**
```
Test 1: [[0,2,3],[2,5,3]] → Expected: [[0,3],[5,0]]
Test 2: [[1,2,1],[1,2,2],[1,2,3]] → Expected: [[1,3],[2,0]]
```

**Practice Platform:** LeetCode #218

---

## Related Topics

### Prerequisites:
- Arrays
- Binary Trees
- Recursion
- Complexity Analysis

### Related Data Structures:
- Priority Queues
- Binary Search Trees
- Balanced Trees (AVL, Red-Black)

### Related Algorithms:
- Heap Sort
- Selection Algorithms
- Graph Algorithms (Dijkstra's, Prim's)

### Next Topics to Study:
- Disjoint Set (Union-Find)
- Segment Trees
- Fenwick Trees (Binary Indexed Trees)

---

## Summary

Heaps are powerful data structures for:
- ✅ Priority queue implementation
- ✅ Finding kth largest/smallest elements
- ✅ Merging sorted sequences
- ✅ Efficient sorting (Heap Sort)
- ✅ Graph algorithms (Dijkstra's, Prim's)

**Key Takeaways:**
1. Heaps provide O(1) access to min/max element
2. Insertion and deletion are O(log n)
3. Building a heap from array is O(n)
4. Not suitable for searching arbitrary elements

---

**Happy Learning! 🎓**

*Master heaps, and you'll unlock efficient solutions to numerous algorithmic challenges!*
