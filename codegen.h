#ifndef CODEGEN_H
#define CODEGEN_H

#include "parser.h"

void gen_var_decl(ASTNode *node, const char *file);
void gen_start(const char *file);

#endif
