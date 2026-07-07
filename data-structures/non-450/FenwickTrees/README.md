# Fenwick Trees (Binary Indexed Trees) - Complete Guide

## Introduction
**Fenwick Tree** or **Binary Indexed Tree (BIT)** is a data structure that can efficiently update elements and calculate prefix sums in O(log n) time.

## Key Operations
- **Update:** O(log n)
- **Prefix Sum Query:** O(log n)
- **Space:** O(n)

## When to Use
✅ Prefix sum queries with updates
✅ Frequency counting
✅ Inversion count
❌ Range queries other than sum (use Segment Tree)

## Core Concept
```
Uses binary representation of indices
Parent-child relationship based on bits
Faster and more space-efficient than Segment Tree for specific use cases
```

## Implementation Template
```
Class FenwickTree:
    Array tree
    Integer n

    Function Constructor(size):
        n = size
        tree = array of size n+1, initialized to 0

    Function update(index, delta):
        index++  // 1-indexed
        while index <= n:
            tree[index] += delta
            index += index & (-index)

    Function prefixSum(index):
        index++  // 1-indexed
        sum = 0
        while index > 0:
            sum += tree[index]
            index -= index & (-index)
        return sum

    Function rangeSum(left, right):
        return prefixSum(right) - prefixSum(left - 1)
```

## Key Insight
```
index & (-index) gives the last set bit
This determines parent-child relationships
```

## Common Problems
- Range Sum Query Mutable - LeetCode #307
- Count of Smaller Numbers After Self - LeetCode #315
- Reverse Pairs - LeetCode #493
- Range Sum Query 2D Mutable - LeetCode #308

## Fenwick Tree vs Segment Tree

| Feature | Fenwick Tree | Segment Tree |
|---------|-------------|--------------|
| **Implementation** | Simpler | More complex |
| **Space** | O(n) | O(4n) |
| **Operations** | Prefix sum | Any associative operation |
| **Range Update** | Harder | Easier (lazy prop) |

## Advanced Topics
- 2D Fenwick Tree
- Range Update Point Query
- Range Update Range Query

## Related Topics
- Segment Trees
- Prefix Sum Arrays
- Difference Arrays

**Happy Learning! 🎓**
