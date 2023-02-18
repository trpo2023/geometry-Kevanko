#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


#define MAX_INPUT_LENGTH 100

// Функция для обработки ошибок и вывода сообщения
void handle_error(const char* error_msg, const char* input, int pos) {
    fprintf(stderr, "%s\n", input);
    for (int i = 0; i < pos; i++) {
        fprintf(stderr, " ");
    }
    fprintf(stderr, "^\n");
    fprintf(stderr, "%s at column %d\n", error_msg, pos);
}

// Функция для парсинга круга
int parse_circle(char* input) {
    const char* prefix = "circle(";
    char* start_ptr = input;
    int prefix_len = strlen(prefix);
    if (strncmp(input, prefix, prefix_len)) {
        handle_error("Error: expected 'circle('", start_ptr, 0);
        return -1;
    }
    input += prefix_len;

    char* end_ptr;
    double x = strtod(input, &end_ptr);
    if (end_ptr == input || *end_ptr != ' ') {
        handle_error("Error: expected <double>", start_ptr, end_ptr - start_ptr);
        return -1;
    }
    input = end_ptr + 1;

    double y = strtod(input, &end_ptr);
    if (end_ptr == input || *end_ptr != ',' ) {
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
    return 0;
}

// Функция для обработки входной строки
int parse_input(const char* input) {
    if (strncmp(input, "circle", 6) == 0) {
        return parse_circle((char*)input);
    }
    handle_error("Error: unexpected token", input, 0);
    return -1;
}



int main(int argv, char** argc)
{   
    
    const char* filePath = "commands";
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Error: can't open commands file:\n");
        printf("%s\n", filePath);
        return 1;
    }

    char input[MAX_INPUT_LENGTH];

    while (!feof(file)) {

        fgets(input, MAX_INPUT_LENGTH, file);
        input[strcspn(input, "\n")] = '\0'; // Удаляем символ переноса строки, если есть

        if (parse_input(input)) {
            return 1;
        }

    }
    
    fclose(file);
    return 0;
}
