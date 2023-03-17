#include <libgeometry/parser.h>

int main()
{
    const char* file_path = "commands";
    FILE* file = fopen(file_path, "r");
    if (!file) {
        fprintf(stderr, "Error: can't open commands file:\n%s\n", file_path);
        return -1;
    }
    char input[MAX_INPUT_LENGTH];
    while (!feof(file)) {
        fgets(input, MAX_INPUT_LENGTH, file);
        input[strcspn(input, "\n")]
                = '\0'; // Удаляем символ переноса строки, если есть
        if (parse_input(input)) {
            return -1;
        }
    }
    fclose(file);
    return 0;
}
