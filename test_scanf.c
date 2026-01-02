#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
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
        FILE *f = tmpfile();
        fprintf(f, "42\n");
        rewind(f);
        input_file = f;
        int assigned = my_scanf("%d", &x);
        input_file = NULL; fclose(f);
        assert(assigned == 1 && x == 42);
    }

    {
        int x = 0;
        FILE *f = tmpfile();
        fprintf(f, "1a\n");
        rewind(f);
        input_file = f;
        int assigned = my_scanf("%x", &x);
        input_file = NULL; fclose(f);
        assert(assigned == 1 && x == 26);
    }

    {
        int x = 0;
        FILE *f = tmpfile();
        fprintf(f, "1010\n");
        rewind(f);
        input_file = f;
        int assigned = my_scanf("%b", &x);
        input_file = NULL; fclose(f);
        assert(assigned == 1 && x == 10);
    }

    {
        unsigned u = 0;
        FILE *f = tmpfile();
        fprintf(f, "1234\n");
        rewind(f);
        input_file = f;
        int assigned = my_scanf("%u", &u);
        input_file = NULL; fclose(f);
        assert(assigned == 1 && u == 1234);
    }

    {
        float fval = 0;
        FILE *f = tmpfile();
        fprintf(f, "-12.34\n");
        rewind(f);
        input_file = f;
        int assigned = my_scanf("%f", &fval);
        input_file = NULL; fclose(f);
        assert(assigned == 1 && fval < -12.33f && fval > -12.35f);
    }

    {
        char s[20];
        FILE *f = tmpfile();
        fprintf(f, "hello\n");
        rewind(f);
        input_file = f;
        int assigned = my_scanf("%s", s);
        input_file = NULL; fclose(f);
        assert(assigned == 1 && strcmp(s, "hello") == 0);
    }

    {
        char c;
        FILE *f = tmpfile();
        fprintf(f, "K\n");
        rewind(f);
        input_file = f;
        int assigned = my_scanf("%c", &c);
        input_file = NULL; fclose(f);
        assert(assigned == 1 && c == 'K');
    }

    {
        char q[50];
        FILE *f = tmpfile();
        fprintf(f, "\"first quote\"\n");
        rewind(f);
        input_file = f;
        int assigned = my_scanf("%q", q);
        input_file = NULL; fclose(f);
        assert(assigned == 1 && strcmp(q, "first quote") == 0);
    }

    {
        int x;
        FILE *f = tmpfile();
        fprintf(f, "   -99  ");
        rewind(f);
        input_file = f;
        int assigned = my_scanf("%d", &x);
        input_file = NULL; fclose(f);
        assert(assigned == 1 && x == -99);
    }

    {
        char s[5];
        FILE *f = tmpfile();
        fprintf(f, "HelloWorld\n");
        rewind(f);
        input_file = f;
        int assigned = my_scanf("%4s", s);
        input_file = NULL; fclose(f);
        assert(assigned == 1 && strcmp(s, "Hell") == 0);
    }

    {
        char tmp[20];
        rand_string(tmp, 10);
        FILE *f = tmpfile();
        fprintf(f, "%s\n", tmp);
        rewind(f);
        input_file = f;
        wchar_t r[20] = {0};
        int assigned = my_scanf("%ls", r);
        input_file = NULL; fclose(f);
        assert(assigned == 1);
        for (int i = 0; i < 10; i++) {
            assert(r[i] == (wchar_t)tmp[i]);
        }
    }

    {
        char tmp[10];
        rand_string(tmp, 5);
        FILE *f = tmpfile();
        fprintf(f, "%s\n", tmp);
        rewind(f);
        input_file = f;
        int width = 3;
        wchar_t r2[10] = {0};
        char fmt[10];
        sprintf(fmt, "%%%dls", width);
        int assigned = my_scanf(fmt, r2);
        input_file = NULL; fclose(f);
        assert(assigned == 1);
        for (int i = 0; i < width; i++) {
            assert(r2[i] == (wchar_t)tmp[i]);
        }
    }
}

int main() {
    run_tests();
    printf("all tests passed!\n");
    return 0;
}
