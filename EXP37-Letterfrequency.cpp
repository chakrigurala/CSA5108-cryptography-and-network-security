#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to calculate the frequency of each letter in a string
void calculateFrequency(const char *text, int *frequency) {
    for (int i = 0; i < strlen(text); i++) {
        if (isalpha(text[i])) {
            char ch = tolower(text[i]);
            frequency[ch - 'a']++;
        }
    }
}

// Function to perform a letter frequency attack and print possible plaintexts
void letterFrequencyAttack(const char *ciphertext, int topResults) {
    int frequency[ALPHABET_SIZE] = {0};
    calculateFrequency(ciphertext, frequency);

    // Find the most frequent letter in the ciphertext
    int maxFrequency = 0;
    char mostFrequentLetter = 'a';

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (frequency[i] > maxFrequency) {
            maxFrequency = frequency[i];
            mostFrequentLetter = 'a' + i;
        }
    }

    // Assume the most frequent letter in the ciphertext corresponds to 'e' in the plaintext
    // Calculate the potential shift value
    int shift = mostFrequentLetter - 'e';
    if (shift < 0) {
        shift += ALPHABET_SIZE;
    }

    // Decrypt the ciphertext using the calculated shift
    printf("Possible plaintexts:\n");

    for (int i = 0; i < topResults; i++) {
        for (int j = 0; j < strlen(ciphertext); j++) {
            char ch = ciphertext[j];

            if (isalpha(ch)) {
                char base = isupper(ch) ? 'A' : 'a';
                char decryptedChar = (ch - base - shift + ALPHABET_SIZE) % ALPHABET_SIZE + base;
                printf("%c", decryptedChar);
            } else {
                printf("%c", ch);
            }
        }

        printf("\n");
    }
}

int main() {
    // Example ciphertext
    const char *ciphertext = "Gur dhvpx oebja sbk whzcf bire gur ynml qbt.";

    // Specify the number of top results to display
    int topResults = 3;

    // Perform the letter frequency attack
    letterFrequencyAttack(ciphertext, topResults);

    return 0;
}

