/*
    Elliptic curve ElGamal demo (toy implementation)

    This file implements a simple elliptic-curve based ElGamal encryption demo
    over a prime field F_p. It is intended for educational use only.

    High-level overview:
    - The curve is y^2 = x^3 + a*x + b (mod p). The user provides p, a, b.
    - The program searches for a curve point G to use as a base point.
    - The user supplies a private key x and the corresponding public key Y = x*G.
    - A message is represented as a point M on the curve (entered by the user).
    - To encrypt, choose random k and compute C1 = k*G and C2 = M + k*Y.
    - To decrypt, compute M = C2 - x*C1 (implemented by adding negation).

    Important notes / caveats:
    - This implementation uses 64-bit integers and brute-force point search. It
        is NOT secure or practical for real-world cryptography. Use big-integer
        libraries, proper curve parameters, and cryptographically-secure randomness
        for production.
    - The program assumes inputs are valid (p prime, a and b define a non-singular
        curve, M is a point on the curve). No exhaustive validation is performed.
*/

#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
    bool inf;
    Point() { x = y = 0; inf = true; }
    Point(long long _x, long long _y) { x = _x; y = _y; inf = false; }
};

long long mod(long long a, long long p) {
    long long r = a % p;
    if (r < 0) r += p;
    return r;
}

long long modInverse(long long a, long long p) {
    long long m0 = p, y = 0, x = 1;
    if (p == 1) return 0;
    while (a > 1) {
        long long q = a / p;
        long long t = p;
        p = a % p, a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0) x += m0;
    return x;
}

long long a, b, p;

// Elliptic curve point addition: returns P + Q over the field modulo p.
// Handles special cases: identity point, point doubling, and inverse pairs.
Point add(Point P, Point Q) {
    if (P.inf) return Q;
    if (Q.inf) return P;
    // If P and Q are inverses of each other (same x, y = -y), return infinity.
    if (P.x == Q.x && (P.y != Q.y || P.y == 0)) return Point(); 

    long long lambda;
    if (P.x == Q.x && P.y == Q.y) {
        // Point doubling: lambda = (3*x^2 + a) / (2*y)
        long long num = mod(3 * P.x * P.x + a, p);
        long long den = modInverse(mod(2 * P.y, p), p);
        lambda = mod(num * den, p);
    } else {
        // Point addition: lambda = (y2 - y1) / (x2 - x1)
        long long num = mod(Q.y - P.y, p);
        long long den = modInverse(mod(Q.x - P.x, p), p);
        lambda = mod(num * den, p);
    }

    long long xr = mod(lambda * lambda - P.x - Q.x, p);
    long long yr = mod(lambda * (P.x - xr) - P.y, p);

    return Point(xr, yr);
}

Point multiply(Point P, long long k) {
    Point R; 
    while (k > 0) {
        if (k & 1) R = add(R, P);
        P = add(P, P);
        k >>= 1;
    }
    return R;
}


Point findBasePoint() {
    for (long long x = 0; x < p; x++) {
        long long rhs = mod((x * x % p * x % p + a * x + b), p);
        for (long long y = 0; y < p; y++) {
            if (mod(y * y, p) == rhs)
                return Point(x, y);
        }
    }
    return Point(); 
}

int main() {
    cout << "Enter prime p: ";
    cin >> p;
    cout << "Enter curve parameters a and b for y^2 = x^3 + ax + b mod p:\n";
    cin >> a >> b;
    // Find a curve point to use as base G (brute-force search)
    Point G = findBasePoint();
    if (G.inf) {
        cout << "No valid base point found!\n";
        return 0;
    }
    cout << "Generated base point G = (" << G.x << ", " << G.y << ")\n";

    long long x; 
    cout << "Enter private key x: ";
    cin >> x;

    // Public key Y = x * G
    Point Y = multiply(G, x);
    cout << "Public key Y = (" << Y.x << ", " << Y.y << ")\n";

    // Message point M must be a valid point on the curve supplied by user
    Point M;
    cout << "Enter message point M (x y): ";
    cin >> M.x >> M.y;
    M.inf = false;

    long long k;
    cout << "Enter random session key k: ";
    cin >> k;

    // Encryption: C1 = k*G, C2 = M + k*Y
    Point C1 = multiply(G, k);
    Point kY = multiply(Y, k);
    Point C2 = add(M, kY);

    cout << "\nCiphertext:\n";
    cout << "C1 = (" << C1.x << ", " << C1.y << ")\n";
    cout << "C2 = (" << C2.x << ", " << C2.y << ")\n";

    // Decryption: compute x*C1 and subtract from C2 (subtract by adding negation)
    Point xC1 = multiply(C1, x);
    Point negX = xC1;
    negX.y = mod(-negX.y, p); 

    Point decrypted = add(C2, negX);

    cout << "\nDecrypted message point M = (" << decrypted.x << ", " << decrypted.y << ")\n";

    return 0;
}