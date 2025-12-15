#include "parser.h"
#include <stdio.h>
#include "codegen.h"

void gen_var_decl(ASTNode *node, const char *file) {
	FILE *asmarch = fopen(file, "a");  // "a" para append
	if (!asmarch) {
		printf("Erro ao abrir arquivo: %s\n", file);
		return;
	}

	if (node->var_type == TOKEN_INT) {
		fprintf(asmarch, "%s:\n", node->name);
		fprintf(asmarch, "    .word %d\n", node->int_value);
	}

	if (node->var_type == TOKEN_STRING_KW) {
		fprintf(asmarch, "%s:\n", node->name);
		fprintf(asmarch, "    .asciz \"%s\"\n", node->str_value);
	}
	fclose(asmarch);
}
void gen_start(const char *file) {
	FILE *asmarch = fopen(file, "a");
	if (!asmarch) {
		printf("Erro ao abrir arquivo: %s\n", file);
		return;
	}
	fprintf(asmarch, ".section .bss\n");
	fprintf(asmarch, ".align 4\n");
	fprintf(asmarch, "stack_space:\n");
	fprintf(asmarch, "    .skip 0x1000\n");
	fprintf(asmarch, ".section .text\n");
	fprintf(asmarch, ".global _start\n");
        fprintf(asmarch, "_start:\n");
        fprintf(asmarch, "    adrp x0, stack_space\n");
        fprintf(asmarch, "    add x0, x0, :lo12:stack_space\n");
	fprintf(asmarch, "    add x0, x0, #0x1000\n");
        fprintf(asmarch, "    mov sp, x0\n");
        fprintf(asmarch, "    bl init_globals\n");
	fprintf(asmarch, "    bl cx_program\n");
	fprintf(asmarch, "hang:\n");
	fprintf(asmarch, "    b hang\n");
	fprintf(asmarch, "init_globals:\n");
	fprintf(asmarch, "    ret\n");
	fprintf(asmarch, "cx_program:\n");
	fprintf(asmarch, "    ret");
	fclose(asmarch);
}

