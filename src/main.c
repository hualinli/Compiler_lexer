#include "include/lexer.c"
#include <stdio.h>


int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Error opening file %s\n", argv[1]);
        return 1;
    }
    FILE* fp2 = fopen("output.txt", "w");
    if (fp2 == NULL) {
        printf("Error opening file output.txt\n");
        return 1;
    }
    FILE* fp3 = fopen("symbolTable.txt", "w");
    if (fp3 == NULL) {
        printf("Error opening file symbolTable.txt\n");
        return 1;
    }
    Tokenizer(fp, fp2, fp3);
    fclose(fp);
    return 0;
}