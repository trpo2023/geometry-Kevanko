#include <stdio.h>
#include <stdlib.h>

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
    int count = 0;

    char bufStr[50][500];
    fgets(bufStr[count], 500, file);

    while (bufStr[count][0] != '\0') {
        count += 1;
        fgets(bufStr[count], 500, file);
        printf("%s", bufStr[count]);

    }

    fclose(file);
    return 0;
}
