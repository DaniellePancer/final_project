#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

/* Include the implementation directly */
#include "my_scanf.c"

void run_tests() {
    // ----- Integer test -----
    {
        int result = 0;
        FILE *input_stream = tmpfile();
        fprintf(input_stream, "42\n");
        rewind(input_stream);
        stdin = input_stream;

        int assigned = my_scanf("%d", &result);
        assert(assigned == 1);
        assert(result == 42);
        fclose(input_stream);
    }

    // ----- Hex test -----
    {
        int result = 0;
        FILE *input_stream = tmpfile();
        fprintf(input_stream, "1a\n");
        rewind(input_stream);
        stdin = input_stream;

        int assigned = my_scanf("%x", &result);
        assert(assigned == 1);
        assert(result == 26);
        fclose(input_stream);
    }

    // ----- Binary test -----
    {
        int result = 0;
        FILE *input_stream = tmpfile();
        fprintf(input_stream, "1010\n");
        rewind(input_stream);
        stdin = input_stream;

        int assigned = my_scanf("%b", &result);
        assert(assigned == 1);
        assert(result == 10);
        fclose(input_stream);
    }

    // ----- Unsigned test -----
    {
        unsigned u = 0;
        FILE *input_stream = tmpfile();
        fprintf(input_stream, "1234\n");
        rewind(input_stream);
        stdin = input_stream;

        int assigned = my_scanf("%u", &u);
        assert(assigned == 1);
        assert(u == 1234);
        fclose(input_stream);
    }

    // ----- Float test -----
    {
        float f = 0.0f;
        FILE *input_stream = tmpfile();
        fprintf(input_stream, "-12.34\n");
        rewind(input_stream);
        stdin = input_stream;

        int assigned = my_scanf("%f", &f);
        assert(assigned == 1);
        assert(f < -12.33f && f > -12.35f);  // allow tiny float error
        fclose(input_stream);
    }

    // ----- String test -----
    {
        char s[20];
        FILE *input_stream = tmpfile();
        fprintf(input_stream, "hello\n");
        rewind(input_stream);
        stdin = input_stream;

        int assigned = my_scanf("%s", s);
        assert(assigned == 1);
        assert(strcmp(s, "hello") == 0);
        fclose(input_stream);
    }

    // ----- Character test -----
    {
        char c;
        FILE *input_stream = tmpfile();
        fprintf(input_stream, "K\n");
        rewind(input_stream);
        stdin = input_stream;

        int assigned = my_scanf("%c", &c);
        assert(assigned == 1);
        assert(c == 'K');
        fclose(input_stream);
    }

    // ----- Quoted string test -----
    {
        char q[50];
        FILE *input_stream = tmpfile();
        fprintf(input_stream, "\"first quote\"\n");
        rewind(input_stream);
        stdin = input_stream;

        int assigned = my_scanf("%q", q);
        assert(assigned == 1);
        assert(strcmp(q, "first quote") == 0);
        fclose(input_stream);
    }

    // ----- Edge cases -----
    {
        int result;
        FILE *input_stream = tmpfile();
        fprintf(input_stream, "   -99  ");
        rewind(input_stream);
        stdin = input_stream;

        int assigned = my_scanf("%d", &result);
        assert(assigned == 1);
        assert(result == -99);
        fclose(input_stream);
    }

    // ----- Width-limited string -----
    {
        char s[5];
        FILE *input_stream = tmpfile();
        fprintf(input_stream, "HelloWorld\n");
        rewind(input_stream);
        stdin = input_stream;

        int assigned = my_scanf("%4s", s);
        assert(assigned == 1);
        assert(strcmp(s, "Hell") == 0);  // only 4 chars
        fclose(input_stream);
    }
}

int main() {
    run_tests();
    printf("All tests passed!\n");
    return 0;
}
