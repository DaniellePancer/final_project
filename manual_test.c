#include <stdio.h>
#include <stdlib.h>
#include "my_scanf.c"

int main(void) {

    int i;
    float f;
    unsigned x;
    char s[50];
    char c;
    int is_cat;

    FILE *temp_file;

    printf("Testing %%d\n");
    temp_file = tmpfile();
    fprintf(temp_file, "123\n");
    rewind(temp_file);
    input_file = temp_file;
    my_scanf("%d", &i);
    input_file = NULL;
    fclose(temp_file);
    printf("value = %d\n\n", i);

    printf("Testing %%f\n");
    temp_file = tmpfile();
    fprintf(temp_file, "-12.5\n");
    rewind(temp_file);
    input_file = temp_file;
    my_scanf("%f", &f);
    input_file = NULL;
    fclose(temp_file);
    printf("value = %f\n\n", f);

    printf("Testing %%x\n");
    temp_file = tmpfile();
    fprintf(temp_file, "1a\n");
    rewind(temp_file);
    input_file = temp_file;
    my_scanf("%x", &x);
    input_file = NULL;
    fclose(temp_file);
    printf("value = %u\n\n", x);

    printf("Testing %%s\n");
    temp_file = tmpfile();
    fprintf(temp_file, "hello\n");
    rewind(temp_file);
    input_file = temp_file;
    my_scanf("%s", s);
    input_file = NULL;
    fclose(temp_file);
    printf("value = %s\n\n", s);

    printf("Testing %%c\n");
    temp_file = tmpfile();
    fprintf(temp_file, "Z");
    rewind(temp_file);
    input_file = temp_file;
    my_scanf("%c", &c);
    input_file = NULL;
    fclose(temp_file);
    printf("value = %c\n\n", c);

    printf("Testing %%4s\n");
    temp_file = tmpfile();
    fprintf(temp_file, "HelloWorld\n");
    rewind(temp_file);
    input_file = temp_file;
    my_scanf("%4s", s);
    input_file = NULL;
    fclose(temp_file);
    printf("value = %s\n\n", s);

    printf("Testing %%b\n");
    temp_file = tmpfile();
    fprintf(temp_file, "1011\n");
    rewind(temp_file);
    input_file = temp_file;
    my_scanf("%b", &i);
    input_file = NULL;
    fclose(temp_file);
    printf("value = %d\n\n", i);

    printf("Testing %%q\n");
    temp_file = tmpfile();
    fprintf(temp_file, "\"hello world\"\n");
    rewind(temp_file);
    input_file = temp_file;
    my_scanf("%q", s);
    input_file = NULL;
    fclose(temp_file);
    printf("value = %s\n\n", s);

    printf("Testing %%C\n");
    temp_file = tmpfile();
    fprintf(temp_file, "meow\n");
    rewind(temp_file);
    input_file = temp_file;
    my_scanf("%C", &is_cat);
    input_file = NULL;
    fclose(temp_file);
    printf("value = %d\n\n", is_cat);

    return 0;
}
