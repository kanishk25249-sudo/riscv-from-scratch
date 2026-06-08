#include "parser.h"
#include <stdlib.h>
#include <string.h>

void parser_init(Parser* p, Lexer* lexer) {
    p->lexer = lexer;
    p->current_token = next_token(lexer);
}

ASTNode* parse_expr(Parser* p) {
    ASTNode* left = NULL;
    
    if (p->current_token.type == TOKEN_NUMBER) {
        left = malloc(sizeof(ASTNode));
        left->type = EXPR_NUMBER;
        left->data.number = p->current_token.numval;
        p->current_token = next_token(p->lexer);
    }
    else if (p->current_token.type == TOKEN_IDENT) {
        left = malloc(sizeof(ASTNode));
        left->type = EXPR_VARIABLE;
        left->data.varname = malloc(strlen(p->current_token.value) + 1);
        strcpy(left->data.varname, p->current_token.value);
        p->current_token = next_token(p->lexer);
    }
    
    if (left == NULL) return NULL;

    if (p->current_token.type == TOKEN_PLUS ||
        p->current_token.type == TOKEN_MINUS ||
        p->current_token.type == TOKEN_STAR ||
        p->current_token.type == TOKEN_SLASH) {
        
        TokenType op = p->current_token.type;
        p->current_token = next_token(p->lexer);

        ASTNode* right = parse_expr(p);
        
        ASTNode* node = malloc(sizeof(ASTNode));
        node->type = EXPR_BINARY;
        node->data.binary.left = left;
        node->data.binary.op = op;
        node->data.binary.right = right;
        
        return node;
    }
    return left;
}

Stmt* parse_stmt(Parser* p) {
    if (p->current_token.type == TOKEN_INT) {
        p->current_token = next_token(p->lexer);
        if (p->current_token.type != TOKEN_IDENT) return NULL;
        char* name = malloc(strlen(p->current_token.value) + 1);
        strcpy(name, p->current_token.value);
        p->current_token = next_token(p->lexer);
        if (p->current_token.type != TOKEN_ASSIGN) return NULL;
        p->current_token = next_token(p->lexer);
        ASTNode* init = parse_expr(p);
        if (p->current_token.type != TOKEN_SEMICOLON) return NULL;
        p->current_token = next_token(p->lexer);

        Stmt* stmt = malloc(sizeof(Stmt));
        stmt->type = STMT_VAR_DECL;
        stmt->data.var_decl.name = name;
        stmt->data.var_decl.init = init;
        return stmt;
    }

    if (p->current_token.type == TOKEN_IDENT) {
        char* name = malloc(strlen(p->current_token.value) + 1);
        strcpy(name, p->current_token.value);
        p->current_token = next_token(p->lexer);
        if (p->current_token.type != TOKEN_ASSIGN) return NULL;
        p->current_token = next_token(p->lexer);
        ASTNode* value = parse_expr(p);
        if (p->current_token.type != TOKEN_SEMICOLON) return NULL;
        p->current_token = next_token(p->lexer);
        Stmt* stmt = malloc(sizeof(Stmt));
        stmt->type = STMT_ASSIGNMENT;
        stmt->data.assignment.name = name;
        stmt->data.assignment.value = value;
        return stmt;
    }

    if (p->current_token.type == TOKEN_RETURN) {
        p->current_token = next_token(p->lexer);
        
        ASTNode* value = parse_expr(p);
        
        if (p->current_token.type != TOKEN_SEMICOLON) return NULL;
        p->current_token = next_token(p->lexer);
        
        Stmt* stmt = malloc(sizeof(Stmt));
        stmt->type = STMT_RETURN;
        stmt->data.return_stmt.value = value;
        
        return stmt;
    }

    if (p->current_token.type == TOKEN_IF) {
        p->current_token = next_token(p->lexer);
        if (p->current_token.type != TOKEN_LPAREN) return NULL;
        p->current_token = next_token(p->lexer);
        ASTNode* condition = parse_condition(p);

        if (p->current_token.type != TOKEN_RPAREN) return NULL;
        p->current_token = next_token(p->lexer);
        
        Stmt* then_stmt = parse_block(p);

        Stmt* else_stmt = NULL;
        if (p->current_token.type == TOKEN_ELSE) {
            p->current_token = next_token(p->lexer);
            else_stmt = parse_block(p);
        }
        
        Stmt* stmt = malloc(sizeof(Stmt));
        stmt->type = STMT_IF;
        stmt->data.if_stmt.condition = condition;
        stmt->data.if_stmt.then_stmt = then_stmt;
        stmt->data.if_stmt.else_stmt = else_stmt;
        
        return stmt;
    }

    if (p->current_token.type == TOKEN_WHILE) {
        p->current_token = next_token(p->lexer);
        
        if (p->current_token.type != TOKEN_LPAREN) return NULL;
        p->current_token = next_token(p->lexer);
        
        ASTNode* condition = parse_condition(p);
        
        if (p->current_token.type != TOKEN_RPAREN) return NULL;
        p->current_token = next_token(p->lexer);
        
        Stmt* body = parse_block(p);
        
        Stmt* stmt = malloc(sizeof(Stmt));
        stmt->type = STMT_WHILE;
        stmt->data.while_stmt.condition = condition;
        stmt->data.while_stmt.body = body;
        
        return stmt;
    }
    
    return NULL;
}

ASTNode* parse_condition(Parser* p) {
    ASTNode* left = parse_expr(p);
    if (p->current_token.type == TOKEN_EQ ||
        p->current_token.type == TOKEN_NEQ ||
        p->current_token.type == TOKEN_LT ||
        p->current_token.type == TOKEN_LEQ ||
        p->current_token.type == TOKEN_GT ||
        p->current_token.type == TOKEN_GEQ) {
        
            TokenType op = p->current_token.type;
            p->current_token = next_token(p->lexer);
            ASTNode* right = parse_expr(p);
            ASTNode* node = malloc(sizeof(ASTNode));
            node->type = EXPR_BINARY;
            node->data.binary.left = left;
            node->data.binary.op = op;
            node->data.binary.right = right;
            return node;
    }
    return left;
}

Stmt* parse_block(Parser* p) {
    if (p->current_token.type != TOKEN_LBRACE) return NULL;
    p->current_token = next_token(p->lexer);
    Stmt* body = parse_stmt(p);
    if (p->current_token.type != TOKEN_RBRACE) return NULL;
    p->current_token = next_token(p->lexer);
    return body;
}
