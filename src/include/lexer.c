#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* getTokenName(int type) {
    switch (type) {
        case TOKEN_ADD:
            return "ADD";
        case TOKEN_DIV:
            return "DIV";
        case TOKEN_MUL:
            return "MUL";
        case TOKEN_SUB:
            return "SUB";
        case TOKEN_EQUAL:
            return "EQUAL";
        case TOKEN_ASSIGN:
            return "ASSIGN";
        case TOKEN_MOD:
            return "MOD";
        case TOKEN_LESS_EQUAL:
            return "LESS_EQUAL";
        case TOKEN_LESS:
            return "LESS";
        case TOKEN_GREATER_EQUAL:
            return "GREATER_EQUAL";
        case TOKEN_GREATER:
            return "GREATER";
        case TOKEN_REAL:
            return "REAL";
        case TOKEN_INT:
            return "INT";
        case TOKEN_STRING:
            return "STRING";
        case TOKEN_CHAR:
            return "CHAR";
        case TOKEN_KEYWORD:
            return "KEYWORD";
        case TOKEN_IDENTIFIER:
            return "IDENTIFIER";
        case TOKEN_ADDRESS_OF:
            return "ADDRESS_OF";
        case TOKEN_QUOTE:
            return "QUOTE";
        case TOKEN_SQUOT:
            return "SQUOT";
        case TOKEN_EOF:
            return "EOF";
        case TOKEN_LPAREN:
            return "LPAREN";
        case TOKEN_RPAREN:
            return "RPAREN";
        case TOKEN_LBRACKET:
            return "LBRACKET";
        case TOKEN_RBRACKET:
            return "RBRACKET";
        case TOKEN_LBRACE:
            return "LBRACE";
        case TOKEN_RBRACE:
            return "RBRACE";
        case TOKEN_COLON:
            return "COLON";
        case TOKEN_SEMICOLON:
            return "SEMICOLON";
        case TOKEN_COMMA:
            return "COMMA";
        default:
            return "UNKNOWN";
    }
}

void handleError(Token* token) {
    printf("invalid character '%s' in input at %d:%d\n", token->value, token->pos.line, token->pos.column);
}

char peekNextChar(FILE* fp) {
    char nextChar;
    int currentPosition = ftell(fp);
    nextChar = fgetc(fp);
    fseek(fp, currentPosition, SEEK_SET);
    return nextChar;
}
char readNextChar(FILE* fp, Position* pos) {
    char nextChar;
    nextChar = fgetc(fp);
    if (nextChar == '\n') {
        pos->line++;
        pos->column = 1;
    } else {
        pos->column++;
    }
    return nextChar;
}

