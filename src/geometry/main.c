#include <libgeometry/parser.h>

int main()
{
    const char* output_path = "output";
    const char* input_path = "../Input/commands";

    FILE* output_file = fopen(output_path, "w");
    if (!output_file) {
        fprintf(stderr, "Error: can't open output file:\n%s\n", output_path);
        return 1;
    }
    fclose(output_file);

    FILE* input_file = fopen(input_path, "r");
    if (!input_file) {
        fprintf(stderr, "Error: can't open commands file:\n%s\n", input_path);
        return 1;
    }
    char input[MAX_INPUT_LENGTH];
    
    while (!feof(input_file)) {
        fgets(input, MAX_INPUT_LENGTH, input_file);
        input[strcspn(input, "\n")] = '\0';
        if (parse_input(input, output_path)) {
            return 1;
        }
    }
    fclose(input_file);
    return 0;
}
