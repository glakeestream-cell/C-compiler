#include "lexer.h"
#include <stdio.h>
#include <string.h>


void lexer_init(Lexer *lexer, const char *src) {
	lexer->src = src;
	lexer->pos = 0;
	lexer->current = src[0];
}

void lexer_advance(Lexer *lexer) {
	lexer->pos++;
	lexer->current = lexer->src[lexer->pos];
}

void lexer_skip_whitespace(Lexer *lexer) {
	while (lexer->current == ' ' || lexer->current == '\n' || lexer->current == '\t' || lexer->current == '\r'){
		lexer_advance(lexer);
	}
}

TokenInfo lexer_next_token(Lexer *lexer) {
    lexer_skip_whitespace(lexer);

    char c = lexer->current;

    if (lexer->current == '"') {
	    lexer_advance(lexer);
	    int len = 0;
	    char buffer[256];

	    while (lexer->current != '"' && lexer->current != '\0') {
		    buffer[len++] = lexer->current;
		    lexer_advance(lexer);
	    }

	    if (lexer->current == '"') {
		    lexer_advance(lexer);
		    buffer[len] = '\0';
		    TokenInfo tok;
		    tok.type = TOKEN_STRING;
		    tok.value = 0;
		    strcpy(tok.value_str, buffer);
		    return tok;
	    } else {
		    printf("'cê acha que eu sou magico pra advinhar onde a string acaba?");
		    return (TokenInfo){ TOKEN_UNKNOWN, 0};
	    }
    }






    // EOF
    if (c == '\0')
        return (TokenInfo){ TOKEN_EOF, 0 };

    // NÚMEROS
    if (c >= '0' && c <= '9') {
        int value = 0;
        while (lexer->current >= '0' && lexer->current <= '9') {
            value = value * 10 + (lexer->current - '0');
            lexer_advance(lexer);
        }
        return (TokenInfo){ TOKEN_NUMBER, value };
    }

    // IDENTIFICADORES + KEYWORDS
    if ((c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
         c == '_') {

        char buffer[64];
        int len = 0;

        while ((lexer->current >= 'a' && lexer->current <= 'z') ||
               (lexer->current >= 'A' && lexer->current <= 'Z') ||
               (lexer->current >= '0' && lexer->current <= '9') ||
                lexer->current == '_') {

            buffer[len++] = lexer->current;
            lexer_advance(lexer);
        }

        buffer[len] = '\0';

        // keywords
        if (!strcmp(buffer, "int"))    return (TokenInfo){ TOKEN_INT, 0 };
	if (!strcmp(buffer, "string")) return (TokenInfo){ TOKEN_STRING_KW, 0 };
        if (!strcmp(buffer, "fn"))     return (TokenInfo){ TOKEN_FN, 0 };
        if (!strcmp(buffer, "return")) return (TokenInfo){ TOKEN_RETURN, 0 };

        TokenInfo tok;
        tok.type = TOKEN_IDENTIFIER;
        tok.value = 0;
        strcpy(tok.value_str, buffer);
        return tok;
    }

    // OPERADORES E SÍMBOLOS
    lexer_advance(lexer);

    switch (c) {
        case '+': return (TokenInfo){ TOKEN_PLUS, 0 };
        case '-': return (TokenInfo){ TOKEN_MINUS, 0 };
        case '*': return (TokenInfo){ TOKEN_STAR, 0 };
        case '/': return (TokenInfo){ TOKEN_SLASH, 0 };
        case ',': return (TokenInfo){ TOKEN_COMMA, 0 };
        case ';': return (TokenInfo){ TOKEN_SEMICOLON, 0 };
        case '[': return (TokenInfo){ TOKEN_LSQRBRACKET, 0 };
        case ']': return (TokenInfo){ TOKEN_RSQRBRACKET, 0 };
        case '{': return (TokenInfo){ TOKEN_LBRACE, 0 };
        case '}': return (TokenInfo){ TOKEN_RBRACE, 0 };
        case '(': return (TokenInfo){ TOKEN_LPAREN, 0 };
        case ')': return (TokenInfo){ TOKEN_RPAREN, 0 };
	case '=': return (TokenInfo){ TOKEN_EQUAL, 0 };
    }
    printf("LEXER UNKNOWN CHAR: '%c' (%d)\n",
       lexer->current,
       lexer->current);
    return (TokenInfo){ TOKEN_UNKNOWN, 0 };
}
