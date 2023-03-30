#pragma once
#define MAX_INPUT_LENGTH 100

typedef struct Circle {
    double x, y, r, perimetr, area;
} Circle;

enum ERRORS_ID {
    ERROR_FILE_OUTPUT = 1,
    ERROR_FILE_INPUT,
    ERROR_PARSER_NAME,
    ERROR_PARSER_LEFT_PARENTHESIS,
    ERROR_PARSER_RIGHT_PARENTHESIS,
    ERROR_PARSER_COMMA,
    ERROR_PARSER_DOUBLE,
    ERROR_PARSER_UNEXPECTED_TOKEN,
};
int is_input_files_exist(const char* input_path, const char* output_path);
// Функция для обработки ошибок и вывода сообщения
void handle_error(int error_id, char* str);
// Функция для перевода строки в нижний регистр
char* lower_all(char* str);
// Функция для парсинга круга
int is_circle(char* str);
int is_left_parenthesis(char* str);
int is_x_circle(char* str, double* x);
int is_y_circle(char* str, double* y);
int is_r_circle(char* str, double* r);
int parse_circle(char* str, Circle* out_values);
// Функция для обработки входной строки
int parse_input(char* input, const char* output_file);
void print_circle(const char* output_path, Circle* circle);
