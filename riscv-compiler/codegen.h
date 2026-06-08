#ifndef CODEGEN_H
#define CODEGEN_H

#include "parser.h"

typedef struct {
    char* code;
    int code_pos;
    int code_capacity;

    char* var_names[100];
    int var_offsets[100];
    int var_count;

    int next_offset;
    int label_count;
} Codegen;

void codegen_init(Codegen* cg);
void codegen_expr(Codegen* cg, ASTNode* expr);
void codegen_stmt(Codegen* cg, Stmt* stmt);
char* codegen_get_code(Codegen* cg);

#endif