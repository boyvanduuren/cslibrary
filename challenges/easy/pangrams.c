#include <stdio.h>
#include <string.h>

int main() {
    int lines, lineIndex, charIndex, count, countChars[26] = { 0 };
    char sentence[512], currentChar;

    // Ask how many lines we have as input
    scanf("%d\n", &lines);

    // Loop for every line we want to input
    for (lineIndex = 0; lineIndex < lines; lineIndex++) {
        count = 0;

        // Ask for a sentence, save it in char sentence[512]
        fgets(sentence, sizeof(sentence), stdin);

        if (sentence) currentChar = 0;
        while (sentence[currentChar]) {
            // Add count for current character (0=a, 25=z)
            if (isalpha(sentence[currentChar])) {
                // If all letters are present, count will be 26 1's, or 0x3ffffff
                // it does this by bitshifting 0 to 25 places to the left,
                // then OR-ing 1 to that bit.
                count |= 1 << (tolower(sentence[currentChar]) - 'a');
                countChars[tolower((sentence[currentChar])) - 'a'] += 1;
            }
            if (currentChar < strlen(sentence)) currentChar++;
        }

        if (count == 0x3ffffff) {
            printf("True, ");
            for (charIndex = 0; charIndex < 26; charIndex++) {
                // Print count of characters
                printf("%c:%d ", charIndex + 'a', countChars[charIndex]);
                // Reset count
                countChars[charIndex] = 0;
            }
            printf("\n");
        }
        else
            printf("False\n");
    }
    return 0;
}
