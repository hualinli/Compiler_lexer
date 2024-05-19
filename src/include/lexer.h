#ifndef LEXER__H
#define LEXER__H
#include <stdio.h>
typedef struct {
    int line;
    int column;
} Position;
typedef struct Token {
    int type;
    char* value;
    Position pos;
} Token;

enum TokenType {
    TOKEN_ADD, // +
    TOKEN_DIV, // /
    TOKEN_MUL, // *
    TOKEN_SUB, // -
    TOKEN_EQUAL, // ==
    TOKEN_ASSIGN, // =
    TOKEN_MOD, // %
    TOKEN_LESS_EQUAL, // <=
    TOKEN_LESS, // <
    TOKEN_GREATER_EQUAL, // >=
    TOKEN_GREATER, // >

    TOKEN_REAL,
    TOKEN_INT,
    TOKEN_STRING,
    TOKEN_CHAR,

    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,

    TOKEN_ADDRESS_OF, //    &
    TOKEN_QUOTE, // "
    TOKEN_SQUOT, // '
    TOKEN_EOF, // EOF
    TOKEN_LPAREN, // (
    TOKEN_RPAREN, // )
    TOKEN_LBRACKET, // [
    TOKEN_RBRACKET, // ]
    TOKEN_LBRACE, // {
    TOKEN_RBRACE, // }
    TOKEN_COLON, // :
    TOKEN_SEMICOLON, // ;
    TOKEN_COMMA, // ,
    TOKEN_UNKNOWN,
};
const char* keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if", "int",
    "long", "register", "return", "short", "signed", "static", "struct",
    "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};

const int numKeywords = sizeof(keywords) / sizeof(keywords[0]);

void printToken(Token* token);
void handleError(Token* token);
char peekNextChar(FILE* fp);
char readNextChar(FILE* fp, Position* pos);
int isKeyword(const char* value);
Token* initToken(int type, char* value, Position pos);
void writeTokenToFile(Token* token, FILE* file, FILE* sym);
void Tokenizer(FILE* input_fp, FILE* output_fp, FILE* sym_fp);
const char* getTokenName(int type);
#endif