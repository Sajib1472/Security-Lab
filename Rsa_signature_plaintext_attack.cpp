/*
    Rsa_signature_plaintext_attack.cpp

    Purpose:
    - Educational/demo program showing RSA key generation and verification of the
        property that multiple valid private exponents exist (d and d + k*phi).
    - It computes the modular inverse `b1 = e^{-1} mod phi` and also shows `b2 = b1 + phi`.
    - Demonstrates encryption/decryption with both exponents and (optionally)
        brute-forces small exponents that correctly decrypt the ciphertext.

    Notes:
    - This is for learning only. It uses `long long` and is limited to small primes.
    - Brute-forcing exponents is infeasible for real RSA-sized moduli.
    - The code does not perform primality checks on p and q; assume the user inputs primes.
*/

#include<bits/stdc++.h>
using namespace std;

#define ll long long

ll gcd(ll a, ll b){
    if ( b == 0 ) return a;
    return gcd(b, a%b);
}

ll power(ll a, ll b, ll m){
    ll result = 1;
    a = a%m;
    while(b>0){
        if (b&1) result = (result * a)%m;
        a = ( a*a ) % m;
        b >>= 1;
    }
    return result;
}

ll modInverse(ll a, ll m){
    ll m0=m, x=1, y=0;
    if(m==1) return 0;

    while(a>1){   
        ll q = a / m;
        ll t = m;
        m = a % m, a = t;
        t = y;
        y = x - q*y;
        x = t;
    }
    if (x < 0) x = x+m0;
    return x;
}

int main(){
    ll p,q;
    cout << "Enter two numbers: ";
    cin >> p >> q;

    ll n = p*q;
    ll phi = (p-1)*(q-1);

    ll e = 13;
    while(gcd(e,phi)!=1){
        e=e+2;
    }
    if(e > phi){
        cout << "No e found";
    }

    ll b1 = modInverse(e,phi);
    // another valid private exponent is b2 = b1 + phi (exponents are modulo phi)
    long long b2 = b1 + phi;

    cout << "Computed private exponent b1 = " << b1 << "\n";
    cout << "Another valid exponent b2 = b1 + phi = " << b2 << "\n";

    ll m;
    cout << "Enter the message: ";
    cin >> m;

    ll en = power(m,e,n);

    // verify decryption using b1 and b2
    ll dec1 = power(en, b1, n);
    ll dec2 = power(en, b2, n);

    cout << "Decrypted with b1: " << dec1 << "\n";
    cout << "Decrypted with b2: " << dec2 << "\n";

    // brute-force search to find up to two exponents d that decrypt to the message
    vector<ll> found;
    for (ll i = 3; i < n && found.size() < 2; ++i) {
        ll de = power(en, i, n);
        if (de == m) {
            found.push_back(i);
        }
    }

    if (!found.empty()) {
        cout << "Found d values via brute-force:\n";
        for(int i=0;i<found.size();i++){
            cout << "Value of d is: " << found[i] << endl;
        }
    } else {
        cout << "No d found by brute-force (or search aborted early)." << endl;
    }
}