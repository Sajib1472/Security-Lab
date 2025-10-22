# 🔐 Security Lab — Cryptography Demos in C++

A collection of educational C++ programs demonstrating classical and modern cryptographic algorithms for learning and experimentation.

> ⚠️ **Educational purposes only!** These implementations use simplified math and are not suitable for production use. Always use established cryptographic libraries (OpenSSL, libsodium, Botan) for real-world security.

---

## 📚 Table of Contents

- [Overview](#overview)
- [Programs Included](#programs-included)
- [Quick Start](#quick-start)
- [Build & Run](#build--run)
- [Usage Examples](#usage-examples)
- [Security Notes](#security-notes)
- [Known Issues & Improvements](#known-issues--improvements)
- [Git Workflow](#git-workflow)
- [Contributing](#contributing)
- [License](#license)

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

---

## 🚀 Quick Start

**Prerequisites:**
- C++ compiler with C++11 or later (g++, clang++)
- Basic familiarity with modular arithmetic

**Clone and build:**

```bash
git clone https://github.com/Sajib1472/Security-Lab.git
cd Security-Lab

# Compile a single program
g++ -std=c++17 -O2 Caesar_cipher.cpp -o caesar
./caesar

# Or compile all programs at once
mkdir -p bin
for f in *.cpp; do 
  g++ -std=c++17 -O2 "$f" -o "bin/$(basename "$f" .cpp)"
done
```

---

## 🔨 Build & Run

### Single Program

```bash
# Compile and run Caesar cipher
g++ -std=c++17 -O2 Caesar_cipher.cpp -o caesar
./caesar
```

### Batch Compilation

```bash
# Compile all programs into bin/ directory
mkdir -p bin
for f in *.cpp; do 
  echo "Compiling $f..."
  g++ -std=c++17 -Wall -O2 "$f" -o "bin/$(basename "$f" .cpp)" || break
done

# List compiled programs
ls -lh bin/
```

### Makefile (Optional)

Create a `Makefile` for easier builds:

```makefile
CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2
BINDIR = bin
SOURCES = $(wildcard *.cpp)
TARGETS = $(patsubst %.cpp,$(BINDIR)/%,$(SOURCES))

all: $(BINDIR) $(TARGETS)

$(BINDIR):
	mkdir -p $(BINDIR)

$(BINDIR)/%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(BINDIR)

.PHONY: all clean
```

Then simply run `make` to build everything or `make clean` to remove binaries.

---

## 💡 Usage Examples

### Caesar Cipher
```bash
./bin/Caesar_cipher
# Input: HELLO
# Key: 3
# Output: KHOOR
```

### RSA Encryption
```bash
./bin/RSA_encryption
# The program demonstrates:
# - Prime selection (p, q)
# - Public/private key generation (e, d, n)
# - Encryption: c = m^e mod n
# - Decryption: m = c^d mod n
```

### ElGamal Encryption
```bash
./bin/Elgamal_encryption
# Demonstrates:
# - Generator selection for prime p
# - Key generation (public h, private x)
# - Random k selection
# - Encryption: (c1, c2) pair
# - Decryption using discrete log
```

### Transpose Cipher
```bash
./bin/transpose_cipher
# Input: "HELLO WORLD"
# Key (columns): 4
# Creates matrix and reads column-wise
```

### Vernam Cipher (One-Time Pad)
```bash
./bin/Verman_cipher
# XORs plaintext with key
# Outputs in hexadecimal
# Perfect secrecy when key is truly random
```

### Elliptic Curve
```bash
./bin/Elliptic_curve_encryption
# Demonstrates:
# - Point arithmetic (add, double, multiply)
# - Base point selection
# - EC-ElGamal encryption/decryption
```

---

## 🔒 Security Notes

### ⚠️ Educational Use Only

These implementations are **NOT secure** for production use because:

1. **Small Parameters** — Uses small primes/keys that can be easily factored or brute-forced
2. **Naive Integer Math** — No big-integer library; prone to overflow and side-channel attacks
3. **Weak Randomness** — Uses `rand()` instead of cryptographically secure RNGs
4. **No Padding** — Missing OAEP, PSS, or other padding schemes required for real RSA
5. **Timing Attacks** — Not constant-time; vulnerable to timing side channels
6. **No Input Validation** — Minimal error checking and sanitization

### ✅ For Real Cryptography, Use:

- **OpenSSL** — Industry standard, widely audited
- **libsodium** — Modern, easy-to-use, misuse-resistant
- **Botan** — C++ cryptographic library
- **BoringSSL** — Google's fork of OpenSSL
- **Crypto++** — C++ class library of cryptographic schemes

### 📖 Learning Path

1. Start with classical ciphers (Caesar, Vigenère, Vernam)
2. Understand modular arithmetic (RSA examples)
3. Study discrete logarithm problem (ElGamal)
4. Explore elliptic curves (modern crypto foundation)
5. Read *Applied Cryptography* by Bruce Schneier and *Cryptography Engineering*

---

## 🐛 Known Issues & Improvements

### Current Limitations

| Issue | Impact | Suggested Fix |
|-------|--------|---------------|
| **No input validation** | Empty keys, invalid inputs crash programs | Add checks for empty strings, numeric validation |
| **`ctype` on signed char** | Undefined behavior on some platforms | Cast to `unsigned char` before calling `isalpha()`, etc. |
| **Native int overflow** | RSA/ElGamal fail with realistic key sizes | Use GMP or Boost.Multiprecision |
| **Weak randomness** | Predictable `k` values in ElGamal/signatures | Use `std::random_device` + platform secure RNG |
| **VLA usage** | Non-portable C++ (some files) | Replace with `std::vector` (already done in `transpose_cipher.cpp`) |
| **No constant-time ops** | Vulnerable to timing attacks | Implement constant-time comparison/exponentiation |

### Roadmap for Improvements

- [ ] Add comprehensive input validation to all programs
- [ ] Integrate GMP library for big-integer support
- [ ] Add unit tests with known test vectors
- [ ] Implement constant-time utilities
- [ ] Add GitHub Actions CI for automatic compilation
- [ ] Create interactive demo mode with pre-loaded examples

---

## 📤 Git Workflow

### Push Only Source Files

To avoid committing binaries and build artifacts:

**1. Create `.gitignore`:**

```bash
cat > .gitignore << 'EOF'
# Compiled binaries
bin/
*.out
*.exe
*.o
*.obj
a.out

# macOS
.DS_Store
.AppleDouble
.LSOverride

# IDE
.vscode/
.idea/
*.swp
*.swo
*~

# Build artifacts
build/
cmake-build-*/
EOF
```

**2. Stage and commit source files:**

```bash
# Add only C++ source files and documentation
git add *.cpp *.h README.md .gitignore

# Commit with descriptive message
git commit -m "Add cryptography demos with documentation"

# Push to remote
git push -u origin main
```

### Remove Already-Committed Binaries

If you accidentally committed binaries:

```bash
# Remove from tracking but keep local copies
git rm --cached bin/*
git rm --cached *.out

# Commit the removal
git commit -m "Remove compiled binaries from tracking"

# Push changes
git push
```

### Clean Git History (Advanced)

To completely remove large files from history:

```bash
# Install git-filter-repo (recommended over filter-branch)
brew install git-filter-repo  # macOS
# or: pip install git-filter-repo

# Backup your repo first!
cp -r ../Security-Lab ../Security-Lab-backup

# Remove all files in bin/ from history
git filter-repo --path bin/ --invert-paths

# Force push (only if you're sure!)
git push origin --force --all
```

⚠️ **Warning:** History rewriting affects all collaborators. Coordinate with your team first!

---

## 🤝 Contributing

Contributions are welcome! Here are some ideas:

### Potential Enhancements
- **Tests:** Add sample inputs/outputs for each program
- **CI/CD:** GitHub Actions workflow for automated builds
- **Documentation:** Step-by-step algorithm explanations
- **Visualization:** Add ASCII diagrams for encryption flows
- **More Algorithms:** AES demo, Diffie-Hellman, DSA
- **Performance:** Benchmark comparisons between algorithms

### How to Contribute
1. Fork the repository
2. Create a feature branch (`git checkout -b feature/new-cipher`)
3. Add your changes with clear comments
4. Test your code compiles and runs
5. Commit with descriptive messages
6. Push and create a Pull Request

---

## 📄 License

This project is educational and provided **as-is** for learning purposes.

**Recommended:** Add a permissive license (MIT) to make it clear others can learn from and modify the code:

```
MIT License - See LICENSE file for details
```

To add MIT license:

```bash
cat > LICENSE << 'EOF'
MIT License

Copyright (c) 2025 Security Lab Contributors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
EOF
```

---

## 📞 Contact & Support

**Questions or suggestions?**  
Open an issue on GitHub or reach out through pull requests.

**Learning Resources:**
- [Cryptography I - Coursera](https://www.coursera.org/learn/crypto)
- [The Cryptopals Challenges](https://cryptopals.com/)
- [Practical Cryptography for Developers](https://cryptobook.nakov.com/)

---

## 🌟 Acknowledgments

These implementations are based on standard cryptographic algorithms and educational materials. They're designed to help students understand the mathematical foundations of cryptography through hands-on coding.

**Happy Learning! 🎓🔐**
If you want me to add examples, tests, or CI, tell me which files to prioritize and whether you want sample inputs or automated tests.
