#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libgeometry/parser.h>

int main()
{
    const char* output_path = "output";
    const char* input_path = "../input/commands";

    int status = is_input_files_exist(input_path, output_path);
    if (status) {
        handle_error(status, (char*)input_path);
        return status;
    }

    FILE* input_file = fopen(input_path, "r");
    char input[MAX_INPUT_LENGTH];
    Circle circle;
    while (fgets(input, MAX_INPUT_LENGTH, input_file)) {
        int index = strcspn(input, "\n");
        input[index] = '\0';
        status = parse_circle(input, &circle);
        if (status) {
            handle_error(status, input);
            return status;
        } else {
            calculate_circle(&circle);
            print_circle(output_path, &circle);
        }
    }
    fclose(input_file);
    return 0;
}
