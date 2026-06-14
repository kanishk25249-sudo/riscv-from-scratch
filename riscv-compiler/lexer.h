#ifndef LEXER_H
#define LEXER_H

#define MAX_TOKEN_LEN 64

typedef enum {
    TOKEN_NUMBER,
    TOKEN_IDENT,

    TOKEN_INT,
    TOKEN_RETURN,
    TOKEN_IF, 
    TOKEN_ELSE,
    TOKEN_WHILE,

    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_ASSIGN,
    TOKEN_EQ,
    TOKEN_NEQ,
    TOKEN_LT,
    TOKEN_GT,
    TOKEN_LEQ,
    TOKEN_GEQ,

    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_SEMICOLON,
    TOKEN_COMMA,

    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    char value[MAX_TOKEN_LEN];
    int numval;
} Token;

typedef struct {
    char* src;
    int pos;
    int len;
} Lexer;

void lexer_init(Lexer* l, char* src);
Token next_token(Lexer* l);

#endif