# Number Theory for DSA

## Prime Numbers

### Sieve of Eratosthenes
```
Find all primes up to n
Time: O(n log log n)
Space: O(n)
```

### Prime Factorization
```
Time: O(√n)
```

## GCD & LCM

### Euclidean Algorithm
```
GCD(a, b) = GCD(b, a mod b)
Time: O(log min(a, b))
```

### Extended Euclidean Algorithm
Find x, y such that ax + by = GCD(a, b)

## Modular Arithmetic

### Fast Exponentiation
```
Calculate a^b mod m
Time: O(log b)
```

### Modular Inverse
```
For prime modulo: a^(-1) = a^(p-2) mod p (Fermat's Little Theorem)
```

## Common Problems:
- Count Primes - LeetCode #204
- Power(x, n) - LeetCode #50
- Super Pow - LeetCode #372
- Nth Digit - LeetCode #400

**Happy Learning! 🎓**
