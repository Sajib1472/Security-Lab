/*
  Vernam cipher (one-time pad style) implementation

  This file implements a simple Vernam-style cipher using bytewise XOR.
  - The function `vermanCipher(text, key)` XORs each byte of `text` with the
    corresponding byte of `key` and returns the result. The key must be the same
    length as the text (one-time-pad requirement).
  - The program prints the encrypted bytes in hexadecimal form for readability.
  - To decrypt, the same function is used again with the same key because XOR
    is its own inverse: (A ^ K) ^ K = A.

  Important notes / caveats:
  - This is an educational/demo implementation. In real cryptography do NOT
    reuse keys; use a cryptographically secure RNG for one-time pads, or use
    authenticated encryption in practice.
  - The code treats strings as sequences of bytes and uses `char` XOR. For
    non-ASCII or multibyte encodings (UTF-8) be careful: length in bytes vs
    characters matters.
  - The program requires `text.length() == key.length()`; otherwise it prints
    an error and returns an empty result.
*/

#include<bits/stdc++.h>
using namespace std;

// XOR each byte of text with the corresponding byte of key and return result.
// Caller must ensure text.length() == key.length().
string vermanCipher(string text, string key){
    string result="";

    if (text.length() != key.length()){
        cout << "Both length is not same." << endl;
        return result;
    }

    for(int i=0;i<text.length();i++){
        // Byte-wise XOR; works for both encryption and decryption
        result += text[i] ^ key[i];
    }
    return result;
}

int main(){
    string text, key;
    cout << "Enter the text: ";
    getline(cin, text);

    cout << "Enter the key: ";
    getline(cin, key);

    // Encrypt (XOR) and print ciphertext as hex bytes
    string en = vermanCipher(text, key);
    cout << "Encrypted message is: ";
    for (unsigned char c : en)
        cout << hex << setw(2) << setfill('0') << (int)c;
    cout << endl;

    // Decrypt by XORing ciphertext with same key (XOR inverse)
    string de = vermanCipher(en, key);
    cout << "Decrypted message is: " << de;
}