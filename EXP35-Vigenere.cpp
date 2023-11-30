#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to encrypt a single character
char encryptChar(char plainChar, int key) {
    if (isalpha(plainChar)) {
        char base = isupper(plainChar) ? 'A' : 'a';
        return (char)(((plainChar - base + key) % ALPHABET_SIZE) + base);
    } else {
        return plainChar;  // Leave non-alphabetic characters unchanged
    }
}

// Function to perform Vigenère encryption using a one-time pad
void vigenereEncrypt(const char *plaintext, const int *key, char *ciphertext) {
    int keyIndex = 0;
    int plaintextLength = strlen(plaintext);

    for (int i = 0; i < plaintextLength; ++i) {
        ciphertext[i] = encryptChar(plaintext[i], key[keyIndex]);
        keyIndex = (keyIndex + 1) % ALPHABET_SIZE; // Move to the next key
    }

    ciphertext[plaintextLength] = '\0'; // Null-terminate the string
}

int main() {
    // Example key: 3 19 5
    int key[] = {3, 19, 5};

    // Example plaintext
    const char *plaintext = "HelloWorld";

    // Allocate memory for ciphertext
    char *ciphertext = (char *)malloc(strlen(plaintext) + 1);

    // Encrypt the plaintext
    vigenereEncrypt(plaintext, key, ciphertext);

    // Print the results
    printf("Plaintext: %s\n", plaintext);
    printf("Key: %d %d %d\n", key[0], key[1], key[2]);
    printf("Ciphertext: %s\n", ciphertext);

    // Free allocated memory
    free(ciphertext);

    return 0;
}

