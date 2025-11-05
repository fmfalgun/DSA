# Bit Manipulation - Complete Guide

## Introduction

**Bit Manipulation** involves using bitwise operators to directly manipulate bits in binary representation of numbers. It's one of the fastest operations as it directly works at the CPU level.

## Bitwise Operators

### 1. AND (&)
```
5 & 3 = 1
  0101
& 0011
-------
  0001
```
**Use:** Check if bit is set, clear bits, find even/odd

### 2. OR (|)
```
5 | 3 = 7
  0101
| 0011
-------
  0111
```
**Use:** Set bits

### 3. XOR (^)
```
5 ^ 3 = 6
  0101
^ 0011
-------
  0110
```
**Properties:**
- a ^ a = 0
- a ^ 0 = a
- a ^ b ^ a = b (cancellation)

**Use:** Find unique element, swap without temp variable

### 4. NOT (~)
```
~5 = -6 (in two's complement)
~0101 = 1010
```

### 5. Left Shift (<<)
```
5 << 1 = 10  (multiply by 2)
0101 << 1 = 1010
```
**Effect:** Multiply by 2^n

### 6. Right Shift (>>)
```
5 >> 1 = 2  (divide by 2)
0101 >> 1 = 0010
```
**Effect:** Divide by 2^n

## Common Bit Manipulation Tricks

### Check if Number is Power of 2
```
n & (n-1) == 0
Example: 8 & 7 = 1000 & 0111 = 0
```

### Count Number of Set Bits
```
Function countSetBits(n):
    count = 0
    while n:
        count += n & 1
        n >>= 1
    return count

// Brian Kernighan's Algorithm:
Function countSetBits(n):
    count = 0
    while n:
        n &= (n-1)  // Removes rightmost set bit
        count++
    return count
```

### Get ith Bit
```
(n >> i) & 1
```

### Set ith Bit
```
n | (1 << i)
```

### Clear ith Bit
```
n & ~(1 << i)
```

### Toggle ith Bit
```
n ^ (1 << i)
```

### Clear All Bits from MSB to ith Bit
```
n & ((1 << i) - 1)
```

### Check if Bit is Set
```
(n & (1 << i)) != 0
```

### Swap Two Numbers Without Temp
```
a ^= b
b ^= a
a ^= b
```

### Find Missing Number (1 to n)
```
XOR all numbers from 1 to n and XOR with array elements
Missing number will remain
```

### Find Two Non-Repeating Elements
```
1. XOR all elements → gives xor of two unique elements
2. Find rightmost set bit in xor
3. Divide elements into two groups based on this bit
4. XOR each group separately
```

## Problem Statements

### Beginner: Number of 1 Bits
**Problem:** Count number of 1 bits in unsigned integer.
**Hints:** Use n & (n-1) to clear rightmost set bit
**Platform:** LeetCode #191

### Easy: Single Number
**Problem:** Find element appearing once when others appear twice.
**Hints:** XOR all elements (duplicates cancel)
**Platform:** LeetCode #136

### Easy: Power of Two
**Problem:** Check if n is power of 2.
**Hints:** n & (n-1) == 0 and n > 0
**Platform:** LeetCode #231

### Medium: Single Number II
**Problem:** Find element appearing once when others appear thrice.
**Hints:** Count bits at each position, take modulo 3
**Platform:** LeetCode #137

### Medium: Counting Bits
**Problem:** Count 1 bits for numbers from 0 to n.
**Hints:** bits[i] = bits[i>>1] + (i&1)
**Platform:** LeetCode #338

### Medium: Bitwise AND of Numbers Range
**Problem:** Bitwise AND of all numbers in range [left, right].
**Hints:** Find common prefix
**Platform:** LeetCode #201

### Hard: Maximum XOR of Two Numbers
**Problem:** Find max XOR of two numbers in array.
**Hints:** Build trie of binary representations
**Platform:** LeetCode #421

### Expert: Minimum XOR Sum of Two Arrays
**Problem:** Minimize XOR sum by rearranging one array.
**Hints:** Bitmask DP with assignment
**Platform:** LeetCode #1879

## Bit Manipulation Patterns

### Pattern 1: XOR Properties
Finding unique elements, detecting duplicates

### Pattern 2: Counting/Checking Bits
Hamming weight, checking powers

### Pattern 3: Bitmask DP
Using bits to represent subsets

### Pattern 4: Bit Tricks
Optimization using bitwise operations

## Time Complexity

Most bit operations: **O(1)**
Counting bits: **O(log n)** or **O(number of set bits)**

## Real-World Applications

1. **Cryptography:** XOR cipher, hash functions
2. **Graphics:** Color manipulation, alpha blending
3. **Networking:** IP address masking
4. **Databases:** Bitmap indexes
5. **Compression:** Huffman coding
6. **Operating Systems:** Permissions (rwx = 111)

## Common Use Cases

- **Space optimization:** Store multiple boolean flags in one integer
- **Fast arithmetic:** Multiply/divide by powers of 2
- **Set operations:** Union, intersection using bits
- **Permutations:** Generate all subsets using bitmask

## Interview Tips

1. **Know basic operations cold**
2. **Remember XOR properties**
3. **Practice common tricks**
4. **Visualize binary representation**
5. **Consider edge cases (0, negative numbers)**

## Summary

Bit manipulation is powerful for:
- ✅ Fast operations
- ✅ Space optimization
- ✅ Clever algorithmic solutions

**Key Takeaway:** Master the basics (AND, OR, XOR, shifts) and common patterns. They appear frequently in interviews!

**Happy Learning! 🎓**
