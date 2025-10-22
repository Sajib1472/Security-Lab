/*
    RSA Product demo (educational)

    Purpose:
    - Demonstrates RSA key generation and encrypting the product of two messages:
            Encrypt( (m1 * m2) mod n ) and then decrypt to recover the product.
    - This is a toy/example implementation using 64-bit integers; it is NOT secure
        for real cryptographic use. For production use bignum libraries and padding.

    High-level flow (main):
    1) Read two primes p and q, compute n = p*q and phi = (p-1)*(q-1).
    2) Choose public exponent e with gcd(e, phi) == 1.
    3) Compute private exponent d = e^{-1} mod phi.
    4) Read two messages m1 and m2 (integers), compute product m = m1*m2 mod n.
    5) Encrypt product: C = m^e mod n. Decrypt with C^d mod n to recover m.

    Note: This file intentionally keeps the math simple for learning purposes.
*/

#include<bits/stdc++.h>
using namespace std;

#define ll long long

// Compute gcd(a,b) using Euclid's algorithm
ll gcd(ll a, ll b){
    if(b == 0) return a;  
    return gcd(b, a % b);       
}

// Fast modular exponentiation: computes (a^b) % m in O(log b) steps
ll power(ll a, ll b, ll m){
    ll result = 1;  
    a = a % m;
    while(b > 0){   
        if ( b & 1) result = (result * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return result;
}

// Modular inverse via Extended Euclidean Algorithm
// Returns x such that (a * x) % m == 1, assuming gcd(a,m) == 1
ll modInverse(ll a, ll m){
    ll m0=m, x=1, y=0;
    if (m == 1) return 0;  

    while(a > 1){  
        ll q = a/m;
        ll t = m;
        m = a % m , a=t;
        t = y;
        y = x - q*y;
        x = t;
    }
    if (x < 0) x = x+m0;   
    return x;
}

int main(){
    ll p,q;
    cout << "Enter two prime numbers: " ;
    cin >> p >> q;

    ll n = p*q;
    ll phi = (p-1)*(q-1);

    ll e = 13;
    while(gcd(e,phi) != 1){
        e += 2;
    }
    if (e > phi){
        cout << "No e found";
        return 0;
    }

    ll d = modInverse(e,phi);

    cout << n << " " << e << endl;
    cout << d << endl;

    ll m1,m2;
    cout << "Enter the messages: ";
    cin >> m1 >> m2;

    cout << "product message: " << (m1*m2) % n << endl;

    ll enc = power(((m1*m2)%n), e, n);
    cout << "Encryption is: " << enc << endl;

    ll decp = power(enc, d, n);
    cout << "Actual message: " << decp;
}