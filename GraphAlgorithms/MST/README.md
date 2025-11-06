# Minimum Spanning Tree Algorithms

## Kruskal's Algorithm
- **Approach:** Sort edges, add if no cycle (use Union-Find)
- **Time:** O(E log E)
- **Problem:** Min Cost to Connect All Points - LeetCode #1584

## Prim's Algorithm
- **Approach:** Grow tree from vertex using min heap
- **Time:** O((V + E) log V)
- **Problem:** Connecting Cities With Minimum Cost - LeetCode #1135

## When to Use:
- Network design (minimize cost)
- Clustering
- Approximation algorithms

**See [Graphs README](../../Graphs/) and [DisjointSet README](../../DisjointSet/) for details.**
