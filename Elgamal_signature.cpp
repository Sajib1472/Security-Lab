/*
    ElGamal Signature demo (educational implementation)

    Purpose:
    - Demonstrates how to generate and verify an ElGamal-style signature.
    - This is a textbook/example implementation for learning and is NOT
        secure for production use (no cryptographic RNG, small integer types,
        and no hashing/padding of messages).

    High-level flow:
    1) Read a prime p and find a generator g of Z_p*.
    2) Read private key x and compute public key y = g^x mod p.
    3) Choose a random-like k with gcd(k, p-1) = 1, compute r = g^k mod p.
    4) Compute s = k^{-1} * (M - x*r) mod (p-1).
    5) Signature is (r, s). Verify by checking g^M ?= y^r * r^s (mod p).

    Variable mapping:
    - p : prime modulus
    - g : generator of multiplicative group modulo p
    - x : private key (secret)
    - y : public key = g^x mod p
    - k : ephemeral nonce (must be invertible mod p-1)
    - M : integer message to sign (in practice, sign a hash(M))
    - r, s : signature components

    Notes:
    - Uses long long for simplicity: only for tiny toy primes. Real systems use bignums.
    - Do not reuse k between signatures: reuse leaks x.
*/

#include <bits/stdc++.h>
using namespace std;

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

// check if g is generator of Zp*
bool isGenerator(long long g, long long p) {
    long long phi = p - 1;
    vector<long long> factors;

    long long n = phi;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            factors.push_back(i);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) factors.push_back(n);

    for (int i = 0; i < factors.size(); i++) {
        long long f = factors[i];
        if (power(g, phi / f, p) == 1) {
            return false;
        }
    }

    return true;
}

int main() {
    long long p;
    cout << "Enter a large prime p: ";
    cin >> p;

    // find generator starting from 100
    long long g = 100;
    while (g < p && !isGenerator(g, p)) g++;
    if (g >= p) {
        cout << "No generator found.\n";
        return 0;
    }

    long long x;
    cout << "Enter private key x (1 <= x <= p-2): ";
    cin >> x;

    long long M;
    cout << "Enter message (as number): ";
    cin >> M;

    // public key
    long long y = power(g, x, p);

    // auto-generate k starting from 300 until gcd(k, p-1)=1
    long long k = 55;
    while (k <= p - 2 && gcd(k, p - 1) != 1) {
        k++;
    }
    if (k > p - 2) {
        cout << "No valid k found.\n";
        return 0;
    }

    cout << "Chosen random k = " << k << "\n";

    // signature generation
    long long r = power(g, k, p);
    long long k_inv = modInverse(k, p - 1);
    long long s = (k_inv * ((M - (x * r) % (p - 1)) + (p - 1))) % (p - 1); // ensure non-negative

    cout << "\nPublic Key: (p=" << p << ", g=" << g << ", y=" << y << ")\n";
    cout << "Private Key: x = " << x << "\n";
    cout << "Signature: (r=" << r << ", s=" << s << ")\n";

    // verification
    long long v1 = power(g, M, p);
    long long v2 = (power(y, r, p) * power(r, s, p)) % p;

    cout << "\nVerification:\n";
    cout << "g^M mod p = " << v1 << "\n";
    cout << "y^r * r^s mod p = " << v2 << "\n";

    if (v1 == v2)
        cout << "✅ Signature is VALID\n";
    else
        cout << "❌ Signature is INVALID\n";

    return 0;
}