/*
    ElGamal encryption demo (textbook, educational implementation)

    What this file does:
    - Implements basic ElGamal public-key encryption and decryption over Z_p (integers mod p).
    - It asks the user for a prime p, selects a generator g, reads a private key x and a session key k,
        then encrypts a numeric message M and decrypts it back.

    Important variables / mapping:
    - p : prime modulus (user input)
    - g : generator of the multiplicative group Z_p* (found by the program)
    - x : private key (user input)
    - h : public key component h = g^x mod p
    - k : session/ephemeral key (random-like value used once per message)
    - M : plaintext message represented as an integer (0 <= M < p)
    - C1 = g^k mod p, C2 = M * h^k mod p  (ciphertext pair)

    Security notes (educational; not production):
    - This is textbook ElGamal (no padding). Do NOT use this code for real communications.
    - Uses `long long` and `bits/stdc++.h` for simplicity — real implementations use big-integer libraries (GMP/OpenSSL).
    - The program searches for a generator by factoring p-1 — practical only for small p in demos.

    File structure:
    - gcd: greatest common divisor (Euclid)
    - power: fast modular exponentiation (square-and-multiply)
    - modInverse: modular inverse via Extended Euclid
    - isGenerator: tests whether g is a primitive root modulo p
    - main: interactive flow (read inputs, compute keys, encrypt, decrypt)
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

// check if g is a generator of Z*p
bool isGenerator(long long g, long long p) {
    // p is prime, so group size = p-1
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
    cout << "Enter a large prime number (p): ";
    cin >> p;

    // find generator starting from 100
    long long g = 100;
    while (g < p && !isGenerator(g, p)) {
        g++;
    }
    if (g >= p) {
        cout << "No generator found.\n";
        return 0;
    }

    // private key x
    long long x;
    cout << "Enter private key x (1 <= x <= p-2): ";
    cin >> x;

    // session key k
    long long k = 12345;
    while(k <= p - 2 && gcd(k, p-1) != 1){
        k++;
    }
    if (k > p - 2){
        cout << "No valid k found.\n";
        return 0;
    }

    // message M
    long long M;
    cout << "Enter message (as number): ";
    cin >> M;

    // compute public key h
    long long h = power(g, x, p);

    // Encryption
    long long C1 = power(g, k, p);
    long long C2 = (M * power(h, k, p)) % p;

    cout << "\nPublic Key: (p=" << p << ", g=" << g << ", h=" << h << ")\n";
    cout << "Private Key: x = " << x << "\n";
    cout << "Ciphertext: (" << C1 << ", " << C2 << ")\n";

    // Decryption
    long long s = power(C1, x, p);
    long long s_inv = modInverse(s, p);
    long long decrypted = (C2 * s_inv) % p;

    cout << "\nDecrypted Message: " << decrypted << "\n";

    return 0;
}