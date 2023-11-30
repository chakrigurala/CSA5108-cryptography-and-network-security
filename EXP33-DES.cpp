#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/des.h>

void des_encrypt(const char *plaintext, const char *key, char *ciphertext) {
    DES_cblock desKey;
    DES_key_schedule ks;

    // Ensure the key is 56 bits (7 bytes)
    if (strlen(key) != 7) {
        fprintf(stderr, "Error: Key length must be 56 bits (7 bytes)\n");
        exit(EXIT_FAILURE);
    }

    // Set the key
    memcpy(desKey, key, 8);

    // Set up the key schedule
    if (DES_set_key_checked(&desKey, &ks) != 0) {
        fprintf(stderr, "Error setting up key schedule\n");
        exit(EXIT_FAILURE);
    }

    // Encrypt the plaintext
    DES_encrypt1((DES_cblock *)plaintext, &ks, DES_ENCRYPT);
    memcpy(ciphertext, plaintext, 8);
}

void des_decrypt(const char *ciphertext, const char *key, char *decryptedtext) {
    DES_cblock desKey;
    DES_key_schedule ks;

    // Ensure the key is 56 bits (7 bytes)
    if (strlen(key) != 7) {
        fprintf(stderr, "Error: Key length must be 56 bits (7 bytes)\n");
        exit(EXIT_FAILURE);
    }

    // Set the key
    memcpy(desKey, key, 8);

    // Set up the key schedule
    if (DES_set_key_checked(&desKey, &ks) != 0) {
        fprintf(stderr, "Error setting up key schedule\n");
        exit(EXIT_FAILURE);
    }

    // Decrypt the ciphertext
    DES_encrypt1((DES_cblock *)ciphertext, &ks, DES_DECRYPT);
    memcpy(decryptedtext, ciphertext, 8);
}

int main() {
    const char *plaintext = "Hello123";
    const char *key = "abcdefgh";  // 56-bit key

    char ciphertext[8];
    char decryptedtext[8];

    // Encrypt
    des_encrypt(plaintext, key, ciphertext);

    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: ");
    for (int i = 0; i < 8; ++i) {
        printf("%02x", (unsigned char)ciphertext[i]);
    }
    printf("\n");

    // Decrypt
    des_decrypt(ciphertext, key, decryptedtext);

    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}

