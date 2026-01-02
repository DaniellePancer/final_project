#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>


static void skip_spaces(void) {
    int c;
    while ((c = getchar()) != EOF) {
        if (!isspace(c)) {
            ungetc(c, stdin);
            return;
        }
    }
}

static int read_numbers(int *out, int base, int width, int signed_flag) {
    int c, value = 0, sign = 1, digits = 0;

    skip_spaces();
    c = getchar();

    if (signed_flag && c == '-') {
        sign = -1;
        c = getchar();
    }

    while (c != EOF && width != 0) {
        int digit = -1;

        if (isdigit(c)) digit = c - '0';
        else if (isalpha(c)) digit = tolower(c) - 'a' + 10;

        if (digit < 0 || digit >= base) break;

        value = value * base + digit;
        digits++;
        width--;
        c = getchar();
    }

    if (c != EOF) ungetc(c, stdin);
    if (digits == 0) return 0;

    *out = value * sign;
    return 1;
}

static int read_unsigned(unsigned *out, int width) {
    int c;
    unsigned value = 0;
    int digits = 0;

    skip_spaces();
    c = getchar();

    while (isdigit(c) && width != 0) {
        value = value * 10 + (c - '0');
        digits++;
        width--;
        c = getchar();
    }

    if (c != EOF) ungetc(c, stdin);
    if (digits == 0) return 0;

    *out = value;
    return 1;
}

static int read_floats(float *out, int width) {
    int c, sign = 1, seen_dot = 0;
    float value = 0.0f, divisor = 10.0f;

    skip_spaces();
    c = getchar();

    if (c == '-') {
        sign = -1;
        c = getchar();
    }

    if (!isdigit(c) && c != '.') return 0;

    while ((isdigit(c) || c == '.') && width != 0) {
        if (c == '.') {
            if (seen_dot) break;
            seen_dot = 1;
        } else {
            if (!seen_dot) {
                value = value * 10 + (c - '0');
            } else {
                value += (c - '0') / divisor;
                divisor *= 10.0f;
            }
        }
        width--;
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

    while (c != EOF && !isspace(c) && width != 0) {
        out[count++] = c;
        width--;
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

    while ((c = getchar()) != EOF && c != '"' && width != 0) {
        out[count++] = c;
        width--;
    }

    out[count] = '\0';
    return 1;
}



int my_scanf(const char *format, ...) {
    va_list parameters;
    va_start(parameters, format);

    int assigned = 0;

    while (*format) {
        if (*format == '%') {
            format++;
            int width = 0;

            while (isdigit(*format)) {
                width = width * 10 + (*format - '0');
                format++;
            }
            if (width == 0) width = -1;

            switch (*format) {
                case 'd': {
                    int *p = va_arg(parameters, int *);
                    if (!read_numbers(p, 10, width, 1)) goto done;
                    assigned++;
                    break;
                }
                case 'x': {
                    int *p = va_arg(parameters, int *);
                    if (!read_numbers(p, 16, width, 0)) goto done;
                    assigned++;
                    break;
                }
                case 'b': {
                    int *p = va_arg(parameters, int *);
                    if (!read_numbers(p, 2, width, 0)) goto done;
                    assigned++;
                    break;
                }
                case 'u': {
                    unsigned *p = va_arg(parameters, unsigned *);
                    if (!read_unsigned(p, width)) goto done;
                    assigned++;
                    break;
                }
                case 'f': {
                    float *p = va_arg(parameters, float *);
                    if (!read_floats(p, width)) goto done;
                    assigned++;
                    break;
                }
                case 's': {
                    char *p = va_arg(parameters, char *);
                    if (!read_strings(p, width)) goto done;
                    assigned++;
                    break;
                }
                case 'q': {
                    char *p = va_arg(parameters, char *);
                    if (!read_quote_strings(p, width)) goto done;
                    assigned++;
                    break;
                }
                case 'c': {
                    char *p = va_arg(parameters, char *);
                    if (!read_characters(p)) goto done;
                    assigned++;
                    break;
                }
                default:
                    goto done;
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

