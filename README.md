# 🔐 Security Lab — Cryptography Demos in C++

A collection of educational C++ programs demonstrating classical and modern cryptographic algorithms for learning and experimentation.

> ⚠️ **Educational purposes only!** These implementations use simplified math and are not suitable for production use. Always use established cryptographic libraries (OpenSSL, libsodium, Botan) for real-world security.

---

## 📚 Table of Contents

- [Overview](#overview)
- [Programs Included](#programs-included)

---

## 🎯 Overview

This repository contains hands-on implementations of cryptographic primitives, organized into three categories:

**Classical Ciphers** — Historical encryption techniques  
**Public-Key Cryptography** — RSA and ElGamal systems  
**Modern Cryptography** — Elliptic curve implementations

All programs are written in modern C++ with inline comments explaining the mathematics and algorithms.

---

## 📂 Programs Included

### 🔤 Classical Ciphers
| File | Description | Key Concept |
|------|-------------|-------------|
| `Caesar_cipher.cpp` | Caesar & Vigenère shift ciphers | Character shifting with modular arithmetic |
| `Verman_cipher.cpp` | Vernam cipher (One-Time Pad) | XOR-based perfect secrecy |
| `transpose_cipher.cpp` | Columnar transposition | Permutation-based encryption |

### 🔑 RSA Cryptosystem
| File | Description | Key Concept |
|------|-------------|-------------|
| `RSA_encryption.cpp` | Basic RSA encryption/decryption | Modular exponentiation, Euler's theorem |
| `RSA_signature.cpp` | RSA digital signatures | Sign & verify with private/public keys |
| `RSA_Product.cpp` | Multiplicative homomorphism demo | Property: E(m₁) × E(m₂) = E(m₁ × m₂) |
| `Rsa_signature_plaintext_attack.cpp` | Signature forgery demo | Educational weakness exploration |

### 🛡️ ElGamal Cryptosystem
| File | Description | Key Concept |
|------|-------------|-------------|
| `Elgamal_encryption.cpp` | ElGamal public-key encryption | Discrete logarithm problem |
| `Elgamal_signature.cpp` | ElGamal signatures | Schnorr-like signature scheme |
| `Elgamal_Product_Rerandomization.cpp` | Homomorphic properties | Ciphertext product & rerandomization |

### 📐 Elliptic Curve Cryptography
| File | Description | Key Concept |
|------|-------------|-------------|
| `Elliptic_curve_encryption.cpp` | EC-ElGamal encryption | Point addition, scalar multiplication |
