#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libgeometry/parser.h>

int is_input_files_exist(const char* input_path, const char* output_path)
{
    FILE* output_file = fopen(output_path, "w");
    if (!output_file)
        return ERROR_FILE_OUTPUT;

    fclose(output_file);

    FILE* input_file = fopen(input_path, "r");

    if (!input_file)
        return ERROR_FILE_INPUT;

    fclose(input_file);
    return 0;
}

void handle_error(int error_id, char* str)
{
    char* error_msg;
    switch (error_id) {
    case ERROR_FILE_OUTPUT:
        error_msg = "Error: can't create output file";
        break;
    case ERROR_FILE_INPUT:
        error_msg = "Error: can't open input file";
        break;
    case ERROR_PARSER_NAME:
        error_msg = "Error: expected 'circle'";
        break;
    case ERROR_PARSER_LEFT_PARENTHESIS:
        error_msg = "Error: expected '('";
        break;
    case ERROR_PARSER_RIGHT_PARENTHESIS:
        error_msg = "Error: expected ')'";
        break;
    case ERROR_PARSER_COMMA:
        error_msg = "Error: expected ','";
        break;
    case ERROR_PARSER_DOUBLE:
        error_msg = "Error: expected <double>";
        break;
    case ERROR_PARSER_UNEXPECTED_TOKEN:
        error_msg = "Error: unexpected token";
        break;
    default:
        error_msg = "Error: something wrong";
        break;
    }
    fprintf(stderr, "%s\n%s\n", error_msg, str);
}

char* lower_all(char* str)
{
    int i = 0;
    while (str[i] != '\0') {
        str[i] = tolower(str[i]);
        i += 1;
    }
    return str;
}
void print_circle(const char* output_path, Circle* circle)
{
    static unsigned int counter;
    FILE* file = fopen(output_path, "a");
    counter++;
    fprintf(file,
            "%d. circle(%f %f, %f)\n perimetr: %f\n area: %f\n\n",
            counter,
            circle->x,
            circle->y,
            circle->r,
            circle->perimetr,
            circle->area);
    fclose(file);
    printf("%d. circle(%f %f, %f)\n perimetr: %f\n area: %f\n\n",
           counter,
           circle->x,
           circle->y,
           circle->r,
           circle->perimetr,
           circle->area);
}

int is_circle(char* str)
{
    if (strncmp(str, "circle", 6))
        return ERROR_PARSER_NAME;
    return 0;
}

int is_left_parenthesis(char* str)
{
    if (strncmp(str + 6, "(", 1)) {
        return ERROR_PARSER_LEFT_PARENTHESIS;
    }
    return 0;
}

int is_x_circle(char* str, double* x)
{
    char* number_end;
    str += 7;
    *x = strtod(str, &number_end);
    if (number_end == str) {
        return ERROR_PARSER_DOUBLE;
    } else if (strncmp(number_end, " ", 1))
        return ERROR_PARSER_UNEXPECTED_TOKEN;
    return 0;
}

int is_y_circle(char* str, double* y)
{
    char* number_end;
    str += 7;
    strtod(str, &number_end);
    str = number_end + 1;
    *y = strtod(str, &number_end);
    if (number_end == str) {
        return ERROR_PARSER_DOUBLE;
    } else if (strncmp(number_end, ",", 1))
        return ERROR_PARSER_UNEXPECTED_TOKEN;
    return 0;
}

int is_r_circle(char* str, double* r)
{
    char* number_end;
    str += 7;
    strtod(str, &number_end);
    str = number_end + 1;
    strtod(str, &number_end);
    str = number_end + 1;
    *r = strtod(str, &number_end);
    if (number_end == str) {
        return ERROR_PARSER_DOUBLE;
    } else if (strncmp(number_end, ")", 1))
        return ERROR_PARSER_RIGHT_PARENTHESIS;
    str = number_end + 1;
    if (strncmp(str, "\0", 1))
        return ERROR_PARSER_UNEXPECTED_TOKEN;
    return 0;
}

void calculate_circle(Circle* circle)
{
    circle->perimetr = 2 * M_PI * circle->r;
    circle->area = M_PI * circle->r * circle->r;
}

int parse_circle(char* str, Circle* out_values)
{
    double x, y, r;
    int status;

    status = is_circle(str);
    if (status)
        return status;

    status = is_left_parenthesis(str);
    if (status)
        return status;

    status = is_x_circle(str, &x);
    if (status)
        return status;

    status = is_y_circle(str, &y);
    if (status)
        return status;

    status = is_r_circle(str, &r);
    if (status)
        return status;

    out_values->x = x;
    out_values->y = y;
    out_values->r = r;

    return 0;
}
