# Topological Sorting

## Introduction
Linear ordering of vertices in DAG such that for every edge u→v, u comes before v.

## Kahn's Algorithm (BFS-based)
```
1. Find in-degree of all vertices
2. Add vertices with in-degree 0 to queue
3. Process queue, reduce in-degrees
4. If all vertices processed, return order; else cycle exists
```
**Time:** O(V + E)

## DFS-based Approach
```
1. Run DFS on all unvisited vertices
2. Add vertex to stack after visiting all descendants
3. Return reversed stack
```
**Time:** O(V + E)

## Problems:
- Course Schedule - LeetCode #207
- Course Schedule II - LeetCode #210
- Alien Dictionary - LeetCode #269
- All Ancestors of a Node in DAG - LeetCode #2192

**See [Graphs README](../../Graphs/) for detailed explanations.**
