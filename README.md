# RSA Cryptanalysis: Fermat Factorization Attack

![C++](https://img.shields.io/badge/language-C%2B%2B-blue)
![Algorithm](https://img.shields.io/badge/algorithm-Fermat%20Factorization-orange)
![License](https://img.shields.io/badge/license-MIT-green)

A educational C++ implementation demonstrating a classical cryptanalytic attack on RSA. This program shows how choosing two **close prime numbers** (p and q) when generating RSA keys makes the encryption vulnerable to **Fermat's factorization method**.

## 🎯 Overview

RSA security relies on the practical difficulty of factoring large composite numbers. However, if the two prime factors (p and q) are close to each other, an attacker can efficiently recover them using Fermat's factorization:

> `n = p * q = a² - b² = (a-b)(a+b)`, where `a = (p+q)/2` and `b = (q-p)/2`

This program:
1. **Generates** two close prime numbers of specified bit length
2. **Performs** Fermat's factorization attack on their product
3. **Demonstrates** the vulnerability in real-time with progress tracking

## ✨ Features

- **Miller-Rabin Primality Test**: Probabilistic prime checking with configurable accuracy (k rounds)
- **Close Prime Generation**: Generates primes with a small difference (search space up to 2²⁰)
- **Fermat's Factorization**: Implements the classical algorithm with detailed step tracking
- **Performance Measurement**: Tracks execution time with chrono library
- **Educational Output**: Real-time progress indicators showing each step of the search process
- **Automatic Verification**: Confirms that found factors match the original primes

## 🧮 Algorithm Details

### Miller-Rabin Test
The program uses 5 rounds of Miller-Rabin testing by default, providing high confidence that generated numbers are indeed prime.

### Fermat's Factorization
The attack works by searching for integers a and b such that:
- Start with `a = ceil(√n)`
- Compute `b² = a² - n`
- Check if `b²` is a perfect square
- If not, increment `a` and repeat
- When a perfect square is found, factors are `(a-b)` and `(a+b)`

## The program will:
- Generate two close 30-bit primes (configurable in code)
- Display the generated RSA parameters (p, q, n)
- Run Fermat's factorization attack on n
- Show the step-by-step search process
- Display results and verification

## 📊 Performance

Fermat's factorization is extremely efficient when p and q are close:
- Difference ~10²: Factoring completes in milliseconds
- Difference ~10⁴: Takes a few seconds
- Difference ~10⁶: May take minutes to hours
The search complexity is approximately O(|p-q|²/8√n) steps.

## ⚠️ Security Implications

This demonstration highlights a critical requirement for secure RSA key generation:
- ✅ DO generate primes independently and randomly
- ✅ DO ensure a large difference between p and q
- ❌ DON'T generate primes that are close together
- ❌ DON'T use prime numbers generated sequentially
Modern RSA implementations use secure random prime generation with sufficient distance between factors to prevent this attack.

##📚 Educational Value

This project is excellent for learning about:
- RSA cryptosystem fundamentals
- Prime number theory
- Fermat's factorization method
- Time complexity of cryptographic attacks
- Secure key generation practices
