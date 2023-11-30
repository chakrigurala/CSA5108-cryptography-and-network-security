#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_TEXT_LENGTH 1000
#define MATRIX_SIZE 2

// Function to convert a character to its numerical value (A=0, B=1, ..., Z=25)
int charToNum(char ch) {
    if (ch >= 'a' && ch <= 'z') {
        return ch - 'a';
    } else if (ch >= 'A' && ch <= 'Z') {
        return ch - 'A';
    } else {
        return -1; // Invalid character
    }
}

// Function to convert a numerical value to its character representation (0=A, 1=B, ..., 25=Z)
char numToChar(int num) {
    return num + 'A';
}

// Function to find the modular multiplicative inverse of a number
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // Inverse doesn't exist
}

// Function to calculate the determinant of a 2x2 matrix
int determinant(int mat[MATRIX_SIZE][MATRIX_SIZE]) {
    return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
}

// Function to calculate the adjugate of a 2x2 matrix
void adjugate(int mat[MATRIX_SIZE][MATRIX_SIZE], int adj[MATRIX_SIZE][MATRIX_SIZE]) {
    adj[0][0] = mat[1][1];
    adj[0][1] = -mat[0][1];
    adj[1][0] = -mat[1][0];
    adj[1][1] = mat[0][0];
}

// Function to calculate the inverse of a 2x2 matrix
void inverse(int mat[MATRIX_SIZE][MATRIX_SIZE], int inv[MATRIX_SIZE][MATRIX_SIZE]) {
    int det = determinant(mat);
    int modInv = modInverse(det, 26);

    if (modInv == -1) {
        printf("Inverse doesn't exist\n");
        exit(EXIT_FAILURE);
    }

    int adj[MATRIX_SIZE][MATRIX_SIZE];
    adjugate(mat, adj);

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            inv[i][j] = (adj[i][j] * modInv) % 26;
            if (inv[i][j] < 0) {
                inv[i][j] += 26; // Ensure the result is positive
            }
        }
    }
}

// Function to encrypt a 2x2 matrix with a key matrix
void encryptHill(int key[MATRIX_SIZE][MATRIX_SIZE], int block[MATRIX_SIZE], int result[MATRIX_SIZE]) {
    result[0] = (key[0][0] * block[0] + key[0][1] * block[1]) % 26;
    result[1] = (key[1][0] * block[0] + key[1][1] * block[1]) % 26;
}

// Function to decrypt a 2x2 matrix with a key matrix
void decryptHill(int key[MATRIX_SIZE][MATRIX_SIZE], int block[MATRIX_SIZE], int result[MATRIX_SIZE]) {
    int invKey[MATRIX_SIZE][MATRIX_SIZE];
    inverse(key, invKey);

    result[0] = (invKey[0][0] * block[0] + invKey[0][1] * block[1]) % 26;
    result[1] = (invKey[1][0] * block[0] + invKey[1][1] * block[1]) % 26;

    if (result[0] < 0) {
        result[0] += 26; // Ensure the result is positive
    }
    if (result[1] < 0) {
        result[1] += 26; // Ensure the result is positive
    }
}

int main() {
    // Known plaintext-ciphertext pairs
    char plaintext[MAX_TEXT_LENGTH] = "MEETMEATTHEUSUALPLACEATTENRATHERTHANEIGHTOCLOCK";
    char ciphertext[MAX_TEXT_LENGTH] = "MLTTSRZTEQNVPLRNTURSVGLGNUUHVENTVP";

    int len = strlen(plaintext);

    // Convert plaintext and ciphertext to numerical values
    int numericPlaintext[MAX_TEXT_LENGTH], numericCiphertext[MAX_TEXT_LENGTH];
    for (int i = 0; i < len; i++) {
        numericPlaintext[i] = charToNum(plaintext[i]);
        numericCiphertext[i] = charToNum(ciphertext[i]);
    }

    // Divide the known plaintext-ciphertext pairs into 2x2 matrices
    int numPairs = len / MATRIX_SIZE;
    int plaintextMatrix[numPairs][MATRIX_SIZE];
    int ciphertextMatrix[numPairs][MATRIX_SIZE];

    for (int i = 0; i < numPairs; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            plaintextMatrix[i][j] = numericPlaintext[i * MATRIX_SIZE + j];
            ciphertextMatrix[i][j] = numericCiphertext[i * MATRIX_SIZE + j];
        }
    }

    // Initialize variables for key matrix and decrypted matrix
    int key[MATRIX_SIZE][MATRIX_SIZE];
    int decryptedMatrix[numPairs][MATRIX_SIZE];

    // Perform the known-plaintext attack to find the key matrix
    for (int i = 0; i < numPairs; i++) {
        inverse(plaintextMatrix, key);
        decryptHill(key, ciphertextMatrix[i], decryptedMatrix[i]);
    }

    // Display the key matrix
    printf("Key Matrix:\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", key[i][j]);
        }
        printf("\n");
    }

    // Display the decrypted message
    printf("Decrypted Message:\n");
    for (int i = 0; i < numPairs; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%c", numToChar(decryptedMatrix[i][j]));
        }
        printf(" ");
    }
    printf("\n");

    return 0;
}

