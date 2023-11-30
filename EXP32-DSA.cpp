#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/dsa.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

void generate_dsa_key(DSA **dsa) {
    *dsa = DSA_generate_parameters(2048, NULL, 0, NULL, NULL, NULL, NULL);
    if (!*dsa) {
        fprintf(stderr, "Error generating DSA parameters\n");
        exit(EXIT_FAILURE);
    }

    if (!DSA_generate_key(*dsa)) {
        fprintf(stderr, "Error generating DSA key pair\n");
        exit(EXIT_FAILURE);
    }
}

void generate_rsa_key(RSA **rsa) {
    *rsa = RSA_generate_key(2048, RSA_F4, NULL, NULL);
    if (!*rsa) {
        fprintf(stderr, "Error generating RSA key pair\n");
        exit(EXIT_FAILURE);
    }
}

void sign_and_verify_dsa(const char *message, DSA *dsa) {
    unsigned char signature1[DSA_size(dsa)];
    unsigned char signature2[DSA_size(dsa)];

    // Sign the message twice
    DSA_do_sign((const unsigned char *)message, strlen(message), dsa);
    DSA_do_sign((const unsigned char *)message, strlen(message), dsa);

    // Note: In a real-world scenario, the generated signatures should be stored and compared.
    // For simplicity, this example just prints the raw signature bytes.
    printf("DSA Signature 1: ");
    for (int i = 0; i < DSA_size(dsa); ++i) {
        printf("%02x", signature1[i]);
    }
    printf("\n");

    printf("DSA Signature 2: ");
    for (int i = 0; i < DSA_size(dsa); ++i) {
        printf("%02x", signature2[i]);
    }
    printf("\n");
}

void sign_and_verify_rsa(const char *message, RSA *rsa) {
    unsigned char signature1[4096];  // RSA signature can be larger
    unsigned char signature2[4096];

    // Sign the message twice
    RSA_sign(NID_sha256, (const unsigned char *)message, strlen(message), signature1, NULL, rsa);
    RSA_sign(NID_sha256, (const unsigned char *)message, strlen(message), signature2, NULL, rsa);

    // Note: In a real-world scenario, the generated signatures should be stored and compared.
    // For simplicity, this example just prints the raw signature bytes.
    printf("RSA Signature 1: ");
    for (int i = 0; i < RSA_size(rsa); ++i) {
        printf("%02x", signature1[i]);
    }
    printf("\n");

    printf("RSA Signature 2: ");
    for (int i = 0; i < RSA_size(rsa); ++i) {
        printf("%02x", signature2[i]);
    }
    printf("\n");
}

int main() {
    DSA *dsa;
    generate_dsa_key(&dsa);

    RSA *rsa;
    generate_rsa_key(&rsa);

    const char *message = "Hello, Signatures!";

    printf("DSA Signatures:\n");
    sign_and_verify_dsa(message, dsa);

    printf("\nRSA Signatures:\n");
    sign_and_verify_rsa(message, rsa);

    DSA_free(dsa);
    RSA_free(rsa);

    return 0;
}