int isKeyword(const char* word) {
    for (int i = 0; i < numKeywords; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

Token* initToken(int type, char* value, Position pos) {
    Token* token = malloc(sizeof(Token));
    token->type = type;
    token->value = value;
    token->pos = pos;
    return token;
}
void printToken(Token* token) {
    printf("Token: %d, Value: %s, Line: %d, Column: %d\n", token->type, token->value, token->pos.line, token->pos.column);
}

void writeTokenToFile(Token* token, FILE* file, FILE* sym) {
    fprintf(file, "<%d, %s>\n", token->type, token->value);
    if (token->type >= 11 && token->type <= 16) {
        fprintf(sym, "%s %s\n", getTokenName(token->type), token->value);
    }
}

void Tokenizer(FILE* input_fp, FILE* output_fp, FILE* sym_fp) {
    Position pos;
    pos.line = 1;
    pos.column = 1;
    while (1) {
        char c = readNextChar(input_fp, &pos);
        if (c == EOF) {
            break;
        }
        if (c == '/') {
            if (peekNextChar(input_fp) == '/') {
                while (c != '\n' && c != EOF) {
                    c = readNextChar(input_fp, &pos);
                }
            } else if (peekNextChar(input_fp) == '*') {
                while (1) {
                    c = readNextChar(input_fp, &pos);
                    if (c == '*') {
                        if (peekNextChar(input_fp) == '/') {
                            readNextChar(input_fp, &pos);
                            break;
                        }
                    }
                }
            } else {
                Token* token = initToken(TOKEN_DIV, "/", pos);
                writeTokenToFile(token, output_fp, sym_fp);
            }
        } else if (c == '-') {
            Token* token = initToken(TOKEN_SUB, "-", pos);
            writeTokenToFile(token, output_fp, sym_fp);
        } else if (c == '+') {
            Token* token = initToken(TOKEN_ADD, "+", pos);
            writeTokenToFile(token, output_fp, sym_fp);
        } else if (c == '*') {
            Token* token = initToken(TOKEN_MUL, "*", pos);
            writeTokenToFile(token, output_fp, sym_fp);
        } else if (c == '(') {
            Token* token = initToken(TOKEN_LPAREN, "(", pos);
            writeTokenToFile(token, output_fp, sym_fp);
        } else if (c == ')') {
            Token* token = initToken(TOKEN_RPAREN, ")", pos);
            writeTokenToFile(token, output_fp, sym_fp);
        } else if (c == '[') {
            Token* token = initToken(TOKEN_LBRACKET, "[", pos);
            writeTokenToFile(token, output_fp, sym_fp);
        } else if (c == ']') {
            Token* token = initToken(TOKEN_RBRACKET, "]", pos);
            writeTokenToFile(token, output_fp, sym_fp);
        } else if (c == '{') {
            Token* token = initToken(TOKEN_LBRACE, "{", pos);
            writeTokenToFile(token, output_fp, sym_fp);
        } else if (c == '}') {
            Token* token = initToken(TOKEN_RBRACE, "}", pos);
            writeTokenToFile(token, output_fp, sym_fp);
        } else if (c == ';') {
            Token* token = initToken(TOKEN_SEMICOLON, ";", pos);
            writeTokenToFile(token, output_fp, sym_fp);
        } else if (c == ':') {
            Token* token = initToken(TOKEN_COLON, ":", pos);
            writeTokenToFile(token, output_fp, sym_fp);
        } else if (c == ',') {
            Token* token = initToken(TOKEN_COMMA, ",", pos);
            writeTokenToFile(token, output_fp, sym_fp);
        } else if (c == '%') {
            Token* token = initToken(TOKEN_MOD, "%%", pos);
            writeTokenToFile(token, output_fp, sym_fp);
        } else if (c == '=') {
            if (peekNextChar(input_fp) == '=') {
                Token* token = initToken(TOKEN_EQUAL, "==", pos);
                writeTokenToFile(token, output_fp, sym_fp);
            } else {
                Token* token = initToken(TOKEN_ASSIGN, "=", pos);
                writeTokenToFile(token, output_fp, sym_fp);
            }
        } else if (isdigit(c)) {
            char* value = malloc(sizeof(char) * 100);
            value[0] = c;
            int i = 1;
            int is_real = 0;
            while (1) {
                c = peekNextChar(input_fp);
                if (isdigit(c)) {
                    c = readNextChar(input_fp, &pos);
                    value[i] = c;
                    i++;
                } else if (c == '.' && !is_real) {
                    c = readNextChar(input_fp, &pos);
                    is_real = 1;
                    value[i] = c;
                    i++;
                } else {
                    break;
                }
            }
            if (is_real) {
                Token* token = initToken(TOKEN_REAL, value, pos);
                writeTokenToFile(token, output_fp, sym_fp);
            } else {
                Token* token = initToken(TOKEN_INT, value, pos);
                writeTokenToFile(token, output_fp, sym_fp);
            }
        } else if (isalpha(c) || c == '_') {
            char* value = malloc(sizeof(char) * 100);
            int i = 1;
            value[0] = c;
            if (peekNextChar(input_fp) == '_' || isalnum(peekNextChar(input_fp))) {
                do {
                    value[i] = readNextChar(input_fp, &pos);
                    i++;
                    if (peekNextChar(input_fp) != '_' && !isalnum(peekNextChar(input_fp))) {
                        break;
                    }
                } while (1);
            }
            if (isKeyword(value)) {
                Token* token = initToken(TOKEN_KEYWORD, value, pos);
                writeTokenToFile(token, output_fp, sym_fp);
            } else {
                Token* token = initToken(TOKEN_IDENTIFIER, value, pos);
                writeTokenToFile(token, output_fp, sym_fp);
            }
        } else if (c == '<') {
            c = peekNextChar(input_fp);
            if (c == '=') {
                Token* token = initToken(TOKEN_LESS_EQUAL, "<=", pos);
                writeTokenToFile(token, output_fp, sym_fp);
            } else {
                Token* token = initToken(TOKEN_LESS, "<", pos);
                writeTokenToFile(token, output_fp, sym_fp);
            }
        } else if (c == '>') {
            c = peekNextChar(input_fp);
            if (c == '=') {
                Token* token = initToken(TOKEN_GREATER_EQUAL, ">=", pos);
                writeTokenToFile(token, output_fp, sym_fp);
            } else {
                Token* token = initToken(TOKEN_GREATER, ">", pos);
                writeTokenToFile(token, output_fp, sym_fp);
            }
        } else if (c == '"') {
            Token* token = initToken(TOKEN_QUOTE, "\"", pos);
            writeTokenToFile(token, output_fp, sym_fp);
            char* value = malloc(sizeof(char) * 100);
            int i = 0;
            while (1) {
                c = readNextChar(input_fp, &pos);
                if (c == '"') {
                    break;
                } else {
                    value[i] = c;
                    i++;
                }
            }
            token = initToken(TOKEN_STRING, value, pos);
            writeTokenToFile(token, output_fp, sym_fp);
            token = initToken(TOKEN_QUOTE, "\"", pos);
            writeTokenToFile(token, output_fp, sym_fp);
        } else if (c == '\'') {
            Token* token = initToken(TOKEN_SQUOT, "\'", pos);
            writeTokenToFile(token, output_fp, sym_fp);
            char* value = malloc(sizeof(char) * 2);
            value[0] = readNextChar(input_fp, &pos);
            value[1] = '\0';
            token = initToken(TOKEN_CHAR, value, pos);
            writeTokenToFile(token, output_fp, sym_fp);
            readNextChar(input_fp, &pos);
            token = initToken(TOKEN_SQUOT, "\'", pos);
            writeTokenToFile(token, output_fp, sym_fp);
        } else if (c == EOF) {
            Token* token = initToken(TOKEN_EOF, "EOF", pos);
            writeTokenToFile(token, output_fp, sym_fp);
        } else if (c == ' ' || c == '\n' || c == '\t') {
            continue;
        } else if (c == '&') {
            Token* token = initToken(TOKEN_ADDRESS_OF, "&", pos);
            writeTokenToFile(token, output_fp, sym_fp);
        } 
        else {
            char* value = malloc(sizeof(char) * 2);
            value[0] = c;
            value[1] = '\0';
            Token* token = initToken(TOKEN_UNKNOWN, value, pos);
            writeTokenToFile(token, output_fp, sym_fp);
            handleError(token);
        }
    }
}

