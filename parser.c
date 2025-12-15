#include "parser.h"
#include "lexer.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void parser_init(Parser *parser, Lexer *lexer) {
	parser->lexer = lexer;
	parser->current = lexer_next_token(lexer);
}

void parser_eat(Parser *parser, Token expected) {
    if (parser->current.type == expected) {
        parser->current = lexer_next_token(parser->lexer);
    } else {
        printf(
            "Tá errado meu mano! | isso %d | deveria ser isso: %d\n",
            expected,
            parser->current.type
        );
        exit(1);
    }
}

ASTNode parse_var_decl(Parser *parser) {
    ASTNode node;
    node.type = AST_VAR_DECL;
    node.int_value = 0;
    memset(node.str_value, 0, sizeof(node.str_value));

    // tipo da variável
    if (parser->current.type == TOKEN_INT ||
        parser->current.type == TOKEN_STRING_KW) {

        node.var_type = parser->current.type;
        parser_eat(parser, parser->current.type);

    } else {
        printf("Esperado tipo de variável (int/string)\n");
        exit(1);
    }

    // nome da variável
    if (parser->current.type == TOKEN_IDENTIFIER) {
        strcpy(node.name, parser->current.value_str);
        parser_eat(parser, TOKEN_IDENTIFIER);
    } else {
        printf("Esperado nome da variável\n");
        exit(1);
    }

    // atribuição opcional
    if (parser->current.type == TOKEN_EQUAL) {
        parser_eat(parser, TOKEN_EQUAL);

        if (parser->current.type == TOKEN_NUMBER) {
            node.int_value = parser->current.value;
            parser_eat(parser, TOKEN_NUMBER);
        } else if (parser->current.type == TOKEN_STRING) {
		strcpy(node.str_value, parser->current.value_str);
		parser_eat(parser, TOKEN_STRING);
	} else {
            printf("Esperado valor após '='\n");
            exit(1);
        }
    }

    parser_eat(parser, TOKEN_SEMICOLON);
    return node;
}
