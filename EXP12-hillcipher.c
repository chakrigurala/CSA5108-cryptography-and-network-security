#include <stdio.h>
#include <string.h>

// Function to convert a character to its numerical value (A=0, B=1, ..., Z=25)
int charToNum(char ch) {
    if (ch >= 'a' && ch <= 'z') {
        return ch - 'a';
    } else if (ch >= 'A' && ch <= 'Z') {
        return ch - 'A';
    } else {
        return -1; // Invalid character
    }
}

// Function to encrypt a 2x2 matrix with a key matrix
void encryptHill(int key[2][2], int block[2], int result[2]) {
    result[0] = (key[0][0] * block[0] + key[0][1] * block[1]) % 26;
    result[1] = (key[1][0] * block[0] + key[1][1] * block[1]) % 26;
}

int main() {
    // Key matrix
    int key[2][2] = {
        {9, 4},
        {5, 7}
    };

    char message[] = "meet me at the usual place at ten rather than eight o'clock";
    int len = strlen(message);

    // Encrypt the message using Hill cipher
    printf("Encrypted Message: ");
    int i;
    for (i = 0; i < len; i += 2) {
        int block[2] = {charToNum(message[i]), charToNum(message[i + 1])};
        int result[2];

        encryptHill(key, block, result);

        // Convert numerical values back to characters
        printf("%c%c ", result[0] + 'A', result[1] + 'A');
    }

    printf("\n");

    return 0;
}

