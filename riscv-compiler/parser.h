#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef enum {
    EXPR_NUMBER,
    EXPR_VARIABLE,
    EXPR_BINARY,
} ExprType;

typedef struct ASTNode ASTNode;

struct ASTNode {
    ExprType type;
    union {
        int number;
        char* varname;
        struct {
            ASTNode* left;
            TokenType op;
            ASTNode* right;
        } binary;
    } data;
};

typedef enum {
    STMT_VAR_DECL,
    STMT_ASSIGNMENT,
    STMT_IF,
    STMT_WHILE,
    STMT_RETURN,
} StmtType;

typedef struct Stmt Stmt;

struct Stmt {
    StmtType type;
    union {
        struct {
            char* name;
            ASTNode* init;
        } var_decl;
        struct {
            char* name;
            ASTNode* value;
        } assignment;
        struct {
            ASTNode* condition;
            Stmt* then_stmt;
            Stmt* else_stmt;
        } if_stmt;
        struct {
            ASTNode* condition;
            Stmt* body;
        } while_stmt;
        struct {
            ASTNode* value;
        } return_stmt;
    } data;
};

typedef struct {
    Lexer* lexer;
    Token current_token;
} Parser;

void parser_init(Parser* p, Lexer* lexer);
ASTNode* parse_expr(Parser* p);
Stmt* parse_stmt(Parser* p);
ASTNode* parse_condition(Parser* p);
Stmt* parse_block(Parser* p);

#endif