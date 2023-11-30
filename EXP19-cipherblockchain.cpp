#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl.h>

void encrypt_3des_cbc(const char *input, const char *key, const char *iv, char *output) {
    DES_cblock desKey1, desKey2, desKey3, desIV;
    DES_key_schedule ks1, ks2, ks3;

    // Set the keys
    memcpy(desKey1, key, 8);
    memcpy(desKey2, key + 8, 8);
    memcpy(desKey3, key + 16, 8);

    // Set the initialization vector (IV)
    memcpy(desIV, iv, 8);

    // Set up the key schedules
    DES_set_key_unchecked(&desKey1, &ks1);
    DES_set_key_unchecked(&desKey2, &ks2);
    DES_set_key_unchecked(&desKey3, &ks3);

    // Initialize the encryption context
    DES_cblock ivec;
    memcpy(ivec, desIV, sizeof(desIV));

    // Encrypt each block in CBC mode
    size_t len = strlen(input);
    for (size_t i = 0; i < len; i += 8) {
        DES_encrypt1(&ivec, &ks1, DES_ENCRYPT);
        DES_encrypt2(&ivec, &ks2, DES_ENCRYPT);
        DES_encrypt3(&ivec, &ks3, &ks2, &ks1, DES_ENCRYPT);

        // XOR the result with the plaintext block
        for (size_t j = 0; j < 8 && i + j < len; ++j) {
            output[i + j] = input[i + j] ^ ivec[j];
        }
    }
}

int main() {
    const char *plaintext = "Hello123";
    const char *key = "abcdefghabcdefghabcdefgh";
    const char *iv = "12345678";

    char ciphertext[64];  // Ensure it's large enough to hold the encrypted text

    encrypt_3des_cbc(plaintext, key, iv, ciphertext);

    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: ");
    for (int i = 0; i < 64; ++i) {
        printf("%02x", (unsigned char)ciphertext[i]);
    }
    printf("\n");

    return 0;
}

