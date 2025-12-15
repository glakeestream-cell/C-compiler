#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include "codegen.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo_fonte>\n", argv[0]);
        return 1;
    }

    // Abrir o arquivo fonte
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "Erro: não foi possível abrir o arquivo '%s'\n", argv[1]);
        return 1;
    }

    // Descobrir o tamanho do arquivo
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Alocar memória para o conteúdo
    char *src = (char *)malloc(file_size + 1);
    if (!src) {
        fprintf(stderr, "Erro: falha ao alocar memória\n");
        fclose(file);
        return 1;
    }

    // Ler o arquivo
    size_t bytes_read = fread(src, 1, file_size, file);
    src[bytes_read] = '\0';
    fclose(file);

    // Inicializar lexer e parser
    Lexer lexer;
    Parser parser;

    lexer_init(&lexer, src);
    parser_init(&parser, &lexer);

    // Criar arquivo assembly
    FILE *asmfile = fopen("teste.s", "w");
    if (!asmfile) {
        fprintf(stderr, "Erro ao criar arquivo assembly\n");
        free(src);
        return 1;
    }
    fprintf(asmfile, ".section .data\n");
    fclose(asmfile);

    // Processar todas as declarações até EOF
    int decl_count = 0;
    while (parser.current.type != TOKEN_EOF) {
        ASTNode node = parse_var_decl(&parser);
        gen_var_decl(&node, "teste.s");
        
        printf("Declaração %d OK!\n", ++decl_count);
        printf("  Tipo: %d\n", node.var_type);
        printf("  Nome: %s\n", node.name);
        if (node.var_type == TOKEN_INT) {
            printf("  Valor int: %d\n", node.int_value);
        } else if (node.var_type == TOKEN_STRING_KW) {
            printf("  Valor string: %s\n", node.str_value);
        }
        printf("\n");
    }
    gen_start("teste.s");
    printf("Total de declarações processadas: %d\n", decl_count);

    // Liberar memória
    free(src);

    return 0;
}
