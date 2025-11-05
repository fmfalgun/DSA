# Shortest Path Algorithms

## Dijkstra's Algorithm
- **Time:** O((V + E) log V) with priority queue
- **Use:** Shortest path with non-negative weights
- **Problem:** Network Delay Time - LeetCode #743

## Bellman-Ford Algorithm
- **Time:** O(V × E)
- **Use:** Shortest path with negative weights, detects negative cycles
- **Problem:** Cheapest Flights Within K Stops - LeetCode #787

## Floyd-Warshall Algorithm
- **Time:** O(V³)
- **Use:** All-pairs shortest paths
- **Problem:** Find the City - LeetCode #1334

## A* Algorithm
- **Use:** Pathfinding with heuristic
- **Application:** Game development, robotics

**See main [Graphs README](../../Graphs/) for implementations.**
