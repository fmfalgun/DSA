# Tries (Prefix Trees) - Complete Guide

## Introduction

A **Trie** (pronounced "try") is a tree-like data structure used to store and retrieve strings efficiently. It's particularly useful for prefix-based operations like autocomplete, spell checking, and IP routing.

## What is a Trie?

A Trie is a tree where:
- Each node represents a character
- Path from root to node represents a prefix
- Special marker indicates complete words
- Children organized by character values

**Visual Example:**
```
Storing: "cat", "car", "card", "care", "careful", "dog"

        root
       /    \
      c      d
      |      |
      a      o
     /|\     |
    t r e    g*
    * |\
      d f
      |  \
      *   u
           \
            l
            *

* = end of word marker
```

## Core Operations

### 1. Insert
```
Time: O(m) where m = word length
Space: O(m)
```

### 2. Search
```
Time: O(m)
Space: O(1)
```

### 3. Prefix Search
```
Time: O(m)
Space: O(1)
```

### 4. Delete
```
Time: O(m)
Space: O(m) for recursion
```

## Implementation (Pseudocode)

```
Class TrieNode:
    Map<Character, TrieNode> children
    Boolean isEndOfWord

Class Trie:
    TrieNode root

    Function insert(word):
        node = root
        for each char in word:
            if char not in node.children:
                node.children[char] = new TrieNode()
            node = node.children[char]
        node.isEndOfWord = true

    Function search(word):
        node = root
        for each char in word:
            if char not in node.children:
                return false
            node = node.children[char]
        return node.isEndOfWord

    Function startsWith(prefix):
        node = root
        for each char in prefix:
            if char not in node.children:
                return false
            node = node.children[char]
        return true
```

## When to Use Tries

✅ **Use When:**
- Autocomplete functionality
- Spell checkers
- IP routing tables
- Dictionary implementations
- Prefix matching
- Word games (Boggle, Scrabble)

❌ **Avoid When:**
- Simple key-value lookup (use hash table)
- Memory is very limited
- No prefix operations needed

## Real-World Applications

1. **Search Engines:** Query suggestions
2. **Text Editors:** Autocomplete
3. **Networking:** IP routing (longest prefix matching)
4. **Bioinformatics:** DNA sequence analysis
5. **Compilers:** Symbol tables

## Problem Statements

### Beginner: Implement Trie
**Problem:** Design a Trie with insert, search, and startsWith methods.
**Constraints:** 1 ≤ word.length ≤ 2000
**Hints:** Use hash map for children nodes
**Platform:** LeetCode #208

### Easy: Word Search II
**Problem:** Find all words from dictionary that exist in a 2D board.
**Hints:** Build trie from dictionary, use DFS on board
**Platform:** LeetCode #212

### Medium: Design Search Autocomplete System
**Problem:** Design autocomplete system that returns top 3 historical hot sentences.
**Hints:** Trie + frequency tracking + DFS for top-k
**Platform:** LeetCode #642

### Hard: Word Squares
**Problem:** Given set of words, return all word squares.
**Hints:** Trie for prefix lookup, backtracking
**Platform:** LeetCode #425

## Space & Time Complexity

| Operation | Time | Space |
|-----------|------|-------|
| Insert | O(m) | O(m) |
| Search | O(m) | O(1) |
| Prefix Search | O(m) | O(1) |
| Delete | O(m) | O(m) |

m = word length
Overall space: O(ALPHABET_SIZE * N * M) worst case

## Variants

1. **Compressed Trie (Radix Tree):** Merge single-child nodes
2. **Ternary Search Tree:** Each node has 3 children (left, equal, right)
3. **Suffix Trie:** Store all suffixes of strings
4. **Patricia Trie:** Space-optimized radix tree

## Related Topics
- Hash Tables
- Trees
- String Algorithms
- DFS/BFS

**Happy Learning! 🎓**
