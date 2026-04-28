# String Algorithms - Complete Guide

## Introduction

String algorithms are techniques for processing, searching, and manipulating text data. They're fundamental in text editors, search engines, bioinformatics, and data compression.

## String Matching Algorithms

### 1. Naive String Matching

**Concept:** Check every position in text for pattern match.

```
Function naiveSearch(text, pattern):
    n = text.length
    m = pattern.length

    for i from 0 to n-m:
        j = 0
        while j < m and text[i+j] == pattern[j]:
            j++

        if j == m:
            output "Pattern found at index" i
```

**Complexity:**
- Time: O(n×m)
- Space: O(1)

### 2. KMP (Knuth-Morris-Pratt) Algorithm

**Concept:** Use failure function to avoid re-checking matched characters.

**Preprocessing:**
```
Function computeLPS(pattern):
    m = pattern.length
    lps = array of size m
    lps[0] = 0
    len = 0
    i = 1

    while i < m:
        if pattern[i] == pattern[len]:
            len++
            lps[i] = len
            i++
        else:
            if len != 0:
                len = lps[len-1]
            else:
                lps[i] = 0
                i++

    return lps
```

**Searching:**
```
Function KMPSearch(text, pattern):
    n = text.length
    m = pattern.length
    lps = computeLPS(pattern)

    i = 0  // text index
    j = 0  // pattern index

    while i < n:
        if text[i] == pattern[j]:
            i++
            j++

        if j == m:
            output "Pattern at" i-j
            j = lps[j-1]
        else if i < n and text[i] != pattern[j]:
            if j != 0:
                j = lps[j-1]
            else:
                i++
```

**Complexity:**
- Time: O(n + m)
- Space: O(m)

### 3. Rabin-Karp Algorithm

**Concept:** Use rolling hash to match patterns.

```
Function rabinKarp(text, pattern):
    n = text.length
    m = pattern.length
    d = 256  // number of characters
    q = large_prime

    patternHash = 0
    textHash = 0
    h = pow(d, m-1) % q

    // Calculate initial hashes
    for i from 0 to m-1:
        patternHash = (d*patternHash + pattern[i]) % q
        textHash = (d*textHash + text[i]) % q

    // Slide pattern
    for i from 0 to n-m:
        if patternHash == textHash:
            // Check character by character
            if text[i..i+m-1] == pattern:
                output "Pattern at" i

        if i < n-m:
            textHash = (d*(textHash - text[i]*h) + text[i+m]) % q
            if textHash < 0:
                textHash += q
```

**Complexity:**
- Time: O(n+m) average, O(nm) worst
- Space: O(1)

### 4. Z-Algorithm

**Concept:** Compute Z-array where Z[i] = length of longest substring starting at i that matches prefix.

**Complexity:**
- Time: O(n)
- Space: O(n)

## String Manipulation

### Longest Palindromic Substring

#### Manacher's Algorithm
**Concept:** Find all palindromes in linear time.

**Complexity:**
- Time: O(n)
- Space: O(n)

### Longest Common Substring

**Approach:** Dynamic Programming

```
Function LCS(s1, s2):
    m = s1.length
    n = s2.length
    dp = 2D array of size (m+1) × (n+1)
    maxLen = 0

    for i from 1 to m:
        for j from 1 to n:
            if s1[i-1] == s2[j-1]:
                dp[i][j] = dp[i-1][j-1] + 1
                maxLen = max(maxLen, dp[i][j])
            else:
                dp[i][j] = 0

    return maxLen
```

**Complexity:**
- Time: O(m×n)
- Space: O(m×n)

### String Hashing

**Rolling Hash:**
```
hash = (s[0]*p^0 + s[1]*p^1 + ... + s[n-1]*p^(n-1)) mod m

p = prime (usually 31 or 53)
m = large prime (usually 10^9+9)
```

## Problem Statements

### Beginner: Valid Palindrome
**Problem:** Check if string is palindrome ignoring non-alphanumeric.
**Hints:** Two pointers from both ends
**Platform:** LeetCode #125

### Easy: Implement strStr()
**Problem:** Find first occurrence of needle in haystack.
**Hints:** Use KMP or simple comparison
**Platform:** LeetCode #28

### Easy: Longest Common Prefix
**Problem:** Find longest common prefix in array of strings.
**Hints:** Vertical scanning or divide and conquer
**Platform:** LeetCode #14

### Medium: Longest Palindromic Substring
**Problem:** Find longest palindromic substring.
**Hints:** Expand around center or use Manacher's
**Platform:** LeetCode #5

### Medium: Group Anagrams
**Problem:** Group strings that are anagrams.
**Hints:** Use sorted string or character count as key
**Platform:** LeetCode #49

### Medium: Longest Substring Without Repeating
**Problem:** Find length of longest substring without repeating characters.
**Hints:** Sliding window with hash set
**Platform:** LeetCode #3

### Hard: Minimum Window Substring
**Problem:** Find minimum window in s containing all characters of t.
**Hints:** Sliding window with frequency map
**Platform:** LeetCode #76

### Hard: Edit Distance
**Problem:** Minimum operations to convert one string to another.
**Hints:** Dynamic programming
**Platform:** LeetCode #72

### Expert: Regular Expression Matching
**Problem:** Implement regex with '.' and '*'.
**Hints:** Dynamic programming or recursion with memoization
**Platform:** LeetCode #10

### Expert: Distinct Subsequences
**Problem:** Count distinct subsequences of s that equal t.
**Hints:** 2D DP
**Platform:** LeetCode #115

## Common String Patterns

### Pattern 1: Two Pointers
Valid palindrome, remove duplicates

### Pattern 2: Sliding Window
Longest substring problems

### Pattern 3: Hash Map
Anagrams, character frequency

### Pattern 4: Dynamic Programming
Edit distance, palindrome partitioning

### Pattern 5: Trie
Prefix matching, autocomplete

## String Operations Complexity

| Operation | Time | Space |
|-----------|------|-------|
| Concatenation | O(n) | O(n) |
| Comparison | O(n) | O(1) |
| Substring | O(n) | O(n) |
| Search (naive) | O(nm) | O(1) |
| Search (KMP) | O(n+m) | O(m) |
| Reverse | O(n) | O(1) or O(n) |

## Real-World Applications

1. **Text Editors:** Find and replace
2. **Search Engines:** Pattern matching
3. **Bioinformatics:** DNA sequence alignment
4. **Compilers:** Lexical analysis
5. **Data Validation:** Pattern matching
6. **Plagiarism Detection:** Substring matching

## Tips for String Problems

1. **Consider string immutability** (in some languages)
2. **Use StringBuilder** for concatenations
3. **Two pointers** for palindrome problems
4. **Sliding window** for substring problems
5. **DP** for complex string transformations
6. **Hash maps** for character counting

## Summary

String algorithms are crucial for:
- ✅ Text processing
- ✅ Pattern matching
- ✅ Data validation
- ✅ Computational biology

**Key Takeaway:** Master KMP, sliding window, and DP patterns for strings. They cover most interview problems!

**Happy Learning! 🎓**
