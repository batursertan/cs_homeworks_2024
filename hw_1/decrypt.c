#include <stdio.h>

char alphabet[61] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '(', '<', '=', '+', ')', '[', '*', '/', ']', '{', '>', '!', '-', '}', '?', '\\', '&', '|', '%', '_', ';', '"', '#', '.', '\'', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

void caesar_decipher(char *text, int key) {
    while (*text) {
        int i;
        for (i = 0; i < 61; i++) {
            if (*text == alphabet[i]) {
                *text = alphabet[(i - key + 61) % 61];
                break;
            }
        }     
        text++;
    }
}

int main() {

    char c;
    int key = 7;
    int comment_len;
    int in_comm = 0;

    FILE *input = fopen("encrypted.txt", "r");
    FILE *output = fopen("decrypted.txt", "w");

    if (input == NULL) {
        perror("Couldn't open the encrypted.txt");
        return -1;
    }

    while ((c = fgetc(input)) != EOF) {

        if (c == '@') {
            fscanf(input, "%d", &comment_len); 
            fprintf(output, "<Comment with length %d characters>", comment_len);
            in_comm = 1; 
        } else if (!in_comm && c == '\n') { /* making sure to print the new line characters before the decypher*/
            fputc(c, output);
        } else if (!in_comm) { 
            caesar_decipher(&c, key);
            fputc(c, output);
        } else if (in_comm && c == '\n') { /* same new line logic before but inside the comment*/
            in_comm = 0; 
            fputc(c, output);
        }
    }

    fclose(input);
    fclose(output);

    return 0;
}
