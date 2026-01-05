#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_scanf.c"

void rand_string(char *s, size_t len) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (size_t i = 0; i < len; i++) {
        s[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    s[len] = '\0';
}

void run_tests() {

    {
        int x = 0;
        FILE *temp_file = tmpfile();
        fprintf(temp_file, "42\n");
        rewind(temp_file);
        input_file = temp_file;
        int assigned = my_scanf("%d", &x);
        input_file = NULL; fclose(temp_file);
        assert(assigned == 1 && x == 42);
    }

    {
        short x = 0;
        FILE *temp_file = tmpfile();
        fprintf(temp_file, "-32000\n");
        rewind(temp_file);
        input_file = temp_file;
        int assigned = my_scanf("%hd", &x);
        input_file = NULL; fclose(temp_file);
        assert(assigned == 1 && x == -32000);
    }

    {
        signed char x = 0;
        FILE *temp_file = tmpfile();
        fprintf(temp_file, "127\n");
        rewind(temp_file);
        input_file = temp_file;
        int assigned = my_scanf("%hhd", &x);
        input_file = NULL; fclose(temp_file);
        assert(assigned == 1 && x == 127);
    }

    {
        long x = 0;
        FILE *temp_file = tmpfile();
        fprintf(temp_file, "-2147483648\n");
        rewind(temp_file);
        input_file = temp_file;
        int assigned = my_scanf("%ld", &x);
        input_file = NULL; fclose(temp_file);
        assert(assigned == 1 && x == -2147483648L);
    }

    {
        long long x = 0;
        FILE *temp_file = tmpfile();
        fprintf(temp_file, "9223372036854775807\n");
        rewind(temp_file);
        input_file = temp_file;
        int assigned = my_scanf("%lld", &x);
        input_file = NULL; fclose(temp_file);
        assert(assigned == 1 && x == 9223372036854775807LL);
    }

    {
        unsigned u = 0;
        FILE *temp_file = tmpfile();
        fprintf(temp_file, "12345\n");
        rewind(temp_file);
        input_file = temp_file;
        int assigned = my_scanf("%u", &u);
        input_file = NULL; fclose(temp_file);
        assert(assigned == 1 && u == 12345U);
    }

    {
        unsigned short u = 0;
        FILE *temp_file = tmpfile();
        fprintf(temp_file, "65535\n");
        rewind(temp_file);
        input_file = temp_file;
        int assigned = my_scanf("%hu", &u);
        input_file = NULL; fclose(temp_file);
        assert(assigned == 1 && u == 65535U);
    }

    {
        unsigned char u = 0;
        FILE *temp_file = tmpfile();
        fprintf(temp_file, "255\n");
        rewind(temp_file);
        input_file = temp_file;
        int assigned = my_scanf("%hhu", &u);
        input_file = NULL; fclose(temp_file);
        assert(assigned == 1 && u == 255U);
    }

    {
        unsigned long u = 0;
        FILE *temp_file = tmpfile();
        fprintf(temp_file, "4294967295\n");
        rewind(temp_file);
        input_file = temp_file;
        int assigned = my_scanf("%lu", &u);
        input_file = NULL; fclose(temp_file);
        assert(assigned == 1 && u == 4294967295UL);
    }

    {
        unsigned long long u = 0;
        FILE *temp_file = tmpfile();
        fprintf(temp_file, "18446744073709551615\n");
        rewind(temp_file);
        input_file = temp_file;
        int assigned = my_scanf("%llu", &u);
        input_file = NULL; fclose(temp_file);
        assert(assigned == 1 && u == 18446744073709551615ULL);
    }

    {
        unsigned x = 0;
        FILE *temp_file = tmpfile();
        fprintf(temp_file, "1a2b\n");
        rewind(temp_file);
        input_file = temp_file;
        int assigned = my_scanf("%x", &x);
        input_file = NULL; fclose(temp_file);
        assert(assigned == 1 && x == 0x1a2b);
    }

    {
        int x = 0;
        FILE *temp_file = tmpfile();
        fprintf(temp_file, "1011\n");
        rewind(temp_file);
        input_file = temp_file;
        int assigned = my_scanf("%b", &x);
        input_file = NULL; fclose(temp_file);
        assert(assigned == 1 && x == 11);
    }

    {
        float fval = 0;
        FILE *temp_file = tmpfile();
        fprintf(temp_file, "12.34\n");
        rewind(temp_file);
        input_file = temp_file;
        int assigned = my_scanf("%f", &fval);
        input_file = NULL; fclose(temp_file);
        assert(assigned == 1 && fval > 12.33f && fval < 12.35f);
    }

    {
        double dval = 0;
        FILE *temp_file = tmpfile();
        fprintf(temp_file, "-0.1234\n");
        rewind(temp_file);
        input_file = temp_file;
        int assigned = my_scanf("%lf", &dval);
        input_file = NULL; fclose(temp_file);
        assert(assigned == 1 && dval < -0.1233 && dval > -0.1235);
    }

    {
        long double ldval = 0;
        FILE *temp_file = tmpfile();
        fprintf(temp_file, "3.14159\n");
        rewind(temp_file);
        input_file = temp_file;
        int assigned = my_scanf("%Lf", &ldval);
        input_file = NULL; fclose(temp_file);
        assert(assigned == 1 && ldval > 3.14158L && ldval < 3.14160L);
    }

    {
        char s[20];
        FILE *temp_file = tmpfile();
        fprintf(temp_file, "hello\n");
        rewind(temp_file);
        input_file = temp_file;
        int assigned = my_scanf("%s", s);
        input_file = NULL; fclose(temp_file);
        assert(assigned == 1 && strcmp(s, "hello") == 0);
    }

    {
        char s[5];
        FILE *temp_file = tmpfile();
        fprintf(temp_file, "HelloWorld\n");
        rewind(temp_file);
        input_file = temp_file;
        int assigned = my_scanf("%4s", s);
        input_file = NULL; fclose(temp_file);
        assert(assigned == 1 && strcmp(s, "Hell") == 0);
    }

    {
        char c;
        FILE *temp_file = tmpfile();
        fprintf(temp_file, "K\n");
        rewind(temp_file);
        input_file = temp_file;
        int assigned = my_scanf("%c", &c);
        input_file = NULL; fclose(temp_file);
        assert(assigned == 1 && c == 'K');
    }

    {
        char q[50];
        FILE *temp_file = tmpfile();
        fprintf(temp_file, "\"first quote\"\n");
        rewind(temp_file);
        input_file = temp_file;
        int assigned = my_scanf("%q", q);
        input_file = NULL; fclose(temp_file);
        assert(assigned == 1 && strcmp(q, "first quote") == 0);
    }

    {
        int cat_val;
        FILE *temp_file = tmpfile();
        fprintf(temp_file, "cat\n");
        rewind(temp_file);
        input_file = temp_file;
        int assigned = my_scanf("%C", &cat_val);
        input_file = NULL; fclose(temp_file);
        assert(assigned == 1 && cat_val == 1);
    }

    {
        int cat_val;
        FILE *temp_file = tmpfile();
        fprintf(temp_file, "meow\n");
        rewind(temp_file);
        input_file = temp_file;
        int assigned = my_scanf("%C", &cat_val);
        input_file = NULL; fclose(temp_file);
        assert(assigned == 1 && cat_val == 1);
    }

    {
        int cat_val;
        FILE *temp_file = tmpfile();
        fprintf(temp_file, "dog\n");
        rewind(temp_file);
        input_file = temp_file;
        int assigned = my_scanf("%C", &cat_val);
        input_file = NULL; fclose(temp_file);
        assert(assigned == 1 && cat_val == 0);
    }
}

int main() {
    run_tests();
    printf("All tests passed!\n");
    return 0;
}
