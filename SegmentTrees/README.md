# Segment Trees - Complete Guide

## Introduction
**Segment Tree** is a tree data structure for storing intervals or segments. It allows querying which segments contain a given point efficiently.

## Key Operations
- **Build:** O(n)
- **Query (Range):** O(log n)
- **Update:** O(log n)

## When to Use
✅ Range queries (sum, min, max, GCD)
✅ Range updates
✅ Dynamic arrays
❌ Simple array lookups (use arrays)

## Core Concept
```
Divide array into segments
Each node represents a segment
Leaf nodes represent single elements
Internal nodes represent merged segments
```

## Implementation Template
```
Class SegmentTree:
    Array tree
    Integer n

    Function build(arr, node, start, end):
        if start == end:
            tree[node] = arr[start]
        else:
            mid = (start + end) / 2
            build(arr, 2*node, start, mid)
            build(arr, 2*node+1, mid+1, end)
            tree[node] = tree[2*node] + tree[2*node+1]

    Function query(node, start, end, l, r):
        if r < start or end < l:
            return 0
        if l <= start and end <= r:
            return tree[node]
        mid = (start + end) / 2
        return query(2*node, start, mid, l, r) + query(2*node+1, mid+1, end, l, r)

    Function update(node, start, end, idx, val):
        if start == end:
            tree[node] = val
        else:
            mid = (start + end) / 2
            if idx <= mid:
                update(2*node, start, mid, idx, val)
            else:
                update(2*node+1, mid+1, end, idx, val)
            tree[node] = tree[2*node] + tree[2*node+1]
```

## Common Problems
- Range Sum Query - LeetCode #307
- Range Minimum Query
- Count of Range Sum - LeetCode #327
- Lazy Propagation problems

## Advanced Topics
- Lazy Propagation
- Persistent Segment Trees
- 2D Segment Trees

## Related Topics
- Fenwick Trees (Binary Indexed Trees)
- Sparse Tables
- Square Root Decomposition

**Happy Learning! 🎓**
