#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to compute the modular multiplicative inverse
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // If the inverse does not exist
}

// Function to encrypt a single character using the affine Caesar cipher
char encryptChar(char plainChar, int a, int b) {
    if (isalpha(plainChar)) {
        char base = isupper(plainChar) ? 'A' : 'a';
        int plaintextIndex = plainChar - base;
        int ciphertextIndex = (a * plaintextIndex + b) % ALPHABET_SIZE;
        return (char)(ciphertextIndex + base);
    } else {
        return plainChar;  // Leave non-alphabetic characters unchanged
    }
}

// Function to perform affine Caesar encryption
void affineCaesarEncrypt(const char *plaintext, int a, int b, char *ciphertext) {
    int plaintextLength = strlen(plaintext);

    for (int i = 0; i < plaintextLength; ++i) {
        ciphertext[i] = encryptChar(plaintext[i], a, b);
    }

    ciphertext[plaintextLength] = '\0'; // Null-terminate the string
}

int main() {
    // Example values for a and b
    int a = 5;
    int b = 8;

    // Example plaintext
    const char *plaintext = "HelloWorld";

    // Allocate memory for ciphertext
    char *ciphertext = (char *)malloc(strlen(plaintext) + 1);

    // Encrypt the plaintext
    affineCaesarEncrypt(plaintext, a, b, ciphertext);

    // Print the results
    printf("Plaintext: %s\n", plaintext);
    printf("Key: a = %d, b = %d\n", a, b);
    printf("Ciphertext: %s\n", ciphertext);

    // Free allocated memory
    free(ciphertext);

    return 0;
}

