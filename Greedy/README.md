# Greedy Algorithms - Complete Guide

## Introduction

**Greedy Algorithm** is an algorithmic paradigm that makes the locally optimal choice at each step with the hope of finding a global optimum. It never reconsiders its choices.

## What is a Greedy Algorithm?

A greedy algorithm:
- Makes the best choice at each step
- Never looks back or reconsiders
- Hope local optimums lead to global optimum
- Much faster than dynamic programming when applicable

**Key Insight:** Greedy works when problem exhibits the **greedy choice property** and **optimal substructure**.

## Greedy vs Dynamic Programming

| Greedy | Dynamic Programming |
|--------|-------------------|
| Makes immediate best choice | Considers all choices |
| Never reconsiders | Stores solutions to subproblems |
| O(n) or O(n log n) typically | O(n²) or worse typically |
| Works for specific problems | Works for broader class |
| May not find optimal solution | Always finds optimal solution |

## When Does Greedy Work?

### 1. Greedy Choice Property
A global optimum can be arrived at by selecting a local optimum.

### 2. Optimal Substructure
Optimal solution contains optimal solutions to subproblems.

### Classic Greedy Problems:
✅ Activity Selection
✅ Huffman Coding
✅ Fractional Knapsack
✅ Minimum Spanning Tree (Prim's, Kruskal's)
✅ Dijkstra's Shortest Path
✅ Job Sequencing
✅ Coin Change (specific coin systems)

### Where Greedy Fails:
❌ 0/1 Knapsack (need DP)
❌ Longest Common Subsequence (need DP)
❌ Some graph problems with negative weights

## Common Greedy Patterns

### 1. Sorting First
Many greedy problems require sorting first.

**Example:** Activity Selection
```
Sort activities by finish time
Select earliest finishing non-overlapping activity
```

### 2. Priority Queue/Heap
Use heap to always access best element.

**Example:** Huffman Coding
```
Build tree by always combining two smallest frequency nodes
```

### 3. Two Pointers
Greedily move pointers based on condition.

**Example:** Container With Most Water
```
Move pointer with smaller height inward
```

## Classic Greedy Problems

### 1. Activity Selection

**Problem:** Select maximum number of non-overlapping activities.

**Greedy Strategy:** Always pick activity that finishes earliest.

```
Function activitySelection(activities):
    Sort activities by finish time

    count = 0
    lastFinishTime = -infinity

    for each activity in activities:
        if activity.start >= lastFinishTime:
            count++
            lastFinishTime = activity.finish

    return count
```

**Time:** O(n log n)

### 2. Fractional Knapsack

**Problem:** Fill knapsack to maximize value (can take fractions).

**Greedy Strategy:** Take items with highest value/weight ratio first.

```
Function fractionalKnapsack(items, capacity):
    Sort items by value/weight ratio (descending)

    totalValue = 0

    for each item in items:
        if capacity >= item.weight:
            totalValue += item.value
            capacity -= item.weight
        else:
            totalValue += item.value * (capacity / item.weight)
            break

    return totalValue
```

**Time:** O(n log n)

### 3. Huffman Coding

**Problem:** Optimal prefix-free binary code for data compression.

**Greedy Strategy:** Build tree by repeatedly combining two nodes with smallest frequencies.

```
Function huffmanCoding(frequencies):
    Create min heap with all characters and frequencies

    while heap.size() > 1:
        left = heap.extractMin()
        right = heap.extractMin()

        newNode = create node with frequency left.freq + right.freq
        newNode.left = left
        newNode.right = right

        heap.insert(newNode)

    return heap.top()  // Root of Huffman tree
```

**Time:** O(n log n)

### 4. Job Sequencing

**Problem:** Schedule jobs with deadlines to maximize profit.

**Greedy Strategy:** Sort by profit, assign to latest available slot.

```
Function jobSequencing(jobs):
    Sort jobs by profit (descending)

    Find maximum deadline
    Create slots array

    for each job in jobs:
        for slot from job.deadline down to 1:
            if slots[slot] is empty:
                slots[slot] = job
                break

    return total profit
```

**Time:** O(n²) or O(n log n) with disjoint set

## Problem Statements

