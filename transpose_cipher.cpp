/*
    transpose_cipher.cpp

    Purpose:
    - Simple columnar transposition cipher demo. Key is provided as a string of
    digits representing a column permutation (e.g. "4231" means read column 4,
        then 2, then 3, then 1).
    - This program fills a matrix row-wise with the plaintext (padding with '*'),
        produces ciphertext by reading columns in key order, and demonstrates
        decryption by filling the matrix column-wise from the ciphertext.

    Notes:
    - The key format here only supports single-digit column indices (col <= 9).
    - Input message is read with `cin >> msg` (no spaces). Consider using
        getline if you want to allow spaces in the plaintext.
    - Variable-length arrays were replaced with vectors in the refactor to
        improve portability; behavior remains the same.
*/

#include<bits/stdc++.h>
using namespace std;

// Build a row x col matrix filled row-wise with message and '*' padding
static vector<vector<char>> build_matrix_rowwise(const string &msg, int row, int col) {
    vector<vector<char>> mat(row, vector<char>(col, '*'));
    int k = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (k < (int)msg.size()) mat[i][j] = msg[k++];
            else mat[i][j] = '*';
        }
    }
    return mat;
}

// Encrypt using columnar transposition with numeric digit key (e.g. "4231")
string transpose_encrypt(const string &msg, const string &key) {
    int col = key.size();
    int row = (int)ceil((msg.size() * 1.0) / col);

    auto mat = build_matrix_rowwise(msg, row, col);

    cout << "Matrix (row-wise filled): " << endl;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) cout << mat[i][j] << " ";
        cout << endl;
    }

    string cipher;
    cipher.reserve(row * col);
    for (int c = 0; c < col; ++c) {
        int colIdex = (key[c] - '0') - 1;
        for (int r = 0; r < row; ++r) cipher.push_back(mat[r][colIdex]);
    }

    cout << "Cipher Text: " << cipher << endl;
    return cipher;
}

// Decrypt the cipher using the key and number of rows, return plaintext (no padding)
string transpose_decrypt(const string &cipher, const string &key, int row) {
    int col = key.size();
    vector<vector<char>> mat(row, vector<char>(col, '*'));

    int idx = 0;
    for (int c = 0; c < col; ++c) {
        int colIdex = (key[c] - '0') - 1;
        for (int r = 0; r < row; ++r) {
            mat[r][colIdex] = cipher[idx++];
        }
    }

    cout << "Matrix after filling cipher: " << endl;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) cout << mat[i][j] << " ";
        cout << endl;
    }

    string plain;
    plain.reserve(row * col);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (mat[i][j] != '*') plain.push_back(mat[i][j]);
        }
    }
    cout << "Decryption Plain Text: " << plain << endl;
    return plain;
}

int main() {
    // Program flow:
    // 1) Read plaintext (msg) and numeric key string (key).
    // 2) Compute matrix size (rows, cols) and call transpose_encrypt to
    //    build matrix and generate ciphertext.
    // 3) Call transpose_decrypt with the ciphertext and same key to rebuild
    //    the original matrix and extract plaintext (padding removed).
    string msg;
    cin >> msg;
    string key;
    cin >> key;

    int col = key.size();
    int row = (int)ceil((msg.size() * 1.0) / col);

    string cipher = transpose_encrypt(msg, key);
    // decrypt using computed row count
    string plain = transpose_decrypt(cipher, key, row);

    (void)plain; // plain already printed in decrypt
    return 0;
}


/*

ABCDEFGHIJKLMNO
4231

ABCDEFGHIJKLMNO
1234

*/