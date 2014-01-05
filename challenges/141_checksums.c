#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MAX_LINE_SZ 201

int Fletcher16(uint8_t data[], int length) {
    uint16_t sum1 = 0;
    uint16_t sum2 = 0;
    int i;

    for (i = 0; i < length; i++) {
        sum1 = (sum1 + data[i]) % 255;
        sum2 = (sum2 + sum1) % 255;
    }
    sum1 += sum2 * 256;

    return sum1;
}

int main() {
    int i, lines;
    uint8_t data[50][200];

    scanf("%d\n", &lines);
    if (lines > 50) return 1;

    for (i = 0; i < lines; i++)
        fgets(data[i], MAX_LINE_SZ, stdin);

    for (i = 0; i < lines; i++) {
        if (data[i][strlen(data[i]) - 1] == '\n')
            data[i][strlen(data[i]) - 1] = '\0';
        printf("%X\n", Fletcher16(data[i], strlen(data[i])));
    }

    return 0;
}
