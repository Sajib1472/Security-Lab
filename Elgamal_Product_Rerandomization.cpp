#include<bits/stdc++.h>
using namespace std;

/*
    ElGamal product / rerandomization demo

    This educational file shows two related ElGamal operations:
    1) (commented-out) Product ciphertext: how to multiply two ElGamal ciphertexts
         so that the decrypted plaintext equals the product m1*m2 mod p.
    2) Rerandomization of a single ciphertext: given ciphertext (c1,c2) for m,
         multiply by an encryption of 1 to obtain a new ciphertext (c1',c2') that
         decrypts to the same message m but uses a different randomness (k2).

    Important variables (mapping):
     - p : prime modulus
     - g : generator of multiplicative group modulo p
     - x : private key
     - h : public key = g^x mod p
     - key1, key2 : ephemeral session keys (k1,k2) used for encryption
     - m1,m2 / m1 : plaintext numbers (in Z_p)
     - c11,c21 and c12,c22 : individual ciphertext pairs for each encryption
     - c1,c2 : combined ciphertext after product/rerandomization

    Notes and caveats:
     - This is a toy implementation using 64-bit integers. For real security use a
         big-integer library (GMP, OpenSSL BIGNUM) and cryptographically secure RNGs.
     - The code currently selects deterministic small keys (key1/key2) by linear
         search; in practice use a secure RNG and ensure k is unique per encryption.
     - Inputs are expected to be small enough to fit in `long long` and M < p.
*/

#define ll long long

ll gcd(ll a, ll b){
    if(b == 0) return a;
    return gcd(b, a % b);     
}

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
    ll p, g;
    cout << "Enter the prime number and generator: ";
    cin >> p >> g;

    ll x;
    cout << "Enter the private key: ";
    cin >> x;

    ll h = power(g,x,p);

    ll key1 = 13;
    while(key1 <= p-2 && gcd(key1,p-1)!=1){
        key1++;
    }
    cout << "key1: " << key1 << endl;

    ll key2 = key1+27;
    while(key2 <= p-2 && gcd(key2,p-1)!=1){
        key2++;
    }
    cout << "key2: " << key2 << endl;

/*    

    // elgamal product cipher for two messages

    ll m1,m2;
    cout << "Enter the message: ";
    cin >> m1 >> m2;

    cout << "Enter message is: " << (m1*m2) % p << endl;

    ll c11 = power(g,key1,p);
    ll c21 = (m1*power(h,key1,p))%p;

    cout << "ciphertext: " << c11 << " " << c21 << endl;

    ll c12 = power(g,key2,p);
    ll c22 = (m2*power(h,key2,p))%p;

    ll c1 = (c11*c12)%p;
    ll c2 = (c21*c22)%p;

    cout << "ciphertext: " << c1 << " " << c2 << endl;
    
    ll s = power(c1,x,p);
    ll message = (c2 * modInverse(s,p))%p;

    cout << "Decrypt: " << message << endl;

*/

    // single message rerandomization
    ll m1;
    cout << "Enter the message: ";
    cin >> m1;

    ll c11 = power(g,key1,p);
    ll c21 = (m1*power(h,key1,p))%p;

    cout << "ciphertext: " << c11 << " " << c21 << endl;

    ll c12 = power(g,key2,p);
    ll c22 = power(h,key2,p);

    ll c1 = (c11*c12)%p;
    ll c2 = (c21*c22)%p;

    cout << "New ciphertext: " << c1 << " " << c2 << endl;
    
    ll s = power(c1,x,p);
    ll message = (c2 * modInverse(s,p))%p;

    cout << "Decrypt: " << message << endl;
}