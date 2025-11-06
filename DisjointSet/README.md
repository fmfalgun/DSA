# Disjoint Set (Union-Find) - Complete Guide

## Introduction

**Disjoint Set** (also called Union-Find) is a data structure that tracks elements partitioned into non-overlapping (disjoint) sets. It provides near-constant-time operations to:
- Add new sets
- Merge existing sets (Union)
- Find which set an element belongs to (Find)

## What is Disjoint Set?

A collection of sets where no item can be in more than one set. Each set has a representative element.

**Visual Example:**
```
Initial: {0} {1} {2} {3} {4} {5}

After Union(0,1):  {0,1} {2} {3} {4} {5}
After Union(2,3):  {0,1} {2,3} {4} {5}
After Union(0,2):  {0,1,2,3} {4} {5}

Find(1) → returns representative of {0,1,2,3}
Find(3) → returns same representative
Connected(1,3) → true
```

## Core Operations

### 1. MakeSet(x)
Create a new set with single element x.

### 2. Find(x)
Find representative (root) of set containing x.

### 3. Union(x, y)
Merge sets containing x and y.

## Optimizations

### 1. Union by Rank
Attach smaller tree under root of larger tree.

```
Rank = approximate depth of tree
When union: attach tree with smaller rank to larger rank
```

### 2. Path Compression
During Find, make nodes point directly to root.

```
Before Path Compression:
    5
    |
    4
    |
    3
    |
    2
    |
    1

After Find(1) with Path Compression:
      5
    / | \
   4  3  2  1
```

## Implementation (Pseudocode)

```
Class DisjointSet:
    Array parent
    Array rank

    Function MakeSet(n):
        for i from 0 to n-1:
            parent[i] = i
            rank[i] = 0

    Function Find(x):
        if parent[x] != x:
            parent[x] = Find(parent[x])  // Path compression
        return parent[x]

    Function Union(x, y):
        rootX = Find(x)
        rootY = Find(y)

        if rootX == rootY:
            return  // Already in same set

        // Union by rank
        if rank[rootX] < rank[rootY]:
            parent[rootX] = rootY
        else if rank[rootX] > rank[rootY]:
            parent[rootY] = rootX
        else:
            parent[rootY] = rootX
            rank[rootX]++

    Function Connected(x, y):
        return Find(x) == Find(y)
```

## Time Complexity

With both optimizations (union by rank + path compression):
- **MakeSet:** O(1)
- **Find:** O(α(n)) amortized
- **Union:** O(α(n)) amortized

α(n) = inverse Ackermann function ≈ O(1) for all practical values

## When to Use

✅ **Use When:**
- Detect cycles in undirected graphs
- Find connected components
- Kruskal's MST algorithm
- Network connectivity
- Percolation problems
- Image processing (connected pixels)

❌ **Avoid When:**
- Need to list all elements in a set
- Need to delete elements
- Working with directed graphs (use different algorithms)

## Real-World Applications

1. **Network Connectivity:** Check if two computers connected
2. **Social Networks:** Friend circles
3. **Image Processing:** Find connected regions
4. **Kruskal's Algorithm:** Minimum spanning tree
5. **Game Development:** Maze generation
6. **Compiler:** Variable equivalence

## Problem Statements

### Beginner: Number of Provinces
**Problem:** Find number of provinces (connected cities).
**Constraints:** 1 ≤ n ≤ 200
**Hints:** Use union-find to group connected cities
**Platform:** LeetCode #547

### Easy: Redundant Connection
**Problem:** Find edge that, if removed, makes graph a tree.
**Hints:** Use union-find to detect cycle
**Platform:** LeetCode #684

### Medium: Accounts Merge
**Problem:** Merge accounts belonging to same person.
**Hints:** Union accounts with common emails
**Platform:** LeetCode #721

### Hard: Number of Islands II
**Problem:** Count islands after each addLand operation.
**Hints:** Union adjacent land cells dynamically
**Platform:** LeetCode #305 (Premium)

### Expert: Swim in Rising Water
**Problem:** Find minimum time to swim from top-left to bottom-right.
**Hints:** Binary search + union-find or Dijkstra's
**Platform:** LeetCode #778

## Space Complexity

- **Space:** O(n) for parent and rank arrays

## Variants

1. **Union by Size:** Track size instead of rank
2. **Weighted Union-Find:** Elements have weights
3. **Persistent Union-Find:** Maintain history of operations

## Related Topics

- Graph Algorithms
- Greedy Algorithms (Kruskal's)
- Dynamic Connectivity

**Happy Learning! 🎓**
