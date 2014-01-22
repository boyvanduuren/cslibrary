/*
    See http://redd.it/1heozl
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 100

char* convertUpper(char* input) {
    int i;

    for (i = 0; i < strlen(input); i++)
        input[i] = toupper(input[i]);

    return input;
}

char* convertReverse(char* input) {
    int i, length = strlen(input);
    char* output = malloc(length);


    for (i = 1; i <= length; i++)
        output[i - 1] = input[length - i];
    output[length] = '\0';

    return output;
}

int main() {
    int linesOfInput, i;
    char input[BUFFER];
    char* token;
    char* left;

    scanf("%d\n", &linesOfInput);

    for (i = 0; i < linesOfInput; i++) {
        fgets(input, sizeof(input), stdin);
        input[strlen(input) - 1] = '\0';

        token = strtok(input, " ");

        if (token[0] == '0') {
            token = strtok(NULL, " ");
            left = token;
            token = strtok(NULL, " ");

            if (strcmp(convertReverse(left), token) == 0) printf("Good test data\n");
            else printf("Mismatch! Bad test data\n");
        }
        else if (token[0] == '1') {
            token = strtok(NULL, " ");
            left = token;
            token = strtok(NULL, " ");

            if (strcmp(convertUpper(left), token) == 0) printf("Good test data\n");
            else printf("Mismatch! Bad test data\n");
        }
    }

    return 0;
}
