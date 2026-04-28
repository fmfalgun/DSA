# Dynamic Programming - Complete Guide

## Table of Contents
1. [Introduction](#introduction)
2. [What is Dynamic Programming?](#what-is-dynamic-programming)
3. [When to Use DP](#when-to-use-dp)
4. [DP Approaches](#dp-approaches)
5. [Common DP Patterns](#common-dp-patterns)
6. [Implementation Techniques](#implementation-techniques)
7. [Time & Space Complexity](#time--space-complexity)
8. [Problem-Solving Steps](#problem-solving-steps)
9. [Real-World Applications](#real-world-applications)
10. [Problem Statements](#problem-statements)
11. [Related Topics](#related-topics)

---

## Introduction

**Dynamic Programming (DP)** is an algorithmic paradigm that solves complex problems by breaking them down into simpler subproblems and storing their solutions to avoid redundant calculations. It's one of the most powerful techniques in competitive programming and technical interviews.

---

## What is Dynamic Programming?

Dynamic Programming is an optimization technique that:
- **Breaks down** complex problems into simpler overlapping subproblems
- **Stores** solutions to subproblems to avoid recomputation (**memoization**)
- **Builds up** solutions from smaller subproblems (**tabulation**)

### Key Characteristics:
1. **Optimal Substructure:** Optimal solution contains optimal solutions to subproblems
2. **Overlapping Subproblems:** Same subproblems are solved multiple times
3. **Memoization/Tabulation:** Store and reuse computed results

---

## When to Use DP

### ✅ Use DP When Problem Has:

1. **Optimal Substructure**
   - Problem can be broken into subproblems
   - Optimal solution uses optimal solutions of subproblems

2. **Overlapping Subproblems**
   - Same subproblems recur many times
   - NOT like Divide & Conquer where subproblems are independent

3. **Keywords to Watch For:**
   - "Find optimal..." (min/max/best/longest/shortest)
   - "Count number of ways..."
   - "Is it possible to..."
   - Decision making at each step
   - Sequences, subsequences, substrings
   - Optimization problems

---

## DP Approaches

### 1. Top-Down Approach (Memoization)

Start with original problem, recursively break down, store results.

```
Function fibonacci_memo(n, memo):
    if n <= 1:
        return n

    if n in memo:
        return memo[n]

    memo[n] = fibonacci_memo(n-1, memo) + fibonacci_memo(n-2, memo)
    return memo[n]
```

**Pros:**
- ✅ Intuitive (follows natural recursion)
- ✅ Only computes needed subproblems
- ✅ Easy to convert from recursion

**Cons:**
- ❌ Recursion overhead
- ❌ Stack space for recursion
- ❌ May hit recursion limit

### 2. Bottom-Up Approach (Tabulation)

Start with smallest subproblems, build up to original problem.

```
Function fibonacci_tab(n):
    if n <= 1:
        return n

    dp = array of size n+1
    dp[0] = 0
    dp[1] = 1

    for i from 2 to n:
        dp[i] = dp[i-1] + dp[i-2]

    return dp[n]
```

**Pros:**
- ✅ No recursion overhead
- ✅ Better space optimization possible
- ✅ Predictable time complexity

**Cons:**
- ❌ May compute unnecessary subproblems
- ❌ Less intuitive initially
- ❌ Harder to implement for some problems

---

## Common DP Patterns

### 1. Linear DP (1D Array)

Single parameter changes.

**Examples:**
- Fibonacci numbers
- Climbing stairs
- House robber
- Decode ways

**Template:**
```
dp[i] = function of dp[i-1], dp[i-2], ...
```

### 2. Grid DP (2D Array)

Two parameters change (often 2D grid).

**Examples:**
- Unique paths
- Minimum path sum
- Longest common subsequence
- Edit distance

**Template:**
```
dp[i][j] = function of dp[i-1][j], dp[i][j-1], dp[i-1][j-1], ...
```

### 3. Subsequence DP

Finding optimal subsequence.

**Examples:**
- Longest increasing subsequence (LIS)
- Longest common subsequence (LCS)
- Maximum sum increasing subsequence

### 4. Knapsack Pattern

Choosing items with constraints.

**Types:**
- 0/1 Knapsack (each item once)
- Unbounded Knapsack (unlimited items)
- Fractional Knapsack (can take fractions - Greedy works)

**Template:**
```
dp[i][w] = max value using first i items with weight limit w
```

### 5. Palindrome DP

Problems involving palindromes.

**Examples:**
- Longest palindromic substring
- Palindrome partitioning
- Minimum insertions to make palindrome

### 6. String DP

String manipulation problems.

**Examples:**
- Edit distance
- Wildcard matching
- Regular expression matching
- Interleaving strings

### 7. Tree DP

DP on tree structures.

**Examples:**
- House robber III
- Binary tree maximum path sum
- Diameter of tree

### 8. State Machine DP

Modeling states and transitions.

**Examples:**
- Best time to buy/sell stock
- Paint house
- Flip string to monotone increasing

### 9. Digit DP

Problems involving digits of numbers.

**Examples:**
- Count numbers with unique digits
- Numbers at most N given digit set

### 10. Bitmask DP

Using bits to represent states.

**Examples:**
- Traveling salesman problem
- Assignment problem
- Subset problems

---

## Implementation Techniques

### Basic Memoization Template

```
memo = {}

Function solve(state):
    if base_case(state):
        return base_result

    if state in memo:
        return memo[state]

    result = compute_result_from_subproblems(state)
    memo[state] = result
    return result
```

### Basic Tabulation Template

```
Function solve(n):
    dp = array of appropriate size
    Initialize base cases

    for each state in order:
        dp[state] = compute from previous states

    return dp[final_state]
```

### Space Optimization

Many DP problems only need last few states:

```
# Instead of full array:
dp = [0] * n

# Use only necessary variables:
prev2 = base_case1
prev1 = base_case2

for i in range(2, n):
    current = prev1 + prev2
    prev2 = prev1
    prev1 = current
```

---

## Time & Space Complexity

### General Analysis:

**Time Complexity:** O(number of states × time per state)
- Number of states = size of DP table
- Time per state = time to compute from subproblems

**Space Complexity:** O(number of states)
- Can often be optimized if only recent states needed

**Examples:**
- Fibonacci: O(n) time, O(n) space → O(1) space optimized
- LCS: O(m×n) time, O(m×n) space → O(min(m,n)) optimized
- 0/1 Knapsack: O(n×W) time, O(n×W) space → O(W) optimized

---

## Problem-Solving Steps

### Step-by-Step Approach:

1. **Identify if it's a DP problem**
   - Optimal substructure?
   - Overlapping subproblems?
   - Optimization or counting problem?

2. **Define the state**
   - What parameters uniquely identify a subproblem?
   - What does dp[i] or dp[i][j] represent?

3. **Find the recurrence relation**
   - How to compute current state from previous states?
   - What are the transitions?

4. **Identify base cases**
   - What are the simplest subproblems?
   - What are their direct answers?

5. **Determine computation order**
   - Which subproblems need to be solved first?
   - Top-down or bottom-up?

6. **Implement and optimize**
   - Code the solution
   - Optimize space if possible

---

## Real-World Applications

1. **Bioinformatics**
   - DNA sequence alignment
   - Protein folding
   - Gene prediction

2. **Economics & Finance**
   - Portfolio optimization
   - Risk management
   - Resource allocation

3. **Operations Research**
   - Production planning
   - Inventory management
   - Scheduling

4. **Computer Science**
   - Compiler optimization
   - Database query optimization
   - Text processing (spell check, autocorrect)

5. **Artificial Intelligence**
   - Reinforcement learning
   - Game playing (chess, go)
   - Path finding

---

## Problem Statements

### Beginner Level

#### Problem 1: Fibonacci Number
**Difficulty:** Beginner

**Problem Statement:**
The Fibonacci numbers form a sequence where each number is the sum of the two preceding ones, starting from 0 and 1. Given n, calculate F(n).

**Example:**
```
Input: n = 4
Output: 3
Explanation: F(4) = F(3) + F(2) = 2 + 1 = 3

Input: n = 10
Output: 55
```

**Constraints:**
- 0 ≤ n ≤ 30

**Hints:**
1. Define state: dp[i] = ith Fibonacci number
2. Recurrence: dp[i] = dp[i-1] + dp[i-2]
3. Base cases: dp[0] = 0, dp[1] = 1

**Test Cases:**
```
Test 1: n=0 → Expected: 0
Test 2: n=1 → Expected: 1
Test 3: n=2 → Expected: 1
Test 4: n=5 → Expected: 5
```

**Practice Platform:** LeetCode #509

---

#### Problem 2: Climbing Stairs
**Difficulty:** Beginner

**Problem Statement:**
You are climbing a staircase with n steps. Each time you can climb 1 or 2 steps. In how many distinct ways can you climb to the top?

**Example:**
```
Input: n = 3
Output: 3
Explanation: 1+1+1, 1+2, 2+1

Input: n = 5
Output: 8
```

**Constraints:**
- 1 ≤ n ≤ 45

**Hints:**
1. To reach step n, you came from step n-1 or n-2
2. dp[i] = number of ways to reach step i
3. dp[i] = dp[i-1] + dp[i-2]

**Test Cases:**
```
Test 1: n=1 → Expected: 1
Test 2: n=2 → Expected: 2
Test 3: n=4 → Expected: 5
```

**Practice Platform:** LeetCode #70

---

### Easy Level

#### Problem 3: Min Cost Climbing Stairs
**Difficulty:** Easy

**Problem Statement:**
You are given an integer array cost where cost[i] is the cost of ith step. Once you pay the cost, you can climb one or two steps. You can start from index 0 or 1. Return minimum cost to reach the top.

**Example:**
```
Input: cost = [10,15,20]
Output: 15
Explanation: Start at index 1, pay 15, climb two steps

Input: cost = [1,100,1,1,1,100,1,1,100,1]
Output: 6
```

**Constraints:**
- 2 ≤ cost.length ≤ 1000
- 0 ≤ cost[i] ≤ 999

**Hints:**
1. dp[i] = minimum cost to reach step i
2. dp[i] = cost[i] + min(dp[i-1], dp[i-2])
3. Answer is min(dp[n-1], dp[n-2])

**Test Cases:**
```
Test 1: [10,15] → Expected: 10
Test 2: [1,2,3,4,5] → Expected: 6
```

**Practice Platform:** LeetCode #746

---

#### Problem 4: House Robber
**Difficulty:** Easy

**Problem Statement:**
You are a robber planning to rob houses along a street. Each house has amount of money. Adjacent houses have security systems that alert police if two adjacent houses are broken into on the same night. Given array representing money in each house, return maximum amount you can rob tonight without alerting police.

**Example:**
```
Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (1) and house 3 (3), total = 4

Input: nums = [2,7,9,3,1]
Output: 12
Explanation: Rob house 1 (2), house 3 (9), and house 5 (1), total = 12
```

**Constraints:**
- 1 ≤ nums.length ≤ 100
- 0 ≤ nums[i] ≤ 400

**Hints:**
1. At each house, decide: rob it or skip it
2. dp[i] = max money robbing up to house i
3. dp[i] = max(dp[i-1], dp[i-2] + nums[i])

**Test Cases:**
```
Test 1: [1] → Expected: 1
Test 2: [1,2] → Expected: 2
Test 3: [2,1,1,2] → Expected: 4
```

**Practice Platform:** LeetCode #198

---

#### Problem 5: Maximum Subarray
**Difficulty:** Easy

**Problem Statement:**
Given an integer array nums, find the contiguous subarray with the largest sum and return its sum.

**Example:**
```
Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6

Input: nums = [1]
Output: 1
```

**Constraints:**
- 1 ≤ nums.length ≤ 10^5
- -10^4 ≤ nums[i] ≤ 10^4

**Hints:**
1. Kadane's Algorithm
2. dp[i] = maximum sum ending at index i
3. dp[i] = max(nums[i], dp[i-1] + nums[i])

**Test Cases:**
```
Test 1: [5,4,-1,7,8] → Expected: 23
Test 2: [-1] → Expected: -1
Test 3: [-2,-1] → Expected: -1
```

**Practice Platform:** LeetCode #53

---

### Medium Level

#### Problem 6: Longest Increasing Subsequence
**Difficulty:** Medium

**Problem Statement:**
Given an integer array nums, return the length of the longest strictly increasing subsequence.

**Example:**
```
Input: nums = [10,9,2,5,3,7,101,18]
Output: 4
Explanation: [2,3,7,101] or [2,3,7,18]

Input: nums = [0,1,0,3,2,3]
Output: 4
```

**Constraints:**
- 1 ≤ nums.length ≤ 2500
- -10^4 ≤ nums[i] ≤ 10^4

**Hints:**
1. dp[i] = length of LIS ending at index i
2. For each i, check all j < i where nums[j] < nums[i]
3. dp[i] = max(dp[j] + 1) for all valid j
4. Answer = max(dp[i]) for all i

**Test Cases:**
```
Test 1: [1,3,6,7,9,4,10,5,6] → Expected: 6
Test 2: [7,7,7,7] → Expected: 1
```

**Practice Platform:** LeetCode #300

---

#### Problem 7: Coin Change
**Difficulty:** Medium

**Problem Statement:**
You are given an integer array coins representing coins of different denominations and an integer amount. Return the fewest number of coins needed to make up that amount. If impossible, return -1.

**Example:**
```
Input: coins = [1,2,5], amount = 11
Output: 3
Explanation: 11 = 5 + 5 + 1

Input: coins = [2], amount = 3
Output: -1
```

**Constraints:**
- 1 ≤ coins.length ≤ 12
- 1 ≤ coins[i] ≤ 2^31 - 1
- 0 ≤ amount ≤ 10^4

**Hints:**
1. Unbounded knapsack variant
2. dp[i] = minimum coins needed for amount i
3. dp[i] = min(dp[i-coin] + 1) for all coins ≤ i

**Test Cases:**
```
Test 1: coins=[1], amount=0 → Expected: 0
Test 2: coins=[1], amount=1 → Expected: 1
Test 3: coins=[1,3,4], amount=6 → Expected: 2 (3+3)
```

**Practice Platform:** LeetCode #322

---

#### Problem 8: Longest Common Subsequence
**Difficulty:** Medium

**Problem Statement:**
Given two strings text1 and text2, return the length of their longest common subsequence. A subsequence is a sequence that appears in the same relative order, but not necessarily contiguous.

**Example:**
```
Input: text1 = "abcde", text2 = "ace"
Output: 3
Explanation: LCS is "ace"

Input: text1 = "abc", text2 = "def"
Output: 0
```

**Constraints:**
- 1 ≤ text1.length, text2.length ≤ 1000
- text1 and text2 consist of only lowercase English characters

**Hints:**
1. 2D DP: dp[i][j] = LCS length of text1[0..i] and text2[0..j]
2. If text1[i] == text2[j]: dp[i][j] = dp[i-1][j-1] + 1
3. Else: dp[i][j] = max(dp[i-1][j], dp[i][j-1])

**Test Cases:**
```
Test 1: "a", "a" → Expected: 1
Test 2: "abc", "abc" → Expected: 3
Test 3: "abc", "def" → Expected: 0
```

**Practice Platform:** LeetCode #1143

---

#### Problem 9: Unique Paths
**Difficulty:** Medium

**Problem Statement:**
A robot is located at the top-left corner of an m x n grid. The robot can only move down or right. How many possible unique paths are there to reach the bottom-right corner?

**Example:**
```
Input: m = 3, n = 7
Output: 28

Input: m = 3, n = 2
Output: 3
```

**Constraints:**
- 1 ≤ m, n ≤ 100

**Hints:**
1. dp[i][j] = number of ways to reach cell (i,j)
2. dp[i][j] = dp[i-1][j] + dp[i][j-1]
3. Base case: dp[0][j] = 1, dp[i][0] = 1

**Test Cases:**
```
Test 1: m=1, n=1 → Expected: 1
Test 2: m=2, n=2 → Expected: 2
Test 3: m=1, n=5 → Expected: 1
```

**Practice Platform:** LeetCode #62

---

### Hard Level

#### Problem 10: Edit Distance
**Difficulty:** Hard

**Problem Statement:**
Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2. Operations allowed: insert, delete, replace a character.

**Example:**
```
Input: word1 = "horse", word2 = "ros"
Output: 3
Explanation:
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')

Input: word1 = "intention", word2 = "execution"
Output: 5
```

**Constraints:**
- 0 ≤ word1.length, word2.length ≤ 500
- word1 and word2 consist of lowercase English letters

**Hints:**
1. dp[i][j] = min operations to convert word1[0..i] to word2[0..j]
2. If chars match: dp[i][j] = dp[i-1][j-1]
3. Else: dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])

**Test Cases:**
```
Test 1: "", "" → Expected: 0
Test 2: "a", "b" → Expected: 1
Test 3: "abc", "abc" → Expected: 0
```

**Practice Platform:** LeetCode #72

---

#### Problem 11: Regular Expression Matching
**Difficulty:** Hard

**Problem Statement:**
Given string s and pattern p, implement regex matching with '.' (matches any single character) and '*' (matches zero or more of the preceding element).

**Example:**
```
Input: s = "aa", p = "a"
Output: false

Input: s = "aa", p = "a*"
Output: true

Input: s = "ab", p = ".*"
Output: true
```

**Constraints:**
- 1 ≤ s.length ≤ 20
- 1 ≤ p.length ≤ 30
- s contains only lowercase English letters
- p contains lowercase English letters, '.', and '*'

**Hints:**
1. dp[i][j] = whether s[0..i] matches p[0..j]
2. Handle '.' and '*' separately
3. For '*': match zero times OR match one+ times

**Test Cases:**
```
Test 1: s="a", p="a" → Expected: true
Test 2: s="a", p="." → Expected: true
Test 3: s="ab", p=".*c" → Expected: false
```

**Practice Platform:** LeetCode #10

---

#### Problem 12: Best Time to Buy and Sell Stock with Cooldown
**Difficulty:** Hard

**Problem Statement:**
You may complete as many transactions as you like with the following restrictions: After you sell, you cannot buy on the next day (cooldown). Find maximum profit.

**Example:**
```
Input: prices = [1,2,3,0,2]
Output: 3
Explanation: Buy at 1, sell at 2, cooldown, buy at 0, sell at 2

Input: prices = [1]
Output: 0
```

**Constraints:**
- 1 ≤ prices.length ≤ 5000
- 0 ≤ prices[i] ≤ 1000

**Hints:**
1. State machine DP with three states: hold, sold, rest
2. hold[i] = max profit on day i with stock in hand
3. sold[i] = max profit on day i just sold stock
4. rest[i] = max profit on day i with no stock, not in cooldown

**Test Cases:**
```
Test 1: [1,2] → Expected: 1
Test 2: [2,1] → Expected: 0
Test 3: [1,2,4] → Expected: 3
```

**Practice Platform:** LeetCode #309

---

### Expert Level

#### Problem 13: Burst Balloons
**Difficulty:** Expert

**Problem Statement:**
You are given n balloons, indexed from 0 to n-1. Each balloon has a number on it. You burst all balloons. If you burst ith balloon, you get nums[i-1] * nums[i] * nums[i+1] coins. Find maximum coins you can collect.

**Example:**
```
Input: nums = [3,1,5,8]
Output: 167
Explanation: [3,1,5,8] → [3,5,8] → [3,8] → [8] → []
```

**Constraints:**
- n == nums.length
- 1 ≤ n ≤ 300
- 0 ≤ nums[i] ≤ 100

**Hints:**
1. Think backwards: which balloon to burst last in range [i,j]?
2. dp[i][j] = max coins by bursting balloons in range (i,j)
3. Add padding: nums = [1] + nums + [1]

**Test Cases:**
```
Test 1: [1] → Expected: 1
Test 2: [1,5] → Expected: 10
```

**Practice Platform:** LeetCode #312

---

#### Problem 14: Palindrome Partitioning II
**Difficulty:** Expert

**Problem Statement:**
Given a string s, partition s such that every substring is a palindrome. Return minimum cuts needed.

**Example:**
```
Input: s = "aab"
Output: 1
Explanation: "aa" | "b"

Input: s = "a"
Output: 0
```

**Constraints:**
- 1 ≤ s.length ≤ 2000
- s consists of lowercase English letters only

**Hints:**
1. dp[i] = minimum cuts for s[0..i]
2. Pre-compute palindrome table
3. For each i, check all j where s[j..i] is palindrome

**Test Cases:**
```
Test 1: "aba" → Expected: 0
Test 2: "abc" → Expected: 2
```

**Practice Platform:** LeetCode #132

---

#### Problem 15: Distinct Subsequences
**Difficulty:** Expert

**Problem Statement:**
Given two strings s and t, return the number of distinct subsequences of s which equals t.

**Example:**
```
Input: s = "rabbbit", t = "rabbit"
Output: 3
Explanation: Three ways to form "rabbit"

Input: s = "babgbag", t = "bag"
Output: 5
```

**Constraints:**
- 1 ≤ s.length, t.length ≤ 1000
- s and t consist of English letters

**Hints:**
1. dp[i][j] = number of ways to form t[0..j] from s[0..i]
2. If s[i] == t[j]: dp[i][j] = dp[i-1][j-1] + dp[i-1][j]
3. Else: dp[i][j] = dp[i-1][j]

**Test Cases:**
```
Test 1: s="a", t="a" → Expected: 1
Test 2: s="ab", t="a" → Expected: 1
```

**Practice Platform:** LeetCode #115

---

## Related Topics

### Prerequisites:
- Recursion
- Arrays
- Mathematics

### Related Techniques:
- Greedy Algorithms (when DP not needed)
- Divide and Conquer
- Backtracking

### Advanced DP Topics:
- DP on Trees
- Digit DP
- Bitmask DP
- DP Optimizations (Convex Hull Trick, Divide & Conquer Optimization)

---

## Summary

Dynamic Programming is essential for:
- ✅ Optimization problems
- ✅ Counting problems
- ✅ Decision-making problems
- ✅ Reducing exponential to polynomial time

**Key Takeaways:**
1. Identify optimal substructure and overlapping subproblems
2. Define state clearly
3. Find recurrence relation
4. Choose memoization or tabulation
5. Optimize space when possible

---

**Happy Learning! 🎓**

*Master DP, and you'll solve problems that seem impossible at first!*
