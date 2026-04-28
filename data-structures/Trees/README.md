# Trees - Complete Guide

## Table of Contents
1. [Introduction](#introduction)
2. [What is a Tree?](#what-is-a-tree)
3. [Tree Terminology](#tree-terminology)
4. [Types of Trees](#types-of-trees)
5. [Binary Trees](#binary-trees)
6. [Binary Search Trees (BST)](#binary-search-trees-bst)
7. [Balanced Trees](#balanced-trees)
8. [Tree Traversals](#tree-traversals)
9. [Implementation Guidelines](#implementation-guidelines)
10. [When to Use Trees](#when-to-use-trees)
11. [Real-World Applications](#real-world-applications)
12. [Problem Statements](#problem-statements)
13. [Related Topics](#related-topics)

---

## Introduction

A **Tree** is a hierarchical data structure consisting of nodes connected by edges. It's one of the most important non-linear data structures in computer science, used extensively in databases, file systems, and algorithms.

---

## What is a Tree?

A tree is a collection of nodes where:
- One node is designated as the **root**
- Every other node is connected by a directed edge from exactly one other node (its **parent**)
- No cycles exist (it's a connected acyclic graph)

**Visual Example:**
```
        A (root)
       / \
      B   C
     / \   \
    D   E   F
```

---

## Tree Terminology

### Basic Terms:

**Node:** Basic unit containing data and links to other nodes
**Root:** Topmost node with no parent
**Parent:** Node with children
**Child:** Node with a parent
**Siblings:** Nodes with the same parent
**Leaf:** Node with no children
**Internal Node:** Node with at least one child
**Edge:** Connection between two nodes

### Metrics:

**Depth of Node:** Number of edges from root to node
**Height of Node:** Number of edges on longest path from node to a leaf
**Height of Tree:** Height of root node
**Level:** Depth + 1 (root is at level 1 or 0 depending on convention)
**Degree of Node:** Number of children
**Degree of Tree:** Maximum degree of any node

### Properties:

**Subtree:** Tree formed by a node and all its descendants
**Ancestor:** Node on the path from root to given node
**Descendant:** Node in subtree rooted at given node
**Path:** Sequence of nodes connected by edges
**Depth:** Maximum depth of any leaf node

---

## Types of Trees

### 1. **General Tree**
- No restriction on number of children per node

### 2. **Binary Tree**
- Each node has at most 2 children (left and right)

### 3. **Binary Search Tree (BST)**
- Binary tree with ordering property
- Left subtree values < node value < right subtree values

### 4. **Complete Binary Tree**
- All levels filled except possibly last level
- Last level filled from left to right
- Used in heaps

### 5. **Full Binary Tree**
- Every node has 0 or 2 children

### 6. **Perfect Binary Tree**
- All internal nodes have 2 children
- All leaves at same level

### 7. **Balanced Binary Tree**
- Height of left and right subtrees differ by at most 1

### 8. **AVL Tree**
- Self-balancing BST
- Balance factor ∈ {-1, 0, 1}

### 9. **Red-Black Tree**
- Self-balancing BST
- Used in many standard libraries

### 10. **B-Tree**
- Self-balancing search tree
- Optimized for disk access (databases)

### 11. **Trie (Prefix Tree)**
- Specialized tree for string storage

### 12. **Segment Tree**
- For range queries

---

## Binary Trees

### Properties:
- Maximum nodes at level h: 2^h
- Maximum nodes in tree of height h: 2^(h+1) - 1
- Minimum height with n nodes: ⌊log₂ n⌋
- Number of leaf nodes = Number of internal nodes with 2 children + 1

### Representation:

#### 1. **Struct/Class-based**
```
Class Node:
    Data data
    Node left
    Node right

    Function Constructor(value):
        data = value
        left = null
        right = null
```

#### 2. **Array-based** (for complete binary trees)
```
For node at index i:
- Left child: 2*i + 1
- Right child: 2*i + 2
- Parent: (i-1) / 2
```

---

## Binary Search Trees (BST)

### BST Property:
For every node N:
- All values in left subtree < N.data
- All values in right subtree > N.data

### Operations:

#### Search
```
Function search(root, key):
    if root is null or root.data == key:
        return root

    if key < root.data:
        return search(root.left, key)
    else:
        return search(root.right, key)
```
**Time:** O(h) where h is height

#### Insert
```
Function insert(root, key):
    if root is null:
        return new Node(key)

    if key < root.data:
        root.left = insert(root.left, key)
    else if key > root.data:
        root.right = insert(root.right, key)

    return root
```
**Time:** O(h)

#### Delete
```
Function delete(root, key):
    if root is null:
        return root

    if key < root.data:
        root.left = delete(root.left, key)
    else if key > root.data:
        root.right = delete(root.right, key)
    else:
        // Node with only one child or no child
        if root.left is null:
            return root.right
        else if root.right is null:
            return root.left

        // Node with two children
        // Get inorder successor (smallest in right subtree)
        root.data = minValue(root.right)
        root.right = delete(root.right, root.data)

    return root
```
**Time:** O(h)

---

## Balanced Trees

### Why Balance Matters:
- Unbalanced BST can degenerate to linked list (O(n) operations)
- Balanced trees guarantee O(log n) operations

### AVL Trees:
- Balance Factor = height(left subtree) - height(right subtree)
- BF ∈ {-1, 0, 1} for all nodes
- **Rotations:** Left, Right, Left-Right, Right-Left

### Red-Black Trees:
- Each node colored red or black
- Properties ensure balanced tree
- Used in C++ STL map/set, Java TreeMap

---

## Tree Traversals

### 1. **Inorder (Left, Root, Right)**
```
Function inorder(root):
    if root is null:
        return

    inorder(root.left)
    print(root.data)
    inorder(root.right)
```
**BST Inorder:** Gives sorted order
**Time:** O(n)

### 2. **Preorder (Root, Left, Right)**
```
Function preorder(root):
    if root is null:
        return

    print(root.data)
    preorder(root.left)
    preorder(root.right)
```
**Use:** Copy tree, prefix expression
**Time:** O(n)

### 3. **Postorder (Left, Right, Root)**
```
Function postorder(root):
    if root is null:
        return

    postorder(root.left)
    postorder(root.right)
    print(root.data)
```
**Use:** Delete tree, postfix expression
**Time:** O(n)

### 4. **Level Order (BFS)**
```
Function levelOrder(root):
    if root is null:
        return

    queue = new Queue()
    queue.enqueue(root)

    while not queue.isEmpty():
        node = queue.dequeue()
        print(node.data)

        if node.left:
            queue.enqueue(node.left)
        if node.right:
            queue.enqueue(node.right)
```
**Time:** O(n)
**Space:** O(w) where w is max width

---

## Implementation Guidelines

### Basic Tree Node
```
Class TreeNode:
    Integer data
    TreeNode left
    TreeNode right

    Function Constructor(value):
        data = value
        left = null
        right = null
```

### BST Operations Template
```
Class BST:
    TreeNode root

    Function insert(value):
        root = insertRec(root, value)

    Function insertRec(node, value):
        if node is null:
            return new TreeNode(value)

        if value < node.data:
            node.left = insertRec(node.left, value)
        else:
            node.right = insertRec(node.right, value)

        return node

    Function search(value):
        return searchRec(root, value)

    Function searchRec(node, value):
        if node is null or node.data == value:
            return node

        if value < node.data:
            return searchRec(node.left, value)
        return searchRec(node.right, value)
```

---

## When to Use Trees

### ✅ Use Trees When:
- Hierarchical data representation (file systems, org charts)
- Fast search, insertion, deletion needed (BST: O(log n))
- Need sorted data with dynamic updates
- Implementing priority queues (heap)
- Prefix matching (trie)
- Range queries (segment tree, BST)

### ❌ Avoid Trees When:
- Simple sequential access (use array/list)
- Only need stack/queue operations
- Frequent random access by position (use array)
- Small dataset (overhead not worth it)

---

## Real-World Applications

### 1. **File Systems**
- Directory structure
- File organization

### 2. **Databases**
- B-trees and B+ trees for indexing
- Query optimization

### 3. **Compilers**
- Abstract Syntax Trees (AST)
- Expression parsing

### 4. **Networking**
- Routing tables
- Network topology

### 5. **Operating Systems**
- Process scheduling
- Memory management

### 6. **AI/ML**
- Decision trees
- Random forests
- Game trees (minimax)

### 7. **Graphics**
- Scene graphs
- Bounding volume hierarchies

---

## Problem Statements

### Beginner Level

#### Problem 1: Maximum Depth of Binary Tree
**Difficulty:** Beginner

**Problem Statement:**
Given the root of a binary tree, return its maximum depth (number of nodes along longest path from root to leaf).

**Example:**
```
Input: root = [3,9,20,null,null,15,7]
    3
   / \
  9  20
    /  \
   15   7
Output: 3
```

**Constraints:**
- Number of nodes: [0, 10^4]
- -100 ≤ Node.val ≤ 100

**Hints:**
1. Use recursion
2. Depth = 1 + max(depth of left subtree, depth of right subtree)
3. Base case: null node has depth 0

**Test Cases:**
```
Test 1: [] → Expected: 0
Test 2: [1] → Expected: 1
Test 3: [1,2,3,4,5] → Expected: 3
```

**Practice Platform:** LeetCode #104

---

#### Problem 2: Invert Binary Tree
**Difficulty:** Beginner

**Problem Statement:**
Invert a binary tree (swap left and right children for every node).

**Example:**
```
Input:       4              Output:      4
           /   \                        /   \
          2     7                      7     2
         / \   / \                    / \   / \
        1   3 6   9                  9   6 3   1
```

**Constraints:**
- Number of nodes: [0, 100]
- -100 ≤ Node.val ≤ 100

**Hints:**
1. Swap left and right children
2. Recursively invert left and right subtrees
3. Can use recursion or iteration with queue

**Test Cases:**
```
Test 1: [] → Expected: []
Test 2: [1] → Expected: [1]
Test 3: [1,2,3] → Expected: [1,3,2]
```

**Practice Platform:** LeetCode #226

---

### Easy Level

#### Problem 3: Same Tree
**Difficulty:** Easy

**Problem Statement:**
Given roots of two binary trees p and q, check if they are identical.

**Constraints:**
- Number of nodes: [0, 100]
- -10^4 ≤ Node.val ≤ 10^4

**Hints:**
1. Trees are same if roots have same value and subtrees are same
2. Use recursion to check both subtrees
3. Handle null cases carefully

**Test Cases:**
```
Test 1: p=[1,2,3], q=[1,2,3] → Expected: true
Test 2: p=[1,2], q=[1,null,2] → Expected: false
```

**Practice Platform:** LeetCode #100

---

#### Problem 4: Symmetric Tree
**Difficulty:** Easy

**Problem Statement:**
Check if a binary tree is symmetric around its center.

**Hints:**
1. Tree is symmetric if left subtree is mirror of right subtree
2. Two trees are mirrors if roots are same and opposite subtrees are mirrors
3. Can use recursion or iterative BFS

**Practice Platform:** LeetCode #101

---

### Medium Level

#### Problem 5: Binary Tree Level Order Traversal
**Difficulty:** Medium

**Problem Statement:**
Return level order traversal of binary tree (values level by level, left to right).

**Hints:**
1. Use queue for BFS
2. Process nodes level by level
3. Track level size before processing each level

**Practice Platform:** LeetCode #102

---

#### Problem 6: Validate Binary Search Tree
**Difficulty:** Medium

**Problem Statement:**
Determine if a binary tree is a valid BST.

**Constraints:**
- Number of nodes: [1, 10^4]
- -2^31 ≤ Node.val ≤ 2^31 - 1

**Hints:**
1. Not enough to check node.left < node < node.right
2. Must check entire left subtree < node < entire right subtree
3. Use range constraints: pass min and max allowed values

**Test Cases:**
```
Test 1: [2,1,3] → Expected: true
Test 2: [5,1,4,null,null,3,6] → Expected: false
```

**Practice Platform:** LeetCode #98

---

#### Problem 7: Lowest Common Ancestor of BST
**Difficulty:** Medium

**Problem Statement:**
Find lowest common ancestor of two nodes in a BST.

**Hints:**
1. LCA is split point where p and q go different directions
2. If both < node, LCA in left subtree
3. If both > node, LCA in right subtree
4. Otherwise, current node is LCA

**Practice Platform:** LeetCode #235

---

### Hard Level

#### Problem 8: Binary Tree Maximum Path Sum
**Difficulty:** Hard

**Problem Statement:**
Find maximum path sum in binary tree (path can start and end at any nodes).

**Constraints:**
- Number of nodes: [1, 3 * 10^4]
- -1000 ≤ Node.val ≤ 1000

**Hints:**
1. For each node, calculate max path through it
2. Max path through node = node.val + max(left, 0) + max(right, 0)
3. Use global variable to track overall maximum

**Practice Platform:** LeetCode #124

---

#### Problem 9: Serialize and Deserialize Binary Tree
**Difficulty:** Hard

**Problem Statement:**
Design algorithm to serialize and deserialize binary tree to/from string.

**Hints:**
1. Use preorder traversal with null markers
2. Serialize: convert tree to string with delimiters
3. Deserialize: reconstruct tree from string

**Practice Platform:** LeetCode #297

---

#### Problem 10: Binary Tree Cameras
**Difficulty:** Hard

**Problem Statement:**
Find minimum cameras needed to monitor all nodes (camera at node monitors parent, itself, and children).

**Hints:**
1. Use greedy approach with DFS
2. Three states: needs camera, has camera, monitored
3. Process from leaves upward

**Practice Platform:** LeetCode #968

---

## Related Topics

### Prerequisites:
- [Recursion](../Recursion/)
- [Stacks and Queues](../Stack/) - For iterative traversals
- [Arrays](../Arrays/) - For array-based representation

### Related Data Structures:
- [Heaps](../Heaps/) - Special type of binary tree
- [Tries](../Tries/) - Specialized tree for strings
- [Graphs](../Graphs/) - Generalization of trees
- [Segment Trees](../SegmentTrees/) - For range queries

### Related Algorithms:
- [Depth-First Search](../GraphAlgorithms/Traversal/)
- [Breadth-First Search](../GraphAlgorithms/Traversal/)
- [Dynamic Programming](../DynamicProgramming/) - Tree DP
- [Greedy](../Greedy/) - Some tree problems

### Next Topics to Study:
- AVL Trees - Self-balancing BST
- Red-Black Trees - Alternative balanced BST
- B-Trees - Disk-based trees
- Segment Trees - Range queries
- Tries - String-based trees

---

## Summary

Trees are essential for:
- ✅ Hierarchical data representation
- ✅ Fast search/insert/delete (O(log n) with balanced trees)
- ✅ Sorted data with dynamic updates
- ✅ Many algorithms and applications

**Key Takeaways:**
1. Understand tree traversals (inorder, preorder, postorder, level order)
2. Master recursion - most tree problems use it
3. Know BST property and operations
4. Understand balanced trees for performance
5. Practice tree problems - they're common in interviews

**Time Complexity:**
- Balanced BST: O(log n) for search/insert/delete
- Unbalanced BST (worst): O(n)
- Traversals: O(n)

---

**Happy Learning! 🎓**

*Master trees, and you'll unlock solutions to countless algorithmic problems!*
