#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>

void print_hex(const char* label, const unsigned char* data, size_t len) {
    printf("%s: ", label);
    for (size_t i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

void encrypt_decrypt(const unsigned char* input, const AES_KEY* key, const unsigned char* iv, int mode) {
    size_t input_len = strlen((const char*)input);
    size_t padded_len = ((input_len + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;

    unsigned char padded_input[padded_len];
    memcpy(padded_input, input, input_len);
    memset(padded_input + input_len, 0, padded_len - input_len);

    unsigned char output[padded_len];
    AES_crypt_ofb(key, iv, padded_input, output, padded_len, mode);

    print_hex("Encrypted", output, padded_len);

    unsigned char decrypted[padded_len];
    AES_crypt_ofb(key, iv, output, decrypted, padded_len, mode);

    print_hex("Decrypted", decrypted, padded_len);
}

int main() {
    // Key should be 16, 24, or 32 bytes for AES-128, AES-192, or AES-256
    const char* key_data = "0123456789abcdef";
    AES_KEY key;
    AES_set_encrypt_key((const unsigned char*)key_data, 128, &key);

    // IV (Initialization Vector) should be the same size as the block size
    const char* iv_data = "1234567890123456";

    const char* plaintext = "ThisIsAPlainText";

    printf("Plaintext: %s\n", plaintext);

    printf("\nECB Mode:\n");
    encrypt_decrypt((const unsigned char*)plaintext, &key, (const unsigned char*)iv_data, AES_ENCRYPT);

    printf("\nCBC Mode:\n");
    encrypt_decrypt((const unsigned char*)plaintext, &key, (const unsigned char*)iv_data, AES_CBC_MODE);

    printf("\nCFB Mode:\n");
    encrypt_decrypt((const unsigned char*)plaintext, &key, (const unsigned char*)iv_data, AES_CFB_MODE);

    return 0;
}

