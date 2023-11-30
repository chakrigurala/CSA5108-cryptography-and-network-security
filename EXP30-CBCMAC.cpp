#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>

void cbc_mac(const unsigned char* key, const unsigned char* message, size_t message_len, unsigned char* mac) {
    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);

    unsigned char iv[AES_BLOCK_SIZE];
    memset(iv, 0, AES_BLOCK_SIZE);

    unsigned char ciphertext[AES_BLOCK_SIZE];
    memset(ciphertext, 0, AES_BLOCK_SIZE);

    // Encrypt the first block
    AES_encrypt(message, ciphertext, &aes_key);
    memcpy(mac, ciphertext, AES_BLOCK_SIZE);

    // XOR the second block with the first block's ciphertext
    unsigned char xor_input[AES_BLOCK_SIZE];
    for (size_t i = 0; i < AES_BLOCK_SIZE; i++) {
        xor_input[i] = message[AES_BLOCK_SIZE + i] ^ ciphertext[i];
    }

    // Encrypt the result
    AES_encrypt(xor_input, ciphertext, &aes_key);

    // Final MAC is the last ciphertext block
    memcpy(mac, ciphertext, AES_BLOCK_SIZE);
}

int main() {
    const char* key_data = "0123456789abcdef";
    const char* message_data = "ThisIsAMessage";

    printf("Message: %s\n", message_data);

    unsigned char mac[AES_BLOCK_SIZE];
    cbc_mac((const unsigned char*)key_data, (const unsigned char*)message_data, AES_BLOCK_SIZE * 2, mac);

    printf("CBC-MAC: ");
    for (size_t i = 0; i < AES_BLOCK_SIZE; i++) {
        printf("%02x", mac[i]);
    }
    printf("\n");

    return 0;
}

