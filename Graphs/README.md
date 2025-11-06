# Graphs - Complete Guide

## Table of Contents
1. [Introduction](#introduction)
2. [What is a Graph?](#what-is-a-graph)
3. [Graph Terminology](#graph-terminology)
4. [Types of Graphs](#types-of-graphs)
5. [Graph Representations](#graph-representations)
6. [Implementation Guidelines](#implementation-guidelines)
7. [Time & Space Complexity](#time--space-complexity)
8. [When to Use Graphs](#when-to-use-graphs)
9. [Real-World Applications](#real-world-applications)
10. [Problem Statements](#problem-statements)
11. [Related Topics](#related-topics)

---

## Introduction

A **Graph** is a non-linear data structure consisting of **vertices (nodes)** and **edges** that connect pairs of vertices. Graphs are used to model pairwise relations between objects and are fundamental in computer science for solving complex problems involving networks, paths, and connections.

---

## What is a Graph?

A graph G is defined as G = (V, E) where:
- **V** is a set of vertices (nodes)
- **E** is a set of edges (connections between vertices)

### Key Characteristics:
- **Non-linear** - No hierarchical parent-child relationship
- **Flexible connections** - Any vertex can connect to any other
- **Can represent complex relationships** - Social networks, maps, dependencies
- **Can be weighted or unweighted** - Edges may have costs/distances
- **Can be directed or undirected** - Edges may have direction

---

## Graph Terminology

### Basic Terms:

**Vertex (Node):** A fundamental unit representing an entity
**Edge:** Connection between two vertices
**Adjacent:** Two vertices connected by an edge are adjacent
**Degree:** Number of edges connected to a vertex
  - **In-degree:** Number of incoming edges (directed graphs)
  - **Out-degree:** Number of outgoing edges (directed graphs)

**Path:** Sequence of vertices where each adjacent pair is connected by an edge
**Cycle:** Path that starts and ends at the same vertex
**Connected Graph:** Every vertex is reachable from every other vertex
**Disconnected Graph:** At least one vertex is not reachable from others

**Weighted Graph:** Edges have associated weights/costs
**Unweighted Graph:** All edges are equal

**Dense Graph:** Many edges (E ≈ V²)
**Sparse Graph:** Few edges (E << V²)

**Tree:** Connected acyclic undirected graph
**Forest:** Collection of disconnected trees

---

## Types of Graphs

### 1. Undirected Graph
Edges have no direction; connection is bidirectional.

```
Visual:
    A --- B
    |     |
    C --- D

Edges: {A-B, A-C, B-D, C-D}
```

### 2. Directed Graph (Digraph)
Edges have direction; A→B doesn't imply B→A.

```
Visual:
    A --> B
    ↑     ↓
    C <-- D

Edges: {A→B, B→D, D→C, C→A}
```

### 3. Weighted Graph
Edges have associated weights/costs.

```
Visual:
      5
    A --- B
    |3    |2
    C --- D
      4

Edges with weights: {(A,B,5), (A,C,3), (B,D,2), (C,D,4)}
```

### 4. Unweighted Graph
All edges have equal weight (or weight = 1).

### 5. Cyclic Graph
Contains at least one cycle.

```
    A → B
    ↑   ↓
    C ← D   (cycle: A→B→D→C→A)
```

### 6. Acyclic Graph
Contains no cycles.
- **DAG (Directed Acyclic Graph):** Important for task scheduling, dependency resolution

### 7. Complete Graph
Every pair of vertices is connected.

```
For 4 vertices (K₄):
    A --- B
    |\ /|
    | X |
    |/ \|
    C --- D

Total edges = n(n-1)/2 = 6 for undirected
```

### 8. Bipartite Graph
Vertices can be divided into two sets where edges only connect vertices from different sets.

```
Set 1: {A, B}    Set 2: {X, Y}
    A --- X
    |  X  |
    B --- Y
```

### 9. Multi-Graph
Multiple edges between same pair of vertices allowed.

### 10. Self-Loop Graph
Vertex has edge to itself.

---

## Graph Representations

### 1. Adjacency Matrix

2D array where matrix[i][j] represents edge from vertex i to vertex j.

**Undirected Graph Example:**
```
Graph:
    0 --- 1
    |     |
    2 --- 3

Adjacency Matrix:
    0  1  2  3
0 [ 0  1  1  0 ]
1 [ 1  0  0  1 ]
2 [ 1  0  0  1 ]
3 [ 0  1  1  0 ]

matrix[i][j] = 1 if edge exists, 0 otherwise
```

**Directed Weighted Graph Example:**
```
Graph:
    0 --5--> 1
    ↓        ↓
    3        2

Adjacency Matrix:
    0  1  2  3
0 [ 0  5  0  3 ]
1 [ 0  0  2  0 ]
2 [ 0  0  0  0 ]
3 [ 0  0  0  0 ]

matrix[i][j] = weight if edge exists, 0 or ∞ otherwise
```

**Pros:**
- ✅ O(1) edge lookup
- ✅ Simple implementation
- ✅ Good for dense graphs

**Cons:**
- ❌ O(V²) space (wastes space for sparse graphs)
- ❌ O(V) to iterate over neighbors
- ❌ Adding vertex is expensive

### 2. Adjacency List

Array of lists where each index represents a vertex and contains list of its neighbors.

**Undirected Graph Example:**
```
Graph:
    0 --- 1
    |     |
    2 --- 3

Adjacency List:
0: [1, 2]
1: [0, 3]
2: [0, 3]
3: [1, 2]
```

**Directed Weighted Graph Example:**
```
Graph:
    0 --5--> 1
    ↓        ↓
    3        2

Adjacency List:
0: [(1,5), (3,3)]
1: [(2,2)]
2: []
3: []
```

**Pros:**
- ✅ Space efficient for sparse graphs: O(V + E)
- ✅ Easy to iterate over neighbors
- ✅ Easy to add vertices

**Cons:**
- ❌ O(V) edge lookup in worst case
- ❌ Slightly more complex implementation

### 3. Edge List

List of all edges in the graph.

```
Graph:
    0 --- 1
    |     |
    2 --- 3

Edge List:
[(0,1), (0,2), (1,3), (2,3)]

For weighted:
[(0,1,5), (0,2,3), (1,3,2), (2,3,4)]
```

**Pros:**
- ✅ Space efficient: O(E)
- ✅ Simple for some algorithms (Kruskal's MST)

**Cons:**
- ❌ O(E) to find if edge exists
- ❌ O(E) to find all neighbors

---

## Implementation Guidelines

### Adjacency List Implementation (Most Common)

```
Class Graph:
    Integer num_vertices
    Array<List<Integer>> adj_list  // for unweighted
    // OR
    Array<List<Pair<Integer, Integer>>> adj_list  // for weighted (neighbor, weight)
    Boolean is_directed

    Function Constructor(vertices, directed):
        num_vertices = vertices
        is_directed = directed
        adj_list = array of empty lists of size vertices

    Function addEdge(u, v, weight = 1):
        adj_list[u].append((v, weight))

        if not is_directed:
            adj_list[v].append((u, weight))

    Function removeEdge(u, v):
        Remove v from adj_list[u]

        if not is_directed:
            Remove u from adj_list[v]

    Function hasEdge(u, v):
        return v in adj_list[u]

    Function getNeighbors(u):
        return adj_list[u]

    Function getDegree(u):
        if is_directed:
            in_degree = count vertices with edge to u
            out_degree = length of adj_list[u]
            return (in_degree, out_degree)
        else:
            return length of adj_list[u]
```

### Adjacency Matrix Implementation

```
Class Graph:
    Integer num_vertices
    2D Array matrix
    Boolean is_directed

    Function Constructor(vertices, directed):
        num_vertices = vertices
        is_directed = directed
        matrix = 2D array of size vertices × vertices, initialized with 0 or ∞

    Function addEdge(u, v, weight = 1):
        matrix[u][v] = weight

        if not is_directed:
            matrix[v][u] = weight

    Function removeEdge(u, v):
        matrix[u][v] = 0 or ∞

        if not is_directed:
            matrix[v][u] = 0 or ∞

    Function hasEdge(u, v):
        return matrix[u][v] != 0 and matrix[u][v] != ∞

    Function getNeighbors(u):
        neighbors = []
        for v from 0 to num_vertices - 1:
            if matrix[u][v] != 0 and matrix[u][v] != ∞:
                neighbors.append((v, matrix[u][v]))
        return neighbors
```

---

## Time & Space Complexity

| Operation | Adjacency List | Adjacency Matrix | Edge List |
|-----------|---------------|------------------|-----------|
| **Space** | O(V + E) | O(V²) | O(E) |
| **Add Vertex** | O(1) | O(V²) | O(1) |
| **Add Edge** | O(1) | O(1) | O(1) |
| **Remove Edge** | O(E) | O(1) | O(E) |
| **Check if edge exists** | O(V) worst | O(1) | O(E) |
| **Find all neighbors** | O(degree) | O(V) | O(E) |

**V** = number of vertices, **E** = number of edges

---

## When to Use Graphs

### ✅ Use Graphs When:
- Modeling networks (social, computer, transportation)
- Finding paths or shortest paths
- Detecting cycles
- Representing dependencies (build systems, course prerequisites)
- Modeling state transitions
- Web crawling and page ranking
- Network flow problems
- Game trees and AI

### ❌ Avoid Graphs When:
- Simple linear relationships (use array/linked list)
- Hierarchical relationships (use tree)
- Only need key-value lookup (use hash table)

---

## Real-World Applications

### 1. Social Networks
- **Vertices:** Users
- **Edges:** Friendships/connections
- **Problems:** Friend recommendations, community detection

### 2. Maps and Navigation
- **Vertices:** Locations/intersections
- **Edges:** Roads (weighted by distance/time)
- **Problems:** Shortest path, route optimization

### 3. Computer Networks
- **Vertices:** Routers/computers
- **Edges:** Network connections
- **Problems:** Routing, network topology

### 4. Web Pages
- **Vertices:** Web pages
- **Edges:** Hyperlinks
- **Problems:** PageRank, web crawling

### 5. Dependency Resolution
- **Vertices:** Tasks/packages/courses
- **Edges:** Dependencies
- **Problems:** Build order, course schedule

### 6. Recommendation Systems
- **Vertices:** Users, products
- **Edges:** Interactions
- **Problems:** Collaborative filtering

### 7. Biology
- **Vertices:** Molecules, species
- **Edges:** Interactions, evolutionary relationships
- **Problems:** Protein interaction networks, phylogenetic trees

---

## Problem Statements

### Beginner Level

#### Problem 1: Find if Path Exists in Graph
**Difficulty:** Beginner

**Problem Statement:**
There is a bi-directional graph with n vertices numbered from 0 to n-1. Given an edge list and two vertices source and destination, determine if there is a valid path from source to destination.

**Example:**
```
Input: n = 3, edges = [[0,1],[1,2],[2,0]], source = 0, destination = 2
Output: true
Explanation: Path: 0 → 1 → 2

Input: n = 6, edges = [[0,1],[0,2],[3,5],[5,4],[4,3]], source = 0, destination = 5
Output: false
```

**Constraints:**
- 1 ≤ n ≤ 2 * 10^5
- 0 ≤ edges.length ≤ 2 * 10^5
- 0 ≤ source, destination < n

**Hints:**
1. Build adjacency list from edge list
2. Use BFS or DFS starting from source
3. Check if destination is reachable

**Test Cases:**
```
Test 1: n=1, edges=[], source=0, destination=0 → Expected: true
Test 2: n=2, edges=[[0,1]], source=0, destination=1 → Expected: true
Test 3: n=2, edges=[], source=0, destination=1 → Expected: false
```

**Practice Platform:** LeetCode #1971

---

#### Problem 2: Number of Connected Components
**Difficulty:** Beginner

**Problem Statement:**
Given n nodes labeled from 0 to n-1 and a list of undirected edges, count the number of connected components in the undirected graph.

**Example:**
```
Input: n = 5, edges = [[0,1],[1,2],[3,4]]
Output: 2
Explanation: Components: {0,1,2} and {3,4}

Input: n = 5, edges = [[0,1],[1,2],[2,3],[3,4]]
Output: 1
```

**Constraints:**
- 1 ≤ n ≤ 2000
- 0 ≤ edges.length ≤ 5000

**Hints:**
1. Use DFS/BFS or Union-Find
2. For each unvisited node, run DFS and increment component count
3. Mark all nodes in same component as visited

**Test Cases:**
```
Test 1: n=1, edges=[] → Expected: 1
Test 2: n=3, edges=[] → Expected: 3
Test 3: n=4, edges=[[0,1],[2,3]] → Expected: 2
```

**Practice Platform:** LeetCode #323 (Premium)

---

### Easy Level

#### Problem 3: Clone Graph
**Difficulty:** Easy

**Problem Statement:**
Given a reference of a node in a connected undirected graph, return a deep copy (clone) of the graph. Each node contains a value and a list of its neighbors.

**Example:**
```
Input: adjList = [[2,4],[1,3],[2,4],[1,3]]
Output: [[2,4],[1,3],[2,4],[1,3]]
Explanation: 4 nodes graph where:
Node 1 is connected to nodes 2 and 4
Node 2 is connected to nodes 1 and 3
Node 3 is connected to nodes 2 and 4
Node 4 is connected to nodes 1 and 3
```

**Constraints:**
- Number of nodes is between 0 and 100
- 1 ≤ Node.val ≤ 100
- Node.val is unique for each node

**Hints:**
1. Use DFS/BFS with a hash map
2. Hash map stores mapping from original node to cloned node
3. For each node, clone it and recursively clone its neighbors

**Test Cases:**
```
Test 1: [[]] → Expected: [[]] (single node, no neighbors)
Test 2: [] → Expected: [] (empty graph)
```

**Practice Platform:** LeetCode #133

---

#### Problem 4: All Paths From Source to Target
**Difficulty:** Easy

**Problem Statement:**
Given a directed acyclic graph (DAG) of n nodes labeled from 0 to n-1, find all possible paths from node 0 to node n-1 and return them in any order.

**Example:**
```
Input: graph = [[1,2],[3],[3],[]]
Output: [[0,1,3],[0,2,3]]
Explanation:
0 → 1 → 3
0 → 2 → 3

Input: graph = [[4,3,1],[3,2,4],[3],[4],[]]
Output: [[0,4],[0,3,4],[0,1,3,4],[0,1,2,3,4],[0,1,4]]
```

**Constraints:**
- n == graph.length
- 2 ≤ n ≤ 15
- 0 ≤ graph[i][j] < n
- graph[i][j] != i (no self-loops)
- Input is a DAG

**Hints:**
1. Use DFS with backtracking
2. Keep track of current path
3. When reaching target node, add current path to result

**Test Cases:**
```
Test 1: [[1],[]] → Expected: [[0,1]]
Test 2: [[1,2],[3],[3],[]] → Expected: [[0,1,3],[0,2,3]]
```

**Practice Platform:** LeetCode #797

---

### Medium Level

#### Problem 5: Course Schedule
**Difficulty:** Medium

**Problem Statement:**
There are numCourses courses labeled from 0 to numCourses-1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first before taking course ai. Return true if you can finish all courses, otherwise return false.

**Example:**
```
Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: Take course 0 first, then course 1

Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: Circular dependency
```

**Constraints:**
- 1 ≤ numCourses ≤ 2000
- 0 ≤ prerequisites.length ≤ 5000
- prerequisites[i].length == 2
- 0 ≤ ai, bi < numCourses

**Hints:**
1. This is cycle detection in directed graph
2. Use DFS with three states: unvisited, visiting, visited
3. If you visit a node that's already in "visiting" state, there's a cycle

**Test Cases:**
```
Test 1: numCourses=1, prerequisites=[] → Expected: true
Test 2: numCourses=3, prerequisites=[[0,1],[1,2],[2,0]] → Expected: false
```

**Practice Platform:** LeetCode #207

---

#### Problem 6: Number of Islands
**Difficulty:** Medium

**Problem Statement:**
Given an m x n 2D binary grid which represents a map of '1's (land) and '0's (water), return the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.

**Example:**
```
Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1

Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3
```

**Constraints:**
- m == grid.length
- n == grid[i].length
- 1 ≤ m, n ≤ 300
- grid[i][j] is '0' or '1'

**Hints:**
1. Treat grid as implicit graph
2. For each unvisited land cell, run DFS/BFS
3. Mark all connected land cells as visited
4. Increment island count for each DFS/BFS call

**Test Cases:**
```
Test 1: [["1"]] → Expected: 1
Test 2: [["0"]] → Expected: 0
Test 3: [["1","0"],["0","1"]] → Expected: 2
```

**Practice Platform:** LeetCode #200

---

#### Problem 7: Pacific Atlantic Water Flow
**Difficulty:** Medium

**Problem Statement:**
Given an m x n matrix of non-negative integers representing heights, find all cells where water can flow to both Pacific and Atlantic oceans. Water flows from a cell to adjacent cells with height less than or equal to current cell.

**Example:**
```
Input: heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
```

**Constraints:**
- m == heights.length
- n == heights[i].length
- 1 ≤ m, n ≤ 200
- 0 ≤ heights[i][j] ≤ 10^5

**Hints:**
1. Run DFS/BFS from Pacific border cells
2. Run DFS/BFS from Atlantic border cells
3. Find cells reachable from both oceans

**Test Cases:**
```
Test 1: [[1]] → Expected: [[0,0]]
Test 2: [[1,2],[2,1]] → Expected: [[0,0],[0,1],[1,0],[1,1]]
```

**Practice Platform:** LeetCode #417

---

### Hard Level

#### Problem 8: Word Ladder
**Difficulty:** Hard

**Problem Statement:**
Given two words beginWord and endWord, and a dictionary wordList, return the length of shortest transformation sequence from beginWord to endWord such that:
- Only one letter can be changed at a time
- Each transformed word must exist in wordList

**Example:**
```
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: 5
Explanation: hit → hot → dot → dog → cog

Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
Output: 0
Explanation: endWord "cog" not in wordList
```

**Constraints:**
- 1 ≤ beginWord.length ≤ 10
- endWord.length == beginWord.length
- 1 ≤ wordList.length ≤ 5000
- All words have same length
- All words contain only lowercase English letters

**Hints:**
1. Model as graph: words are vertices, edges connect words differing by 1 letter
2. Use BFS for shortest path
3. Pre-process word list for efficient neighbor finding

**Test Cases:**
```
Test 1: beginWord="a", endWord="c", wordList=["a","b","c"] → Expected: 2
Test 2: beginWord="hot", endWord="dog", wordList=["hot","dog"] → Expected: 0
```

**Practice Platform:** LeetCode #127

---

#### Problem 9: Alien Dictionary
**Difficulty:** Hard

**Problem Statement:**
Given a sorted dictionary of an alien language, derive the order of characters in this language. If the order is invalid, return empty string.

**Example:**
```
Input: words = ["wrt","wrf","er","ett","rftt"]
Output: "wertf"

Input: words = ["z","x"]
Output: "zx"

Input: words = ["z","x","z"]
Output: ""
Explanation: Invalid ordering
```

**Constraints:**
- 1 ≤ words.length ≤ 100
- 1 ≤ words[i].length ≤ 100
- words[i] consists of only lowercase English letters

**Hints:**
1. Build directed graph from character order constraints
2. Use topological sort to find character order
3. Detect cycles (invalid ordering)

**Test Cases:**
```
Test 1: ["z","z"] → Expected: "z"
Test 2: ["abc","ab"] → Expected: "" (invalid)
```

**Practice Platform:** LeetCode #269 (Premium)

---

#### Problem 10: Minimum Height Trees
**Difficulty:** Hard

**Problem Statement:**
A tree is an undirected graph where any two vertices are connected by exactly one path. Given n nodes and edges, find all minimum height trees and return their root labels.

**Example:**
```
Input: n = 4, edges = [[1,0],[1,2],[1,3]]
Output: [1]

Input: n = 6, edges = [[3,0],[3,1],[3,2],[3,4],[5,4]]
Output: [3,4]
```

**Constraints:**
- 1 ≤ n ≤ 2 * 10^4
- edges.length == n - 1
- 0 ≤ ai, bi < n

**Hints:**
1. Root of MHT is at the "center" of the graph
2. Repeatedly remove leaf nodes (degree 1)
3. Remaining nodes are MHT roots

**Test Cases:**
```
Test 1: n=1, edges=[] → Expected: [0]
Test 2: n=2, edges=[[0,1]] → Expected: [0,1]
```

**Practice Platform:** LeetCode #310

---

### Expert Level

#### Problem 11: Critical Connections in a Network
**Difficulty:** Expert

**Problem Statement:**
There are n servers numbered from 0 to n-1 connected by undirected connections. A connection is critical if removing it increases the number of connected components. Return all critical connections.

**Example:**
```
Input: n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
Output: [[1,3]]
Explanation: [[3,1]] is also accepted
```

**Constraints:**
- 1 ≤ n ≤ 10^5
- n - 1 ≤ connections.length ≤ 10^5
- connections[i][0] != connections[i][1]
- No repeated connections

**Hints:**
1. Find bridges in graph (Tarjan's algorithm)
2. Use DFS with discovery time and low time
3. Edge (u,v) is bridge if low[v] > discovery[u]

**Test Cases:**
```
Test 1: n=2, connections=[[0,1]] → Expected: [[0,1]]
Test 2: n=3, connections=[[0,1],[1,2],[0,2]] → Expected: [] (cycle, no bridges)
```

**Practice Platform:** LeetCode #1192

---

#### Problem 12: Graph Valid Tree
**Difficulty:** Expert

**Problem Statement:**
Given n nodes and a list of undirected edges, determine if these edges make up a valid tree.

**Example:**
```
Input: n = 5, edges = [[0,1],[0,2],[0,3],[1,4]]
Output: true

Input: n = 5, edges = [[0,1],[1,2],[2,3],[1,3],[1,4]]
Output: false
```

**Constraints:**
- 1 ≤ n ≤ 2000
- 0 ≤ edges.length ≤ 5000

**Hints:**
1. Tree must have exactly n-1 edges
2. Tree must be connected
3. Tree must have no cycles

**Test Cases:**
```
Test 1: n=1, edges=[] → Expected: true
Test 2: n=2, edges=[[0,1],[1,0]] → Expected: false (duplicate edge)
```

**Practice Platform:** LeetCode #261 (Premium)

---

## Related Topics

### Prerequisites:
- Arrays
- Linked Lists
- Queue (for BFS)
- Stack (for DFS)
- Recursion

### Related Algorithms (covered in GraphAlgorithms/):
- BFS and DFS
- Dijkstra's Algorithm
- Bellman-Ford Algorithm
- Floyd-Warshall Algorithm
- Kruskal's and Prim's Algorithm
- Topological Sort
- Tarjan's Algorithm

### Next Topics to Study:
- Disjoint Set (Union-Find)
- Minimum Spanning Trees
- Shortest Path Algorithms
- Network Flow

---

## Summary

Graphs are versatile for:
- ✅ Modeling complex relationships
- ✅ Network and connectivity problems
- ✅ Path finding and optimization
- ✅ Dependency resolution
- ✅ State space exploration

**Key Takeaways:**
1. Choose representation based on density (adjacency list for sparse, matrix for dense)
2. BFS for shortest path in unweighted graphs
3. DFS for cycle detection, topological sort
4. Many real-world problems map to graph problems

---

**Happy Learning! 🎓**

*Master graphs, and you'll understand the connections in everything!*
