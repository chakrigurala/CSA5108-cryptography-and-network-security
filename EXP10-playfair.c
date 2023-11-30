#include <stdio.h>
#include <string.h>

#define SIZE 5

// Function to find the position of a character in the Playfair matrix
void findPosition(char mat[SIZE][SIZE], char ch, int *row, int *col) {
    if (ch == 'J') {
        ch = 'I'; // Replace 'J' with 'I'
    }

    for (*row = 0; *row < SIZE; (*row)++) {
        for (*col = 0; *col < SIZE; (*col)++) {
            if (mat[*row][*col] == ch) {
                return;
            }
        }
    }
}

// Function to encrypt a digraph using the Playfair cipher
void encryptPlayfair(char mat[SIZE][SIZE], char digraph[2], char encrypted[2]) {
    int row1, col1, row2, col2;

    // Find positions of both letters in the matrix
    findPosition(mat, digraph[0], &row1, &col1);
    findPosition(mat, digraph[1], &row2, &col2);

    // If both letters are in the same row
    if (row1 == row2) {
        encrypted[0] = mat[row1][(col1 + 1) % SIZE];
        encrypted[1] = mat[row2][(col2 + 1) % SIZE];
    }
    // If both letters are in the same column
    else if (col1 == col2) {
        encrypted[0] = mat[(row1 + 1) % SIZE][col1];
        encrypted[1] = mat[(row2 + 1) % SIZE][col2];
    }
    // If letters are in different rows and columns
    else {
        encrypted[0] = mat[row1][col2];
        encrypted[1] = mat[row2][col1];
    }
}

int main() {
    char key[] = "MFHIKUNOPQZVWXYELARCDSTBG"; // Playfair key
    char mat[SIZE][SIZE];
    int k = 0;

    // Create Playfair matrix
    int i;
    for (i = 0; i < SIZE; i++) {
    	int j;
        for (j = 0; j < SIZE; j++) {
            mat[i][j] = key[k++];
        }
    }

    char message[] = "MUSTSEEYOUOVERCADOGANWESTCOMINGATONCE";
    int len = strlen(message);

    // Adjust message for Playfair cipher (insert 'X' between repeated letters)
    for (i = 0; i < len; i += 2) {
        if (message[i] == message[i + 1]) {
            len++;
            int j;
            for (j = len; j > i + 1; j--) {
                message[j] = message[j - 1];
            }
            message[i + 1] = 'X';
        }
    }

    // Encrypt the message using Playfair cipher
    char encryptedMessage[len];
    for (i = 0; i < len; i += 2) {
        encryptPlayfair(mat, &message[i], &encryptedMessage[i]);
    }

    // Display the encrypted message
    printf("Encrypted Message: %s\n", encryptedMessage);

    return 0;
}

