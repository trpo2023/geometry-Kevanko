#include <ctype.h>
#include <libgeometry/parser.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M_PI 3.14

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

void print_result(
        const char* output_path, char* name, double perimetr, double area)
{
    static unsigned int counter;
    FILE* file = fopen(output_path, "a");
    if (!file) {
        printf("Error: can't create output file:\n%s\n", output_path);
        return;
    }
    counter++;
    fprintf(file,
            "%d. %s\n perimetr: %f\n area: %f\n\n",
            counter,
            name,
            perimetr,
            area);
    fclose(file);
    printf("%d. %s\n perimetr: %f\n area: %f\n\n",
           counter,
           name,
           perimetr,
           area);
}
// Функция для парсинга круга
Circle parse_circle(char* input)
{
    Circle exit_error = {0.f, 0.f, 0.f, 0.f, 0.f, 0};
    const char* prefix = "circle(";
    char* start_ptr = input;
    int prefix_len = strlen(prefix);
    if (strncmp(input, prefix, prefix_len)) {
        handle_error("Error: expected '('", start_ptr, 7);
        return exit_error;
    }
    input += prefix_len;
    char* end_ptr;
    double x = strtod(input, &end_ptr);
    if (end_ptr == input || *end_ptr != ' ') {
        handle_error(
                "Error: expected <double>", start_ptr, end_ptr - start_ptr);
        return exit_error;
    }
    input = end_ptr + 1;
    double y = strtod(input, &end_ptr);
    if (end_ptr == input || *end_ptr != ',') {
        handle_error("Error: expected ','", start_ptr, end_ptr - start_ptr);
        return exit_error;
    }
    input = end_ptr + 1;
    double radius = strtod(input, &end_ptr);
    if (end_ptr == input || *end_ptr != ')') {
        handle_error("Error: expected ')'", start_ptr, end_ptr - start_ptr);
        return exit_error;
    }
    end_ptr += 1;
    if (*end_ptr != '\0') {
        handle_error("Error: unexpected token", start_ptr, end_ptr - start_ptr);
        return exit_error;
    }
    Circle result
            = {.x = x,
               .y = y,
               .r = radius,
               .perimetr = 2 * M_PI * radius,
               .area = M_PI * radius * radius,
               .exist = 1};
    return result;
}
// Функция для обработки входной строки
int parse_input(char* input, const char* output_path)
{
    input = lower_all(input);
    if (strncmp(input, "circle", 6) == 0) {
        Circle circle = parse_circle(input);
        if (circle.exist) {
            char name[50];
            sprintf(name,
                    "circle(%.1f %.1f %.1f)",
                    circle.x,
                    circle.y,
                    circle.r);

            print_result(output_path, name, circle.perimetr, circle.area);
            return 0;
        }
    }
    handle_error(
            "Error at column 0: expected 'circle', 'triangle' or 'polygon'",
            input,
            0);
    return 1;

