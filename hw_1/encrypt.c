#include <stdio.h>

char alphabet[61] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '(', '<', '=', '+', ')', '[', '*', '/', ']', '{', '>', '!', '-', '}', '?', '\\', '&', '|', '%', '_', ';', '"', '#', '.', '\'', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

void caesar_cipher(char *text, int key) {
    while (*text) {  
        int i;
        for (i = 0; i < 61; i++) {
            if (*text == alphabet[i]) {
                *text = alphabet[(i + key) % 61]; 
                break;
            }
        }  
        text++;
    }
}

int main() {

    char c;
    int key = 7;  /*student id: 220104004849*/
    int comment_len;

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("encrypted.txt", "w");

    if (input == NULL) {
        perror("Couldn't open the input.txt");
        return -1;
    }

    while ((c = fgetc(input)) != EOF) {

        if (c == '/') {
            if ((c = fgetc(input)) == '*'){ /*making sure we are inside the comment*/
                comment_len = 0;

                while ((c = fgetc(input)) && c != EOF && !(c == '*' && (c = fgetc(input)) == '/')) { /*maybe writing a still in comment func would be better*/
                    comment_len++;
                }
                fprintf(output, "@ %d", comment_len);

            } else {
                caesar_cipher(&c, key);
                fputc(c, output);
            }

        } else {
            caesar_cipher(&c, key);
            fputc(c, output);
        }
    }


    fclose(input);
    fclose(output);

    return 0;
}

