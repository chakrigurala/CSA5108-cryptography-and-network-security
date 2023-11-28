#include <stdio.h>

// Function to decrypt the ciphertext
void decrypt(char *ciphertext, char *plaintext) {
    // Replace characters based on frequency and common words
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        switch (ciphertext[i]) {
            case '†':
                plaintext[i] = 'e';
                break;
            case '‡':
                plaintext[i] = 't';
                break;
            case '¶':
                plaintext[i] = 'h';
                break;
            case '—':
                plaintext[i] = 'a';
                break;
            case ';':
                plaintext[i] = 'o';
                break;
            case ':':
                plaintext[i] = 'n';
                break;
            case ')':
                plaintext[i] = 's';
                break;
            case '(':
                plaintext[i] = 'r';
                break;
            case ']':
                plaintext[i] = 'i';
                break;
            case '8':
                plaintext[i] = 'c';
                break;
            case '4':
                plaintext[i] = 'd';
                break;
            case '5':
                plaintext[i] = 'u';
                break;
            case '6':
                plaintext[i] = 'f';
                break;
            case '2':
                plaintext[i] = 'g';
                break;
            case '0':
                plaintext[i] = 'l';
                break;
            case '3':
                plaintext[i] = 'm';
                break;
            case '9':
                plaintext[i] = 'p';
                break;
            default:
                plaintext[i] = ciphertext[i];
        }
    }
    // Null-terminate the plaintext
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    char ciphertext[] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83"
                        "(88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8*"
                        ";4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81 (‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";
    char plaintext[1000];

    // Decrypt the ciphertext
    decrypt(ciphertext, plaintext);

    // Display the decrypted message
    printf("Decrypted Message: %s\n", plaintext);

    return 0;
}

