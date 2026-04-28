# Hash Tables - Complete Guide

## Table of Contents
1. [Introduction](#introduction)
2. [What is a Hash Table?](#what-is-a-hash-table)
3. [Hash Functions](#hash-functions)
4. [Collision Resolution](#collision-resolution)
5. [Visual Representation](#visual-representation)
6. [Implementation Guidelines](#implementation-guidelines)
7. [Core Operations](#core-operations)
8. [Time & Space Complexity](#time--space-complexity)
9. [When to Use Hash Tables](#when-to-use-hash-tables)
10. [Real-World Applications](#real-world-applications)
11. [Problem Statements](#problem-statements)
12. [Related Topics](#related-topics)

---

## Introduction

A **Hash Table** (also known as Hash Map or Dictionary) is a data structure that implements an associative array abstract data type, mapping keys to values. It uses a **hash function** to compute an index into an array of buckets or slots, from which the desired value can be found.

---

## What is a Hash Table?

A hash table is a data structure that provides **fast insertion, deletion, and lookup** operations by using a hash function to map keys to array indices.

### Key Characteristics:
- **Key-Value Pairs** - Stores data as (key, value) pairs
- **Hash Function** - Converts keys to array indices
- **Average O(1) Operations** - Insert, delete, and search in constant time
- **Unordered** - Elements are not stored in any particular order
- **Dynamic Sizing** - Can grow or shrink as needed

### Components:
1. **Key:** Unique identifier for data
2. **Value:** The actual data stored
3. **Hash Function:** Converts key to array index
4. **Bucket/Slot:** Storage location in the array

---

## Hash Functions

A **hash function** maps keys of arbitrary size to fixed-size values (hash codes/indices).

### Properties of Good Hash Functions:

1. **Deterministic:** Same key always produces same hash
2. **Uniform Distribution:** Distributes keys evenly across table
3. **Efficient:** Computes hash quickly
4. **Minimize Collisions:** Different keys should produce different hashes (ideally)

### Common Hash Function Techniques:

#### 1. Division Method
```
hash(key) = key % table_size
```
- Simple and fast
- table_size should be prime number

#### 2. Multiplication Method
```
hash(key) = floor(table_size * ((key * A) mod 1))
```
- A is constant between 0 and 1 (often (√5 - 1)/2)

#### 3. String Hashing (Polynomial Rolling Hash)
```
hash(string) = (s[0] * p^0 + s[1] * p^1 + ... + s[n-1] * p^(n-1)) mod m
```
- p is prime number (often 31 or 53)
- m is large prime (often 10^9 + 9)

#### 4. Universal Hashing
```
hash(key) = ((a * key + b) mod p) mod m
```
- a, b are random constants
- p is large prime

---

## Collision Resolution

When two keys hash to the same index, it's called a **collision**. Two main strategies:

### 1. Chaining (Open Hashing)

Each bucket contains a linked list of entries that hash to the same index.

```
Visual Representation:
Index 0: [key1:val1] -> [key5:val5] -> NULL
Index 1: [key2:val2] -> NULL
Index 2: [key3:val3] -> [key7:val7] -> [key9:val9] -> NULL
Index 3: NULL
Index 4: [key4:val4] -> NULL
```

**Pros:**
- Simple to implement
- Hash table never fills up
- Less sensitive to hash function quality

**Cons:**
- Extra memory for pointers
- Cache performance issues

**Pseudocode:**
```
Function insert(key, value):
    index = hash(key) % table_size
    Add (key, value) to linked list at table[index]

Function search(key):
    index = hash(key) % table_size
    Search linked list at table[index] for key
    return value if found, else null

Function delete(key):
    index = hash(key) % table_size
    Remove key from linked list at table[index]
```

### 2. Open Addressing (Closed Hashing)

All entries stored in the array itself. When collision occurs, probe for next empty slot.

#### a) Linear Probing
```
If hash(key) is occupied, try hash(key) + 1, hash(key) + 2, ...
```

```
Visual Example (insert keys with hash values):
Insert key with hash=2: [_, _, K1, _, _]
Insert key with hash=2: [_, _, K1, K2, _] (linear probe to index 3)
Insert key with hash=3: [_, _, K1, K2, K3] (linear probe to index 4)
```

**Pros:** Good cache performance
**Cons:** Primary clustering (consecutive blocks form)

#### b) Quadratic Probing
```
If hash(key) is occupied, try hash(key) + 1^2, hash(key) + 2^2, hash(key) + 3^2, ...
```

**Pros:** Reduces primary clustering
**Cons:** Secondary clustering, may not probe all slots

#### c) Double Hashing
```
If hash(key) is occupied, use second hash function:
probe_sequence = (hash1(key) + i * hash2(key)) % table_size
```

**Pros:** Minimal clustering
**Cons:** More computation

---

## Visual Representation

### Hash Table with Chaining

```
Hash Function: key % 7

Keys to Insert: [15, 22, 37, 8, 29, 14]

Hash Table:
┌───┬──────────────────────────┐
│ 0 │ → [14] → NULL            │
├───┼──────────────────────────┤
│ 1 │ → [15] → [22] → [29] →   │  (collision: all hash to 1)
│   │    NULL                  │
├───┼──────────────────────────┤
│ 2 │ → NULL                   │
├───┼──────────────────────────┤
│ 3 │ → NULL                   │
├───┼──────────────────────────┤
│ 4 │ → NULL                   │
├───┼──────────────────────────┤
│ 5 │ → NULL                   │
├───┼──────────────────────────┤
│ 6 │ → [37] → NULL            │
└───┴──────────────────────────┘

8 % 7 = 1 (goes to index 1, but collision occurred)
```

### Hash Table with Open Addressing (Linear Probing)

```
Insert keys: [15, 22, 37, 8]
Hash function: key % 7

Step by step:
Initial: [_, _, _, _, _, _, _]

Insert 15 (15%7=1): [_, 15, _, _, _, _, _]
Insert 22 (22%7=1, collision, probe to 2): [_, 15, 22, _, _, _, _]
Insert 37 (37%7=2, collision, probe to 3): [_, 15, 22, 37, _, _, _]
Insert 8  (8%7=1, collision, probe to 4): [_, 15, 22, 37, 8, _, _]
```

---

## Implementation Guidelines

### Basic Structure (Language-Agnostic Pseudocode)

```
Class HashNode:
    Key key
    Value value
    HashNode next  // for chaining

Class HashTable:
    Array<HashNode> table
    Integer size
    Integer capacity
    Float load_factor_threshold = 0.75

    Function Constructor(initial_capacity):
        capacity = initial_capacity
        table = new Array[capacity]
        size = 0

    Function hash(key):
        // Simple hash function
        hash_code = compute_hash(key)
        return abs(hash_code) % capacity

    Function put(key, value):
        index = hash(key)

        // Check if key exists (update value)
        node = table[index]
        while node is not null:
            if node.key == key:
                node.value = value
                return

            node = node.next

        // Insert new node at beginning of chain
        new_node = new HashNode(key, value)
        new_node.next = table[index]
        table[index] = new_node
        size = size + 1

        // Check if rehashing needed
        if (size / capacity) > load_factor_threshold:
            rehash()

    Function get(key):
        index = hash(key)
        node = table[index]

        while node is not null:
            if node.key == key:
                return node.value
            node = node.next

        return null  // key not found

    Function remove(key):
        index = hash(key)
        node = table[index]
        prev = null

        while node is not null:
            if node.key == key:
                if prev is null:
                    table[index] = node.next
                else:
                    prev.next = node.next
                size = size - 1
                return true

            prev = node
            node = node.next

        return false  // key not found

    Function rehash():
        old_table = table
        capacity = capacity * 2
        table = new Array[capacity]
        size = 0

        // Reinsert all elements
        for each bucket in old_table:
            node = bucket
            while node is not null:
                put(node.key, node.value)
                node = node.next
```

---

## Core Operations

### 1. Insert / Put
```
Function insert(key, value):
    index = hash(key)
    if key exists at index:
        update value
    else:
        add new entry at index
```
**Average Time:** O(1)
**Worst Time:** O(n) with chaining and poor hash function

### 2. Search / Get
```
Function search(key):
    index = hash(key)
    search at index for key
    return value if found
```
**Average Time:** O(1)
**Worst Time:** O(n)

### 3. Delete / Remove
```
Function delete(key):
    index = hash(key)
    find and remove entry at index
```
**Average Time:** O(1)
**Worst Time:** O(n)

### 4. Rehashing
```
Function rehash():
    create new table with 2x capacity
    reinsert all existing entries
```
**Time:** O(n)
**When:** Load factor > threshold (typically 0.75)

---

## Time & Space Complexity

| Operation | Average Case | Worst Case | Notes |
|-----------|-------------|------------|-------|
| Insert | O(1) | O(n) | Worst case if all keys collide |
| Search | O(1) | O(n) | Worst case if all keys collide |
| Delete | O(1) | O(n) | Worst case if all keys collide |
| Space | O(n) | O(n) | n = number of elements |

**Load Factor** = number of entries / table size
- Low load factor → less collisions, more memory
- High load factor → more collisions, less memory
- Typical threshold: 0.75

---

## When to Use Hash Tables

### ✅ Use Hash Tables When:
- Need fast lookup, insertion, and deletion (O(1) average)
- Working with key-value associations
- Need to check if element exists in collection
- Counting frequencies of elements
- Implementing caches (LRU cache)
- Finding duplicates
- Group elements by some property

### ❌ Avoid Hash Tables When:
- Need ordered/sorted data (use BST or sorted array)
- Need to find min/max frequently (use heap)
- Memory is severely constrained
- Need to iterate in insertion order (use array or linked list)
- Keys don't have good hash function

---

## Real-World Applications

1. **Database Indexing**
   - Fast record lookup by key
   - Join operations

2. **Caching**
   - Web browser caches
   - DNS lookup caches
   - LRU/LFU caches

3. **Symbol Tables**
   - Compilers (variable lookup)
   - Interpreters (symbol resolution)

4. **Spell Checkers**
   - Dictionary storage
   - Fast word lookup

5. **Password Verification**
   - Store hashed passwords
   - Quick authentication

6. **Data Deduplication**
   - File systems
   - Backup systems
   - Version control (Git objects)

7. **Routing Tables**
   - Network routers
   - IP address lookup

---

## Problem Statements

### Beginner Level

#### Problem 1: Two Sum
**Difficulty:** Beginner

**Problem Statement:**
Given an array of integers nums and an integer target, return indices of the two numbers that add up to target. You may assume each input has exactly one solution.

**Example:**
```
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: nums[0] + nums[1] = 2 + 7 = 9

Input: nums = [3,2,4], target = 6
Output: [1,2]
```

**Constraints:**
- 2 ≤ nums.length ≤ 10^4
- -10^9 ≤ nums[i] ≤ 10^9
- -10^9 ≤ target ≤ 10^9
- Only one valid answer exists

**Hints:**
1. Use hash table to store values you've seen
2. For each number, check if (target - number) exists in hash table
3. Store index as value in hash table

**Test Cases:**
```
Test 1: [1,2], target=3 → Expected: [0,1]
Test 2: [3,3], target=6 → Expected: [0,1]
Test 3: [-1,-2,-3,-4], target=-5 → Expected: [0,3] or [1,2]
```

**Practice Platform:** LeetCode #1

---

#### Problem 2: Contains Duplicate
**Difficulty:** Beginner

**Problem Statement:**
Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.

**Example:**
```
Input: nums = [1,2,3,1]
Output: true

Input: nums = [1,2,3,4]
Output: false
```

**Constraints:**
- 1 ≤ nums.length ≤ 10^5
- -10^9 ≤ nums[i] ≤ 10^9

**Hints:**
1. Use a hash set to track seen numbers
2. If number already in set, return true
3. After checking all numbers, return false

**Test Cases:**
```
Test 1: [1] → Expected: false
Test 2: [1,1] → Expected: true
Test 3: [1,2,3,4,5,6,7,8,9,1] → Expected: true
```

**Practice Platform:** LeetCode #217

---

### Easy Level

#### Problem 3: Valid Anagram
**Difficulty:** Easy

**Problem Statement:**
Given two strings s and t, return true if t is an anagram of s, and false otherwise. An anagram is formed by rearranging the letters of a word.

**Example:**
```
Input: s = "anagram", t = "nagaram"
Output: true

Input: s = "rat", t = "car"
Output: false
```

**Constraints:**
- 1 ≤ s.length, t.length ≤ 5 * 10^4
- s and t consist of lowercase English letters

**Hints:**
1. Use hash table to count frequency of each character in s
2. Decrement count for each character in t
3. Check if all counts are zero

**Test Cases:**
```
Test 1: s="a", t="a" → Expected: true
Test 2: s="ab", t="ba" → Expected: true
Test 3: s="abc", t="abcd" → Expected: false
```

**Practice Platform:** LeetCode #242

---

#### Problem 4: Group Anagrams
**Difficulty:** Easy

**Problem Statement:**
Given an array of strings strs, group the anagrams together. You can return the answer in any order.

**Example:**
```
Input: strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
```

**Constraints:**
- 1 ≤ strs.length ≤ 10^4
- 0 ≤ strs[i].length ≤ 100
- strs[i] consists of lowercase English letters

**Hints:**
1. Use sorted string as key in hash table
2. All anagrams will have same sorted string
3. Group strings by their sorted version

**Test Cases:**
```
Test 1: [""] → Expected: [[""]]
Test 2: ["a"] → Expected: [["a"]]
Test 3: ["ab","ba"] → Expected: [["ab","ba"]]
```

**Practice Platform:** LeetCode #49

---

#### Problem 5: First Unique Character
**Difficulty:** Easy

**Problem Statement:**
Given a string s, find the first non-repeating character in it and return its index. If it does not exist, return -1.

**Example:**
```
Input: s = "leetcode"
Output: 0

Input: s = "loveleetcode"
Output: 2

Input: s = "aabb"
Output: -1
```

**Constraints:**
- 1 ≤ s.length ≤ 10^5
- s consists of only lowercase English letters

**Hints:**
1. First pass: count frequency of each character
2. Second pass: find first character with count = 1

**Test Cases:**
```
Test 1: "a" → Expected: 0
Test 2: "aabbcc" → Expected: -1
Test 3: "abcabc" → Expected: -1
```

**Practice Platform:** LeetCode #387

---

### Medium Level

#### Problem 6: Longest Substring Without Repeating Characters
**Difficulty:** Medium

**Problem Statement:**
Given a string s, find the length of the longest substring without repeating characters.

**Example:**
```
Input: s = "abcabcbb"
Output: 3
Explanation: "abc" is the longest substring

Input: s = "bbbbb"
Output: 1

Input: s = "pwwkew"
Output: 3
Explanation: "wke" is the longest
```

**Constraints:**
- 0 ≤ s.length ≤ 5 * 10^4
- s consists of English letters, digits, symbols and spaces

**Hints:**
1. Use sliding window with hash table
2. Hash table stores character and its latest index
3. When duplicate found, move left pointer

**Test Cases:**
```
Test 1: "" → Expected: 0
Test 2: "a" → Expected: 1
Test 3: "abcdef" → Expected: 6
Test 4: "abba" → Expected: 2
```

**Practice Platform:** LeetCode #3

---

#### Problem 7: Subarray Sum Equals K
**Difficulty:** Medium

**Problem Statement:**
Given an array of integers nums and an integer k, return the total number of subarrays whose sum equals to k.

**Example:**
```
Input: nums = [1,1,1], k = 2
Output: 2
Explanation: [1,1] appears twice

Input: nums = [1,2,3], k = 3
Output: 2
Explanation: [1,2] and [3]
```

**Constraints:**
- 1 ≤ nums.length ≤ 2 * 10^4
- -1000 ≤ nums[i] ≤ 1000
- -10^7 ≤ k ≤ 10^7

**Hints:**
1. Use prefix sum concept
2. Hash table stores prefix sum and its frequency
3. For each position, check if (current_sum - k) exists in hash table

**Test Cases:**
```
Test 1: [1], k=1 → Expected: 1
Test 2: [1,-1,0], k=0 → Expected: 3
Test 3: [1,2,1,2,1], k=3 → Expected: 4
```

**Practice Platform:** LeetCode #560

---

#### Problem 8: Longest Consecutive Sequence
**Difficulty:** Medium

**Problem Statement:**
Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence. You must write an algorithm that runs in O(n) time.

**Example:**
```
Input: nums = [100,4,200,1,3,2]
Output: 4
Explanation: [1,2,3,4] is the longest consecutive sequence

Input: nums = [0,3,7,2,5,8,4,6,0,1]
Output: 9
```

**Constraints:**
- 0 ≤ nums.length ≤ 10^5
- -10^9 ≤ nums[i] ≤ 10^9

**Hints:**
1. Put all numbers in hash set
2. For each number, check if it's start of sequence (num-1 not in set)
3. Count consecutive numbers from that starting point

**Test Cases:**
```
Test 1: [] → Expected: 0
Test 2: [1] → Expected: 1
Test 3: [1,2,0,1] → Expected: 3
```

**Practice Platform:** LeetCode #128

---

### Hard Level

#### Problem 9: LRU Cache
**Difficulty:** Hard

**Problem Statement:**
Design a data structure that follows Least Recently Used (LRU) cache. Implement the LRUCache class with get(key) and put(key, value) operations, both in O(1) time.

**Example:**
```
Input:
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1,1], [2,2], [1], [3,3], [2], [4,4], [1], [3], [4]]

Output:
[null, null, null, 1, null, -1, null, -1, 3, 4]

Explanation:
LRUCache cache = new LRUCache(2);
cache.put(1, 1);
cache.put(2, 2);
cache.get(1);    // returns 1
cache.put(3, 3); // evicts key 2
cache.get(2);    // returns -1 (not found)
cache.put(4, 4); // evicts key 1
cache.get(1);    // returns -1 (not found)
cache.get(3);    // returns 3
cache.get(4);    // returns 4
```

**Constraints:**
- 1 ≤ capacity ≤ 3000
- 0 ≤ key ≤ 10^4
- 0 ≤ value ≤ 10^5
- At most 2 * 10^5 calls to get and put

**Hints:**
1. Use hash table for O(1) access
2. Use doubly linked list to maintain LRU order
3. Hash table maps key to node in linked list

**Test Cases:**
```
Test 1: capacity=1, operations: put(1,1), get(1) → Expected: 1
Test 2: capacity=2, put(1,1), put(2,2), put(3,3), get(1) → Expected: -1
```

**Practice Platform:** LeetCode #146

---

#### Problem 10: Find All Anagrams in a String
**Difficulty:** Medium-Hard

**Problem Statement:**
Given two strings s and p, return an array of all the start indices of p's anagrams in s.

**Example:**
```
Input: s = "cbaebabacd", p = "abc"
Output: [0,6]
Explanation:
The substring "cba" at index 0 is an anagram of "abc"
The substring "bac" at index 6 is an anagram of "abc"

Input: s = "abab", p = "ab"
Output: [0,1,2]
```

**Constraints:**
- 1 ≤ s.length, p.length ≤ 3 * 10^4
- s and p consist of lowercase English letters

**Hints:**
1. Use sliding window of size p.length
2. Use hash table to track character frequencies
3. Compare window's frequency with p's frequency

**Test Cases:**
```
Test 1: s="a", p="a" → Expected: [0]
Test 2: s="abc", p="xyz" → Expected: []
Test 3: s="aaa", p="a" → Expected: [0,1,2]
```

**Practice Platform:** LeetCode #438

---

### Expert Level

#### Problem 11: Substring with Concatenation of All Words
**Difficulty:** Expert

**Problem Statement:**
You are given a string s and an array of strings words of the same length. Return all starting indices of substring(s) in s that is a concatenation of each word in words exactly once, in any order.

**Example:**
```
Input: s = "barfoothefoobarman", words = ["foo","bar"]
Output: [0,9]
Explanation:
Substring starting at index 0 is "barfoo"
Substring starting at index 9 is "foobar"

Input: s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
Output: []
```

**Constraints:**
- 1 ≤ s.length ≤ 10^4
- 1 ≤ words.length ≤ 5000
- 1 ≤ words[i].length ≤ 30
- All strings of words are of same length

**Hints:**
1. Use hash table to store word frequencies
2. Use sliding window of size (word_count * word_length)
3. For each window, check if it contains exact word frequencies

**Test Cases:**
```
Test 1: s="a", words=["a"] → Expected: [0]
Test 2: s="abab", words=["ab","ba"] → Expected: [0]
```

**Practice Platform:** LeetCode #30

---

#### Problem 12: Minimum Window Substring
**Difficulty:** Expert

**Problem Statement:**
Given two strings s and t, return the minimum window substring of s such that every character in t (including duplicates) is included in the window. If there is no such substring, return the empty string "".

**Example:**
```
Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"

Input: s = "a", t = "a"
Output: "a"

Input: s = "a", t = "aa"
Output: ""
```

**Constraints:**
- 1 ≤ s.length, t.length ≤ 10^5
- s and t consist of uppercase and lowercase English letters

**Hints:**
1. Use two hash tables: one for t's characters, one for current window
2. Expand window until all characters of t are included
3. Contract window from left while maintaining validity
4. Track minimum window

**Test Cases:**
```
Test 1: s="a", t="a" → Expected: "a"
Test 2: s="ab", t="b" → Expected: "b"
Test 3: s="abc", t="cba" → Expected: "abc" or any valid permutation
```

**Practice Platform:** LeetCode #76

---

### Advanced Level

#### Problem 13: Design HashSet
**Difficulty:** Advanced

**Problem Statement:**
Design a HashSet without using any built-in hash table libraries. Implement MyHashSet class with add(key), remove(key), and contains(key) methods.

**Example:**
```
Input:
["MyHashSet", "add", "add", "contains", "contains", "add", "contains", "remove", "contains"]
[[], [1], [2], [1], [3], [2], [2], [2], [2]]

Output:
[null, null, null, true, false, null, true, null, false]
```

**Constraints:**
- 0 ≤ key ≤ 10^6
- At most 10^4 calls to add, remove, and contains

**Hints:**
1. Use array of buckets (chaining approach)
2. Implement a simple hash function
3. Each bucket can be a linked list or dynamic array

**Test Cases:**
```
Test 1: add(1), contains(1) → Expected: true
Test 2: add(1), remove(1), contains(1) → Expected: false
```

**Practice Platform:** LeetCode #705

---

#### Problem 14: Isomorphic Strings
**Difficulty:** Advanced

**Problem Statement:**
Given two strings s and t, determine if they are isomorphic. Two strings are isomorphic if the characters in s can be replaced to get t. All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character, but a character may map to itself.

**Example:**
```
Input: s = "egg", t = "add"
Output: true

Input: s = "foo", t = "bar"
Output: false

Input: s = "paper", t = "title"
Output: true
```

**Constraints:**
- 1 ≤ s.length ≤ 5 * 10^4
- t.length == s.length
- s and t consist of any valid ASCII character

**Hints:**
1. Use two hash tables: s→t mapping and t→s mapping
2. Check if both mappings are consistent
3. Each character can only map to one other character

**Test Cases:**
```
Test 1: s="a", t="a" → Expected: true
Test 2: s="ab", t="aa" → Expected: false
Test 3: s="ab", t="ca" → Expected: true
```

**Practice Platform:** LeetCode #205

---

### Master Level

#### Problem 15: All O(1) Data Structure
**Difficulty:** Master

**Problem Statement:**
Design a data structure to store strings and retrieve the maximum/minimum frequency string in O(1) time. Implement AllOne class with inc(key), dec(key), getMaxKey(), and getMinKey() methods.

**Example:**
```
Input:
["AllOne", "inc", "inc", "getMaxKey", "getMinKey", "inc", "getMaxKey", "getMinKey"]
[[], ["hello"], ["hello"], [], [], ["leet"], [], []]

Output:
[null, null, null, "hello", "hello", null, "hello", "leet"]
```

**Constraints:**
- 1 ≤ key.length ≤ 10
- key consists of lowercase English letters
- At most 5 * 10^4 calls to inc, dec, getMaxKey, and getMinKey

**Hints:**
1. Use hash table + doubly linked list of frequency buckets
2. Each bucket contains all keys with that frequency
3. Maintain pointers to min and max frequency buckets

**Test Cases:**
```
Test 1: inc("a"), inc("a"), getMaxKey() → Expected: "a"
Test 2: inc("a"), inc("b"), dec("a"), getMinKey() → Expected: "a" or "b"
```

**Practice Platform:** LeetCode #432

---

## Related Topics

### Prerequisites:
- Arrays
- Linked Lists
- String Manipulation

### Related Data Structures:
- Sets
- Trees (for ordered maps)
- Tries (for string keys)

### Related Concepts:
- Hashing Algorithms (MD5, SHA)
- Bloom Filters
- Consistent Hashing (distributed systems)

### Next Topics to Study:
- Tries (specialized hash structure for strings)
- Bloom Filters (probabilistic data structure)
- Cuckoo Hashing

---

## Summary

Hash Tables are fundamental for:
- ✅ Fast lookups, insertions, deletions
- ✅ Counting frequencies
- ✅ Finding duplicates
- ✅ Caching and memoization
- ✅ Implementing sets and maps

**Key Takeaways:**
1. Average O(1) for insert, search, delete
2. Quality of hash function is crucial
3. Load factor affects performance
4. Collision resolution strategy matters
5. Not suitable for ordered operations

---

**Happy Learning! 🎓**

*Master hash tables, and you'll solve countless problems efficiently!*
