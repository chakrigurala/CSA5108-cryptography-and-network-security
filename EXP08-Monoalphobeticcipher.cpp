#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to generate the cipher sequence from the keyword
void generateCipherSequence(char *keyword, char *cipherSequence) {
    int i, j, len;

    len = strlen(keyword);

    // Copy the keyword to the beginning of the cipher sequence
    strcpy(cipherSequence, keyword);

    // Mark used characters
    for (i = 0; i < len; i++) {
        keyword[i] = toupper(keyword[i]);
    }

    // Fill in the remaining unused characters in normal order
    for (i = 'A'; i <= 'Z'; i++) {
        if (strchr(keyword, i) == NULL) {
            cipherSequence[len++] = i;
        }
    }

    // Null-terminate the cipher sequence
    cipherSequence[len] = '\0';
}

// Function to perform encryption using the generated cipher sequence
void encrypt(char *plaintext, char *cipherSequence, char *ciphertext) {
    int i, index;

    // Encrypt each character in the plaintext
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            index = toupper(plaintext[i]) - 'A';
            ciphertext[i] = isupper(plaintext[i]) ? cipherSequence[index] : tolower(cipherSequence[index]);
        } else {
            // Non-alphabetic characters remain unchanged
            ciphertext[i] = plaintext[i];
        }
    }

    // Null-terminate the ciphertext
    ciphertext[i] = '\0';
}

int main() {
    char keyword[] = "CIPHER";
    char cipherSequence[27]; // 26 letters + null terminator
    char plaintext[1000];
    char ciphertext[1000];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    // Remove the newline character from the input
    strtok(plaintext, "\n");

    // Generate the cipher sequence from the keyword
    generateCipherSequence(keyword, cipherSequence);

    // Encrypt the plaintext
    encrypt(plaintext, cipherSequence, ciphertext);

    // Display the results
    printf("\nKeyword: %s\n", keyword);
    printf("Cipher Sequence: %s\n", cipherSequence);
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}

