#pragma once

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 100

// Функция для обработки ошибок и вывода сообщения
void handle_error(const char* error_msg, const char* input, int pos);
// Функция для перевода строки в нижний регистр
char* lower_all(char* str);
// Функция для парсинга круга
int parse_circle(char* input);
// Функция для обработки входной строки
int parse_input(char* input);
