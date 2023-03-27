#pragma once
#define MAX_INPUT_LENGTH 100

typedef struct Circle{
	double x, y, r, perimetr, area;
} Circle;

// Функция для обработки ошибок и вывода сообщения
void handle_error(const char* error_msg, const char* input, int pos);
// Функция для перевода строки в нижний регистр
char* lower_all(char* str);
// Функция для парсинга круга
Circle *parse_circle(char* input);
// Функция для обработки входной строки
int parse_input(char* input, const char* output_file);

void print_result(const char* output_path, char* name, double perimetr, double area);
