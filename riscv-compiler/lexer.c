#include "lexer.h"
#include <string.h>

void lexer_init(Lexer* l, char* src) {
    l->src = src;
    l->pos = 0;
    l->len = strlen(src);
}

static char current(Lexer* l) {
    return l->src[l->pos];
}

static char advance(Lexer* l) {
    return l->src[l->pos++];
}

static void skip_whitespace(Lexer* l) {
    while (l->pos < l->len &&
           (current(l) == ' '  ||
            current(l) == '\n' ||
            current(l) == '\t' ||
            current(l) == '\r')) {
        l->pos++;
    }
}

static Token make_token(TokenType type, const char* value, int numval) {
    Token t;
    t.type = type;
    t.numval = numval;
    int i = 0;
    while (value[i] && i < MAX_TOKEN_LEN - 1) {
        t.value[i] = value[i];
        i++;
    }
    t.value[i] = '\0';
    return t;
}

static int is_digit(char c) {
    return c >= '0' && c <= '9';
}

static int is_alpha(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
}

static Token read_number(Lexer* l) {
    char buf[MAX_TOKEN_LEN];
    int i = 0;
    while (l->pos < l->len && is_digit(current(l))) {
        char ch = advance(l);
        buf[i] = ch;
        i = i + 1;
    }
    buf[i] = '\0';
    int val = 0;
    for (int j = 0; j < i; j++) {
        val = val * 10 + (buf[j] - '0');
    }
    return make_token(TOKEN_NUMBER, buf, val);
}

static Token read_ident(Lexer* l) {
    char buf[MAX_TOKEN_LEN];
    int i = 0;
    while (l->pos < l->len && (is_alpha(current(l)) || is_digit(current(l)))) {
        char ch = advance(l);
        buf[i] = ch;
        i = i + 1;
    }
    buf[i] = '\0';
    if (buf[0]=='i' && buf[1]=='n' && buf[2]=='t' && buf[3]=='\0')
        return make_token(TOKEN_INT, buf, 0);
    if (buf[0]=='i' && buf[1]=='f' && buf[2]=='\0')
        return make_token(TOKEN_IF, buf, 0);
    if (buf[0]=='e' && buf[1]=='l' && buf[2]=='s' && buf[3]=='e' && buf[4]=='\0')
        return make_token(TOKEN_ELSE, buf, 0);
    if (buf[0]=='w' && buf[1]=='h' && buf[2]=='i' && buf[3]=='l' && buf[4]=='e' && buf[5]=='\0')
        return make_token(TOKEN_WHILE, buf, 0);
    if (buf[0]=='r' && buf[1]=='e' && buf[2]=='t' && buf[3]=='u' && buf[4]=='r' && buf[5]=='n' && buf[6]=='\0')
        return make_token(TOKEN_RETURN, buf, 0);
    return make_token(TOKEN_IDENT, buf, 0);
}

Token next_token(Lexer* l) {
    skip_whitespace(l);
    if (l->pos >= l->len)
        return make_token(TOKEN_EOF, "", 0);
    char c = current(l);
    if (is_digit(c)) 
        return read_number(l);
    if (is_alpha(c)) 
        return read_ident(l);
    advance(l);
    switch (c) {
        case '+': return make_token(TOKEN_PLUS,      "+", 0);
        case '-': return make_token(TOKEN_MINUS,     "-", 0);
        case '*': return make_token(TOKEN_STAR,      "*", 0);
        case '/': return make_token(TOKEN_SLASH,     "/", 0);
        case '(': return make_token(TOKEN_LPAREN,    "(", 0);
        case ')': return make_token(TOKEN_RPAREN,    ")", 0);
        case '{': return make_token(TOKEN_LBRACE,    "{", 0);
        case '}': return make_token(TOKEN_RBRACE,    "}", 0);
        case ';': return make_token(TOKEN_SEMICOLON, ";", 0);
        case ',': return make_token(TOKEN_COMMA,     ",", 0);
        case '=':
            if (current(l) == '=') {
                advance(l);
                return make_token(TOKEN_EQ, "==", 0);
            }
            return make_token(TOKEN_ASSIGN, "=", 0);
        case '!':
            if (current(l) == '=') {
                advance(l);
                return make_token(TOKEN_NEQ, "!=", 0);
            }
            break;
        case '<':
            if (current(l) == '=') {
                advance(l);
                return make_token(TOKEN_LEQ, "<=", 0);
            }
            return make_token(TOKEN_LT, "<", 0);
        case '>':
            if (current(l) == '=') {
                advance(l);
                return make_token(TOKEN_GEQ, ">=", 0);
            }
            return make_token(TOKEN_GT, ">", 0);
    }
    return make_token(TOKEN_EOF, "", 0);
}