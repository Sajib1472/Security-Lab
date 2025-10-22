/*
  Caesar Cipher (simple shift cipher)

  This file provides a minimal implementation of the classical Caesar cipher.

  How it works (summary):
  - The cipher shifts alphabetic characters by a fixed integer `key`.
  - Uppercase letters ('A'..'Z') remain uppercase after shifting.
  - Lowercase letters ('a'..'z') remain lowercase after shifting.
  - Non-letter characters (digits, punctuation, whitespace) are left unchanged.

  Functions:
  - caesar_cipher(string text, int key, bool decryp = false)
      - If `decryp` is false (default), the function applies a forward shift by
        `key` positions (encryption).
      - If `decryp` is true, the function reverses the shift (decryption).
      - Note: the function assumes `key` is an integer; callers may normalize
        it with `key = ((key%26)+26)%26` if negative or >25.

  Usage (interactive):
    1) Run the program.
    2) Enter the plaintext (one line) when prompted.
    3) Enter an integer key (typically 1..25).
    4) The program prints the encrypted text and then the decrypted text.

  Example:
    Input text: Hello, World!
    Key: 3
    Encrypted: Khoor, Zruog!
    Decrypted: Hello, World!

  Notes & minor improvements you can add:
  - Normalize `key` to [0..25] before calling the function.
  - Cast characters to `unsigned char` when calling ctype functions for
    portability on non-ASCII platforms.
  - Use explicit arithmetic with 'A' and 'a' for clarity.
*/

#include <bits/stdc++.h>
using namespace std;

// Apply Caesar shift to `text`. If `decryp` is true, perform reverse shift.
string caesar_cipher(string text, int key, bool decryp = false){
    string result="";
    // If decrypting, invert the shift: shifting by (26 - key) reverses a forward shift.
    if(decryp) key = 26-key;
    for (char c : text){        
        if(isupper(c)){
            // Uppercase: map 'A'..'Z' -> 0..25, add shift, wrap with %26, map back
            result += char(int(c+key-65)%26 + 65);
        }
        else if(islower(c)){
            // Lowercase: same logic with 'a' base
            result += char(int(c-97+key)%26 + 97);
        }
        else{
            // Non-letter characters are preserved unchanged
            result += c;
        }
    }
    return result;
}

int main(){
    string text;
    int key;
    cout << "Enter the input text: ";
    getline(cin, text);     
    cout << "Enter the key: ";
    cin >> key;

    // Encrypt
    string en = caesar_cipher(text, key);
    cout << "Cipher message: " << en << endl;

    // Decrypt (pass the same key but set decryp = true)
    string de = caesar_cipher(en, key, true);
    cout << "Actual message: " << de << endl;
}