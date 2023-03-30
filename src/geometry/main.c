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
        handle_error(status, " ");
        return status;
    }

    FILE* input_file = fopen(input_path, "r");
    char input[MAX_INPUT_LENGTH];
    Circle* circle = (Circle*)malloc(sizeof(Circle));
    while (!feof(input_file)) {
        fgets(input, MAX_INPUT_LENGTH, input_file);
        input[strcspn(input, "\n")] = '\0';
        status = parse_circle(input, circle);
        if (status) {
            handle_error(status, input);
            return status;
        } else {
            print_circle(output_path, circle);
        }
    }
    free(circle);
    fclose(input_file);
    return 0;
}