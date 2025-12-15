#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"


// Parser
typedef struct {
	Lexer *lexer;
	TokenInfo current;
} Parser;

void parser_init(Parser *parser, Lexer *lexer);
void parser_eat(Parser *parser, Token expected);

// AST
typedef enum {
	AST_VAR_DECL
} ASTType;

// cria node da AST
typedef struct {
	ASTType type;
	Token var_type;
	char name[64];
	int int_value;
	char str_value[256];

} ASTNode;

ASTNode parse_var_decl(Parser *parser);


#endif
