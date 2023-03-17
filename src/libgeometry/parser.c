#include <libgeometry/parser.h>

// Функция для обработки ошибок и вывода сообщения
void handle_error(const char* error_msg, const char* input, int pos)
{
    fprintf(stderr, "%s\n", input);
    for (int i = 0; i < pos; i++) {
        fprintf(stderr, " ");
    }
    fprintf(stderr, "^\n");
    fprintf(stderr, "%s at column %d\n", error_msg, pos);
}
// Функция для перевода строки в нижний регистр
char* lower_all(char* str)
{
    int i = 0;
    while (str[i] != '\0') {
        str[i] = tolower(str[i]);
        i += 1;
    }
    return str;
}
// Функция для парсинга круга
int parse_circle(char* input)
{
    const char* prefix = "circle(";
    char* start_ptr = input;
    int prefix_len = strlen(prefix);
    if (strncmp(input, prefix, prefix_len)) {
        handle_error("Error: expected '('", start_ptr, 7);
        return -1;
    }
    input += prefix_len;
    char* end_ptr;
    double x = strtod(input, &end_ptr);
    if (end_ptr == input || *end_ptr != ' ') {
        handle_error(
                "Error: expected <double>", start_ptr, end_ptr - start_ptr);
        return -1;
    }
    input = end_ptr + 1;
    double y = strtod(input, &end_ptr);
    if (end_ptr == input || *end_ptr != ',') {
        handle_error("Error: expected ','", start_ptr, end_ptr - start_ptr);
        return -1;
    }
    input = end_ptr + 1;
    double radius = strtod(input, &end_ptr);
    if (end_ptr == input || *end_ptr != ')') {
        handle_error("Error: expected ')'", start_ptr, end_ptr - start_ptr);
        return -1;
    }
    end_ptr += 1;
    if (*end_ptr != '\0') {
        handle_error("Error: unexpected token", start_ptr, end_ptr - start_ptr);
        return -1;
    }
    printf("circle(%f, %f) and radius %f\n", x, y, radius);

    const char* output_path = "output";
    FILE* file = fopen(output_path, "a");
    if (!file) {
        printf("Error: can't create output file:\n%s\n", output_path);
        return -1;
    }
    fprintf(file, "circle(%f, %f) and radius %f\n", x, y, radius);
    fclose(file);
    return 0;
}
// Функция для обработки входной строки
int parse_input(char* input)
{
    input = lower_all(input);
    if (strncmp(input, "circle", 6) == 0) {
        return parse_circle((char*)input);
    }
    handle_error(
            "Error at column 0: expected 'circle', 'triangle' or 'polygon'",
            input,
            0);
    return -1;
}