### Beginner: Assign Cookies
**Problem:** Assign cookies to children to maximize satisfied children.
**Greedy Strategy:** Sort both arrays, assign smallest sufficient cookie.
**Constraints:** 1 ≤ g.length, s.length ≤ 3×10⁴
**Platform:** LeetCode #455

### Easy: Jump Game
**Problem:** Determine if you can reach last index from first.
**Greedy Strategy:** Track maximum reachable index.
**Hints:** Keep updating max reach at each step.
**Platform:** LeetCode #55

### Easy: Best Time to Buy and Sell Stock II
**Problem:** Maximize profit with multiple transactions.
**Greedy Strategy:** Take every profitable price increase.
**Hints:** If price[i+1] > price[i], profit = price[i+1] - price[i]
**Platform:** LeetCode #122

### Medium: Jump Game II
**Problem:** Minimum jumps to reach last index.
**Greedy Strategy:** Track current and next reachable range.
**Hints:** BFS-like greedy approach.
**Platform:** LeetCode #45

### Medium: Gas Station
**Problem:** Find starting gas station to complete circular route.
**Greedy Strategy:** If total gas ≥ total cost, solution exists.
**Hints:** Track running balance, reset start on negative.
**Platform:** LeetCode #134

### Medium: Task Scheduler
**Problem:** Minimum time to complete tasks with cooldown.
**Greedy Strategy:** Always schedule most frequent task first.
**Hints:** Use max heap, calculate idle time.
**Platform:** LeetCode #621

### Hard: Minimum Number of Refueling Stops
**Problem:** Minimum stops to reach destination.
**Greedy Strategy:** Always refuel at station with most gas when needed.
**Hints:** Use max heap for passed stations.
**Platform:** LeetCode #871

### Hard: Candy
**Problem:** Distribute candy satisfying rating constraints with minimum total.
**Greedy Strategy:** Two passes (left-to-right, right-to-left).
**Hints:** Handle increasing and decreasing sequences separately.
**Platform:** LeetCode #135

### Expert: Remove K Digits
**Problem:** Remove k digits to get smallest possible number.
**Greedy Strategy:** Remove digit if next digit is smaller.
**Hints:** Use stack to maintain increasing sequence.
**Platform:** LeetCode #402

### Expert: Create Maximum Number
**Problem:** Create largest number from two arrays by taking k digits.
**Greedy Strategy:** Find best k-digit subsequence from each array.
**Hints:** Combine greedy selection with merge.
**Platform:** LeetCode #321

## How to Identify Greedy Problems

### Signs a Problem Might Be Greedy:

1. **Keywords:**
   - "Maximum/minimum"
   - "Largest/smallest"
   - "Optimal"
   - Involves intervals/scheduling

2. **Characteristics:**
   - Local choice seems obvious
   - Sorting might help
   - Problem involves activities/jobs with deadlines
   - Optimal substructure present

3. **Test Greedy Strategy:**
   - Does making locally best choice work?
   - Try small examples
   - If greedy fails, consider DP

## Proving Greedy Correctness

### Methods:

1. **Exchange Argument:**
   - Show swapping greedy choice with another doesn't improve solution

2. **Induction:**
   - Prove greedy choice at each step leads to optimal solution

3. **Contradiction:**
   - Assume optimal solution doesn't include greedy choice
   - Show this leads to contradiction

## Real-World Applications

1. **Data Compression:** Huffman coding
2. **Operating Systems:** CPU scheduling, memory management
3. **Networking:** Routing algorithms (Dijkstra's)
4. **Resource Allocation:** Task scheduling
5. **Financial:** Stock trading strategies

## Time Complexity Patterns

Most greedy algorithms:
- **With sorting:** O(n log n)
- **With heap:** O(n log n)
- **Simple greedy:** O(n)

## Related Topics

- Dynamic Programming
- Sorting
- Heaps/Priority Queues
- Graph Algorithms

## Summary

Greedy algorithms are powerful when:
- ✅ Problem has greedy choice property
- ✅ Need fast solution
- ✅ Can prove correctness

**Key Takeaway:** Not all problems have greedy solutions. Always verify greedy approach works before implementing.

**Happy Learning! 🎓**
