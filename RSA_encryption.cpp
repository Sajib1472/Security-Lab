/*
    RSA encryption demo (textbook implementation)

    Purpose:
    - Small educational implementation of RSA key generation, encryption and decryption.
    - NOT suitable for production: uses fixed-size `long long`, no padding, and simple input.

    Flow overview (main):
    1) Read two distinct primes p and q.
    2) Compute n = p * q and phi = (p-1)*(q-1).
    3) Choose public exponent e such that gcd(e, phi) == 1.
    4) Compute private exponent d = e^{-1} mod phi.
    5) Read message M (integer < n), compute ciphertext C = M^e mod n.
    6) Decrypt with M = C^d mod n.

    Helper functions:
    - gcd: greatest common divisor (Euclid)
    - power: fast modular exponentiation (square-and-multiply)
    - modInverse: modular inverse using Extended Euclidean algorithm

    Notes:
    - This code is for learning and testing with small numbers only.
    - For real RSA use big-integer libraries (OpenSSL, GMP) and secure padding (OAEP).
*/

#include <bits/stdc++.h>
using namespace std;

// Compute greatest common divisor (Euclid's algorithm)
long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Fast modular exponentiation: computes (a^b) % mod in O(log b) time
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

// Modular inverse using the Extended Euclidean Algorithm
// Returns x such that (a * x) % m == 1 when gcd(a,m) == 1
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

    // Encryption
    long long C = power(M, e, n);
    cout << "Ciphertext: " << C << "\n";

    // Decryption
    long long decrypted = power(C, d, n);
    cout << "Decrypted Message: " << decrypted << "\n";

    return 0;
}
