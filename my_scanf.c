#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>   

static FILE *input_file = NULL;

#define getchar() (input_file ? fgetc(input_file) : fgetc(stdin))
#define ungetc(c, f) (input_file ? ungetc(c, input_file) : ungetc(c, stdin))

static void skip_spaces(void) {
    int c;
    while ((c = getchar()) != EOF) {
        if (!isspace(c)) {
            ungetc(c, stdin);
            return;
        }
    }
}

static int read_numbers(long long *out, int base, int width, int signed_flag) {
    int c, sign = 1, digits = 0;
    long long value = 0;
    skip_spaces();
    c = getchar();
    if (signed_flag && (c == '-' || c == '+')) {
        if (c == '-') sign = -1;
        c = getchar();
    }
    while (c != EOF && (width != 0)) {
        int digit = -1;
        if (isdigit(c)) digit = c - '0';
        else if (isalpha(c)) digit = tolower(c) - 'a' + 10;
        if (digit < 0 || digit >= base) break;
        value = value * base + digit;
        digits++;
        if (width > 0) width--;
        c = getchar();
    }
    if (c != EOF) ungetc(c, stdin);
    if (digits == 0) return 0;
    *out = value * sign;
    return 1;
}

static int read_unsigned(unsigned long long *out, int width) {
    int c, digits = 0;
    unsigned long long value = 0;
    skip_spaces();
    c = getchar();
    while (isdigit(c) && (width != 0)) {
        value = value * 10 + (c - '0');
        digits++;
        if (width > 0) width--;
        c = getchar();
    }
    if (c != EOF) ungetc(c, stdin);
    if (digits == 0) return 0;
    *out = value;
    return 1;
}

static int read_floats(long double *out, int width) {
    int c, sign = 1, seen_dot = 0;
    long double value = 0.0, divisor = 10.0;
    skip_spaces();
    c = getchar();
    if (c == '-' || c == '+') { if (c == '-') sign = -1; c = getchar(); }
    if (!isdigit(c) && c != '.') return 0;
    while ((isdigit(c) || c == '.') && (width != 0)) {
        if (c == '.') {
            if (seen_dot) break;
            seen_dot = 1;
        } else {
            if (!seen_dot) value = value * 10 + (c - '0');
            else { value += (c - '0') / divisor; divisor *= 10.0; }
        }
        if (width > 0) width--;
        c = getchar();
    }
    if (c != EOF) ungetc(c, stdin);
    *out = value * sign;
    return 1;
}

static int read_strings(char *out, int width) {
    int c, count = 0;
    skip_spaces();
    c = getchar();
    while (c != EOF && !isspace(c) && (width != 0)) {
        out[count++] = c;
        if (width > 0) width--;
        c = getchar();
    }
    if (c != EOF) ungetc(c, stdin);
    out[count] = '\0';
    return count > 0;
}

static int read_characters(char *out) {
    int c = getchar();
    if (c == EOF) return 0;
    *out = (char)c;
    return 1;
}

static int read_quote_strings(char *out, int width) {
    int c, count = 0;
    skip_spaces();
    c = getchar();
    if (c != '"') return 0;
    while ((c = getchar()) != EOF && c != '"' && (width != 0)) {
        out[count++] = c;
        if (width > 0) width--;
    }
    out[count] = '\0';
    return 1;
}


static int read_cat(int *out, int width) {
    char buffer[16];
    if (!read_strings(buffer, width)) return 0;

    if (!strcmp(buffer, "cat") || !strcmp(buffer, "meow"))
        *out = 1;   
    else
        *out = 0;   

    return 1;
}

int my_scanf(const char *format, ...) {
    va_list parameters;
    va_start(parameters, format);
    int assigned = 0;

    while (*format) {
        if (*format == '%') {
            format++;
            int width = -1;
            int length = 0;

            if (isdigit(*format)) {
                width = 0;
                while (isdigit(*format)) {
                    width = width * 10 + (*format - '0');
                    format++;
                }
            }

            if (*format == 'h') { format++; if (*format == 'h') { length = 2; format++; } else length = 1; }
            else if (*format == 'l') { format++; if (*format == 'l') { length = 4; format++; } else length = 3; }
            else if (*format == 'L') { length = 5; format++; }

            switch (*format) {
                case 'd': case 'i': {
                    long long temp;
                    if (!read_numbers(&temp, 10, width, 1)) goto done;
                    if (length == 0) { int *p = va_arg(parameters, int*); *p = (int)temp; }
                    else if (length == 1) { short *p = va_arg(parameters, short*); *p = (short)temp; }
                    else if (length == 2) { signed char *p = va_arg(parameters, signed char*); *p = (signed char)temp; }
                    else if (length == 3) { long *p = va_arg(parameters, long*); *p = (long)temp; }
                    else if (length == 4) { long long *p = va_arg(parameters, long long*); *p = temp; }
                    assigned++; break;
                }
                case 'u': {
                    unsigned long long temp;
                    if (!read_unsigned(&temp, width)) goto done;
                    if (length == 0) { unsigned *p = va_arg(parameters, unsigned*); *p = (unsigned)temp; }
                    else if (length == 1) { unsigned short *p = va_arg(parameters, unsigned short*); *p = (unsigned short)temp; }
                    else if (length == 2) { unsigned char *p = va_arg(parameters, unsigned char*); *p = (unsigned char)temp; }
                    else if (length == 3) { unsigned long *p = va_arg(parameters, unsigned long*); *p = (unsigned long)temp; }
                    else if (length == 4) { unsigned long long *p = va_arg(parameters, unsigned long long*); *p = temp; }
                    assigned++; break;
                }
                case 'x': {
                    unsigned long long temp;
                    if (!read_numbers((long long*)&temp, 16, width, 0)) goto done;
                    unsigned *p = va_arg(parameters, unsigned*);
                    *p = (unsigned)temp;
                    assigned++; break;
                }
                case 'b': {
                    long long temp;
                    if (!read_numbers(&temp, 2, width, 0)) goto done;
                    int *p = va_arg(parameters, int*);
                    *p = (int)temp;
                    assigned++; break;
                }
                case 'f': {
                    long double temp;
                    if (!read_floats(&temp, width)) goto done;
                    if (length == 0) { float *p = va_arg(parameters, float*); *p = (float)temp; }
                    else if (length == 3) { double *p = va_arg(parameters, double*); *p = (double)temp; }
                    else if (length == 5) { long double *p = va_arg(parameters, long double*); *p = temp; }
                    assigned++; break;
                }
                case 's': {
                    char *p = va_arg(parameters, char*);
                    if (!read_strings(p, width)) goto done;
                    assigned++; break;
                }
                case 'c': {
                    char *p = va_arg(parameters, char*);
                    if (!read_characters(p)) goto done;
                    assigned++; break;
                }
                case 'q': {
                    char *p = va_arg(parameters, char*);
                    if (!read_quote_strings(p, width)) goto done;
                    assigned++; break;
                }
                case 'C': {   
                    int *p = va_arg(parameters, int*);
                    if (!read_cat(p, width)) goto done;
                    assigned++; break;
                }
                default: goto done;
            }

        } else if (isspace(*format)) {
            skip_spaces();
        } else {
            int c = getchar();
            if (c != *format) goto done;
        }
        format++;
    }

done:
    va_end(parameters);
    return assigned;
}
