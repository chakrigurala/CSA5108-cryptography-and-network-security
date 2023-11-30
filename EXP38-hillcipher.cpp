#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_TEXT_LENGTH 100

// Function to calculate the modular inverse of a number
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // Inverse doesn't exist
}

// Function to encrypt using Hill cipher
void encryptHill(char* plaintext, int keyMatrix[][3], int blockSize) {
    int i, j, k;

    int len = strlen(plaintext);
    int paddedLen = (len % blockSize == 0) ? len : len + (blockSize - len % blockSize);
    char paddedText[paddedLen];

    // Padding with 'X' if needed
    strcpy(paddedText, plaintext);
    for (i = len; i < paddedLen; i++) {
        paddedText[i] = 'X';
    }

    paddedText[paddedLen] = '\0';

    // Encryption
    for (i = 0; i < paddedLen; i += blockSize) {
        for (j = 0; j < blockSize; j++) {
            int sum = 0;
            for (k = 0; k < blockSize; k++) {
                sum += keyMatrix[j][k] * (paddedText[i + k] - 'A');
            }
            paddedText[i + j] = (sum % 26) + 'A';
        }
    }

    printf("Encrypted Text: %s\n", paddedText);
}

// Function to perform a known plaintext attack on Hill cipher
void knownPlaintextAttack(char* plaintext, char* ciphertext, int keyMatrix[][3], int blockSize) {
    int i, j, k;

    int len = strlen(plaintext);
    int paddedLen = (len % blockSize == 0) ? len : len + (blockSize - len % blockSize);
    char paddedText[paddedLen];

    // Padding with 'X' if needed
    strcpy(paddedText, plaintext);
    for (i = len; i < paddedLen; i++) {
        paddedText[i] = 'X';
    }

    paddedText[paddedLen] = '\0';

    // Known plaintext attack
    for (i = 0; i < paddedLen; i += blockSize) {
        for (j = 0; j < blockSize; j++) {
            int sum = 0;
            for (k = 0; k < blockSize; k++) {
                sum += modInverse(keyMatrix[j][k], 26) * ((ciphertext[i + k] - 'A') - (paddedText[i + k] - 'A') + 26) % 26;
            }
            keyMatrix[j][j] = (sum % 26 + 26) % 26;
        }
    }

    // Print the key matrix
    printf("Recovered Key Matrix:\n");
    for (i = 0; i < blockSize; i++) {
        for (j = 0; j < blockSize; j++) {
            printf("%d ", keyMatrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int keyMatrix[3][3] = {{6, 24, 1}, {13, 16, 10}, {20, 17, 15}};
    int blockSize = 3;

    char plaintext[MAX_TEXT_LENGTH] = "HELLO";
    char ciphertext[MAX_TEXT_LENGTH];

    // Encryption
    encryptHill(plaintext, keyMatrix, blockSize);

    // Known plaintext attack
    printf("\nEnter the corresponding ciphertext for known plaintext: ");
    scanf("%s", ciphertext);

    knownPlaintextAttack(plaintext, ciphertext, keyMatrix, blockSize);

    return 0;
}

