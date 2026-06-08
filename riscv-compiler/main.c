#include "lexer.h"
#include "parser.h"
#include "codegen.h"
#include <stdio.h>

int main() {
    char code[] = 
        "int x = 10; "
        "int y = 5; "
        "int z = x + y; "
        "if (z > 10) { "
        "    z = z - 3; "
        "} else { "
        "    z = z + 1; "
        "} "
        "while (x > 0) { "
        "    x = x - 1; "
        "} "
        "return z;";
    
    Lexer lexer;
    lexer_init(&lexer, code);
    
    Parser parser;
    parser_init(&parser, &lexer);
    
    Codegen cg;
    codegen_init(&cg);
    
    Stmt* stmt = parse_stmt(&parser);
    while (stmt != NULL && parser.current_token.type != TOKEN_EOF) {
        codegen_stmt(&cg, stmt);
        stmt = parse_stmt(&parser);
    }
    
    printf("%s\n", codegen_get_code(&cg));
    
    return 0;
}