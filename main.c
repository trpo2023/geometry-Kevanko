#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Point {
    int x;
    int y;
} Point;

typedef struct Circule {
    Point point;
    float size;
} Circule;

int main(int argv, char** argc)
{
    for (int i = 1; i < argv; i++) {
        printf("%s\n", argc[i]);
    }
    FILE* file = fopen("commands", "r");
    if (file == NULL) {
        printf("Error: can't open commands file");
        return -1;
    }
    // Circule circule[50];

    int count = 0;

    char bufStr[50][100];
    fgets(bufStr[count], 100, file);

    while (bufStr[count][0] != '\0') {
        count += 1;
        fgets(bufStr[count], 100, file);
    }
    for (int i = 0; i < count; i++) {
        for (int j = 0; bufStr[i][j] != '\0'; j++)
            printf("%c", bufStr[i][j]);
    }

    fclose(file);
    return 0;
}
