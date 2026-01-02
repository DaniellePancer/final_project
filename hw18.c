#include <stdio.h>

int main() {
    FILE *inputFile, *outputFile;
    char ch;

    inputFile = fopen("source.c", "r");
    outputFile = fopen("new", "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Unsuccessful\n");
        return 1;
    }

    while ((ch = fgetc(inputFile)) != EOF) {
        if (ch != ' ' && ch != '\t' && ch != '\n' && ch != '\r') {
            fputc(ch, outputFile);
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Successful\n");
    return 0;
}
