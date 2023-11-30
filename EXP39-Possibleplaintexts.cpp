#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to perform a letter frequency attack on an additive cipher
void frequencyAttack(const char* ciphertext, int topN) {
    int len = strlen(ciphertext);

    // Initialize an array to store the frequency of each letter
    int frequency[ALPHABET_SIZE];
    memset(frequency, 0, sizeof(frequency));

    // Count the frequency of each letter in the ciphertext
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            frequency[toupper(ciphertext[i]) - 'A']++;
        }
    }

    // Find the most frequent letter in English
    int maxFreq = 0;
    int maxIndex = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (frequency[i] > maxFreq) {
            maxFreq = frequency[i];
            maxIndex = i;
        }
    }

    // Guess the key by assuming the most frequent letter in English corresponds to 'E'
    int key = (maxIndex - ('E' - 'A') + ALPHABET_SIZE) % ALPHABET_SIZE;

    // Decrypt the ciphertext using the guessed key
    printf("Possible plaintexts (Top %d):\n", topN);
    for (int i = 0; i < topN; i++) {
        printf("%d. ", i + 1);
        for (int j = 0; j < len; j++) {
            if (isalpha(ciphertext[j])) {
                char decrypted = (toupper(ciphertext[j]) - 'A' - key + ALPHABET_SIZE) % ALPHABET_SIZE + 'A';
                if (islower(ciphertext[j])) {
                    decrypted = tolower(decrypted);
                }
                printf("%c", decrypted);
            } else {
                printf("%c", ciphertext[j]);
            }
        }
        printf("\n");
        key = (key + 1) % ALPHABET_SIZE; // Try the next key
    }
}

int main() {
    char ciphertext[] = "Ifmmp xpsme!";

    int topN = 10;
    frequencyAttack(ciphertext, topN);

    return 0;
}

