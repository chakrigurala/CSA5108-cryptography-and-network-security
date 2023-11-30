#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/des.h>

void des_encrypt_ecb(const char *plaintext, const char *key, char *ciphertext, int padding) {
    DES_cblock desKey;
    DES_key_schedule ks;

    // Set the key
    memcpy(desKey, key, 8);

    // Set up the key schedule
    if (DES_set_key_checked(&desKey, &ks) != 0) {
        fprintf(stderr, "Error setting up key schedule\n");
        exit(EXIT_FAILURE);
    }

    // Encrypt the plaintext in ECB mode
    DES_ecb_encrypt((DES_cblock *)plaintext, (DES_cblock *)ciphertext, &ks, DES_ENCRYPT);

    // Apply padding if needed
    if (padding) {
        int pad_len = 8 - strlen(plaintext) % 8;
        memset(ciphertext + strlen(plaintext), pad_len, pad_len);
    }
}

void des_decrypt_ecb(const char *ciphertext, const char *key, char *decryptedtext) {
    DES_cblock desKey;
    DES_key_schedule ks;

    // Set the key
    memcpy(desKey, key, 8);

    // Set up the key schedule
    if (DES_set_key_checked(&desKey, &ks) != 0) {
        fprintf(stderr, "Error setting up key schedule\n");
        exit(EXIT_FAILURE);
    }

    // Decrypt the ciphertext in ECB mode
    DES_ecb_encrypt((DES_cblock *)ciphertext, (DES_cblock *)decryptedtext, &ks, DES_DECRYPT);
}

void des_encrypt_cbc(const char *plaintext, const char *key, const char *iv, char *ciphertext, int padding) {
    DES_cblock desKey, desIV;
    DES_key_schedule ks;

    // Set the key
    memcpy(desKey, key, 8);

    // Set the initialization vector (IV)
    memcpy(desIV, iv, 8);

    // Set up the key schedule
    if (DES_set_key_checked(&desKey, &ks) != 0) {
        fprintf(stderr, "Error setting up key schedule\n");
        exit(EXIT_FAILURE);
    }

    // Encrypt the plaintext in CBC mode
    DES_cblock ivec;
    memcpy(ivec, desIV, sizeof(desIV));

    size_t len = strlen(plaintext);
    for (size_t i = 0; i < len; i += 8) {
        // XOR the plaintext block with the previous ciphertext block or IV
        for (size_t j = 0; j < 8 && i + j < len; ++j) {
            plaintext[i + j] ^= ivec[j];
        }

        // Encrypt the block
        DES_ecb_encrypt((DES_cblock *)(plaintext + i), (DES_cblock *)(ciphertext + i), &ks, DES_ENCRYPT);

        // Update the IV for the next iteration
        memcpy(ivec, ciphertext + i, sizeof(ivec));
    }

    // Apply padding if needed
    if (padding) {
        int pad_len = 8 - len % 8;
        memset(ciphertext + len, pad_len, pad_len);
    }
}

void des_decrypt_cbc(const char *ciphertext, const char *key, const char *iv, char *decryptedtext) {
    DES_cblock desKey, desIV;
    DES_key_schedule ks;

    // Set the key
    memcpy(desKey, key, 8);

    // Set the initialization vector (IV)
    memcpy(desIV, iv, 8);

    // Set up the key schedule
    if (DES_set_key_checked(&desKey, &ks) != 0) {
        fprintf(stderr, "Error setting up key schedule\n");
        exit(EXIT_FAILURE);
    }

    // Decrypt the ciphertext in CBC mode
    DES_cblock ivec;
    memcpy(ivec, desIV, sizeof(desIV));

    size_t len = strlen(ciphertext);
    for (size_t i = 0; i < len; i += 8) {
        // Decrypt the block
        DES_ecb_encrypt((DES_cblock *)(ciphertext + i), (DES_cblock *)(decryptedtext + i), &ks, DES_DECRYPT);

        // XOR the decrypted block with the previous ciphertext block or IV
        for (size_t j = 0; j < 8; ++j) {
            decryptedtext[i + j] ^= ivec[j];
        }

        // Update the IV for the next iteration
        memcpy(ivec, ciphertext + i, sizeof(ivec));
    }
}

void des_encrypt_cfb(const char *plaintext, const char *key, const char *iv, char *ciphertext, int padding) {
    DES_cblock desKey, desIV;
    DES_key_schedule ks;

    // Set the key
    memcpy(desKey, key, 8);

    // Set the initialization vector (IV)
    memcpy(desIV, iv, 8);

    // Set up the key schedule
    if (DES_set_key_checked(&desKey, &ks) != 0) {
        fprintf(stderr, "Error setting up key schedule\n");
        exit(EXIT_FAILURE);
    }

    // Encrypt the plaintext in CFB mode
    DES_cblock ivec;
    memcpy(ivec, desIV, sizeof(desIV));

    size_t len = strlen(plaintext);
    for (size_t i = 0; i < len; i += 8) {
        // Encrypt the block
        DES_ecb_encrypt(&ivec, &ivec, &ks, DES_ENCRYPT);

        // XOR the encrypted block with the plaintext
        for (size_t j = 0; j < 8 && i + j < len; ++j) {
            ciphertext[i + j] = plaintext[i + j] ^ ivec[j

