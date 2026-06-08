#include "codegen.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

void codegen_init(Codegen* cg) {
    cg->code_capacity = 10000;
    cg->code = malloc(cg->code_capacity);
    cg->code_pos = 0;
    cg->var_count = 0;
    cg->next_offset = -4;
    cg->label_count = 0;
}

static void append_code(Codegen* cg, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int written = vsnprintf(cg->code + cg->code_pos, 
                            cg->code_capacity - cg->code_pos, 
                            fmt, args);
    va_end(args);
    cg->code_pos += written;
}

static int var_offset(Codegen* cg, const char* name) {
    for (int i = 0; i < cg->var_count; i++) {
        if (strcmp(cg->var_names[i], name) == 0) {
            return cg->var_offsets[i];
        }
    }
    return 0;
}

static int add_var(Codegen* cg, const char* name) {
    cg->var_names[cg->var_count] = malloc(strlen(name) + 1);
    strcpy(cg->var_names[cg->var_count], name);
    cg->var_offsets[cg->var_count] = cg->next_offset;
    cg->next_offset -= 4;
    cg->var_count++;
    return cg->var_offsets[cg->var_count - 1];
}

void codegen_expr(Codegen* cg, ASTNode* expr) {
    if (expr->type == EXPR_NUMBER) {
        append_code(cg, "    li x10, %d\n", expr->data.number);
    }
    else if (expr->type == EXPR_VARIABLE) {
        int offset = var_offset(cg, expr->data.varname);
        append_code(cg, "    lw x10, %d(sp)\n", offset);
    }
    else if (expr->type == EXPR_BINARY) {
        codegen_expr(cg, expr->data.binary.left);
        
        append_code(cg, "    addi sp, sp, -4\n");
        append_code(cg, "    sw x10, 0(sp)\n");
        
        codegen_expr(cg, expr->data.binary.right);
        
        append_code(cg, "    lw x11, 0(sp)\n");
        append_code(cg, "    addi sp, sp, 4\n");
        
        if (expr->data.binary.op == TOKEN_PLUS) {
            append_code(cg, "    add x10, x11, x10\n");
        }
        else if (expr->data.binary.op == TOKEN_MINUS) {
            append_code(cg, "    sub x10, x11, x10\n");
        }
        else if (expr->data.binary.op == TOKEN_STAR) {
            append_code(cg, "    mul x10, x11, x10\n");
        }
        else if (expr->data.binary.op == TOKEN_SLASH) {
            append_code(cg, "    div x10, x11, x10\n");
        }
        else if (expr->data.binary.op == TOKEN_LT) {
            append_code(cg, "    slt x10, x11, x10\n");
        }
        else if (expr->data.binary.op == TOKEN_GT) {
            append_code(cg, "    sgt x10, x11, x10\n");
        }
        else if (expr->data.binary.op == TOKEN_EQ) {
            append_code(cg, "    seq x10, x11, x10\n");
        }
    }
}

void codegen_stmt(Codegen* cg, Stmt* stmt) {
    if (stmt->type == STMT_VAR_DECL) {
        int offset = add_var(cg, stmt->data.var_decl.name);
        codegen_expr(cg, stmt->data.var_decl.init);
        append_code(cg, "    sw x10, %d(sp)\n", offset);
    }
    else if (stmt->type == STMT_ASSIGNMENT) {
        codegen_expr(cg, stmt->data.assignment.value);
        int offset = var_offset(cg, stmt->data.assignment.name);
        append_code(cg, "    sw x10, %d(sp)\n", offset);
    }
    else if (stmt->type == STMT_RETURN) {
        codegen_expr(cg, stmt->data.return_stmt.value);
        append_code(cg, "    ret\n");
    }
    else if (stmt->type == STMT_IF) {
        int else_label = cg->label_count++;
        int end_label = cg->label_count++;
        
        codegen_expr(cg, stmt->data.if_stmt.condition);
        append_code(cg, "    beq x10, x0, else_%d\n", else_label);
        
        codegen_stmt(cg, stmt->data.if_stmt.then_stmt);
        append_code(cg, "    jal x0, end_%d\n", end_label);
        
        append_code(cg, "else_%d:\n", else_label);
        if (stmt->data.if_stmt.else_stmt != NULL) {
            codegen_stmt(cg, stmt->data.if_stmt.else_stmt);
        }
        
        append_code(cg, "end_%d:\n", end_label);
    }
    else if (stmt->type == STMT_WHILE) {
        int loop_label = cg->label_count++;
        int end_label = cg->label_count++;
        
        append_code(cg, "loop_%d:\n", loop_label);
        codegen_expr(cg, stmt->data.while_stmt.condition);
        append_code(cg, "    beq x10, x0, end_%d\n", end_label);
        
        codegen_stmt(cg, stmt->data.while_stmt.body);
        append_code(cg, "    jal x0, loop_%d\n", loop_label);
        
        append_code(cg, "end_%d:\n", end_label);
    }
}

char* codegen_get_code(Codegen* cg) {
    return cg->code;
}
