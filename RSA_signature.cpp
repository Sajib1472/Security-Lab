/*
    RSA_signature.cpp

    Purpose:
    - Educational demonstration of RSA-based signatures (textbook method).
    - This program generates RSA keys (p,q -> n, phi), picks e and computes d,
        then shows a simple signature and verification using modular exponentiation.

    Important notes:
    - This is NOT a secure implementation for real use: it uses fixed-size long long,
        no padding or hashing of messages, and no secure randomness.
    - For production use, use a proper crypto library (OpenSSL, libsodium) and
        follow standards (RSA-PSS, hashing, correct key sizes).
*/

#include <bits/stdc++.h>
using namespace std;

// Compute greatest common divisor (Euclid's algorithm)
long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// fast modular exponentiation
long long power(long long a, long long b, long long mod) {
    long long res = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1) res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}

// modular inverse using Extended Euclid
long long modInverse(long long a, long long m) {
    long long m0 = m, y = 0, x = 1;
    if (m == 1) return 0;

    while (a > 1) {
        long long q = a / m;
        long long t = m;
        m = a % m, a = t;
        t = y;
        y = x - q * y;
        x = t;
    }

    if (x < 0) x += m0;
    return x;
}

int main() {
    long long p, q;
    cout << "Enter two distinct prime numbers (p and q): ";
    cin >> p >> q;

    long long n = p * q;
    long long phi = (p - 1) * (q - 1);

    long long e = 3;
    while (e < phi && gcd(e, phi) != 1) {
        e += 2; // increment by 2 to keep e odd
    }
    if (e >= phi) {
        cout << "No valid e found.\n";
        return 0;
    }

    long long d = modInverse(e, phi);

    cout << "\nPublic Key: (n = " << n << ", e = " << e << ")\n";
    cout << "Private Key: (d = " << d << ", n = " << n << ")\n";

    long long M;
    cout << "\nEnter message as a number (M < n): ";
    cin >> M;

    // ---- Signature Generation ----
    long long S = power(M, d, n);
    cout << "\nSignature (S): " << S << "\n";

    // ---- Signature Verification ----
    long long V = power(S, e, n);
    cout << "\nVerification:\n";
    cout << "Recovered message = " << V << "\n";

    if (V == M)
        cout << "✅ Signature is VALID\n";
    else
        cout << "❌ Signature is INVALID\n";

    return 0;
}
