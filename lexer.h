#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_EQUAL,        // = 0
    TOKEN_PLUS,         // + 1
    TOKEN_MINUS,        // - 2 
    TOKEN_STAR,         // * 3
    TOKEN_SLASH,        // '/' 4 
    TOKEN_COMMA,        // , 5
    TOKEN_SEMICOLON,    // ; 6
    TOKEN_LSQRBRACKET,  // [ 7
    TOKEN_RSQRBRACKET,  // ] 8
    TOKEN_LBRACE,       // { 9
    TOKEN_RBRACE,       // } 10
    TOKEN_LPAREN,       // ( 11
    TOKEN_RPAREN,       // ) 12
    TOKEN_NUMBER,       // 123 13
    TOKEN_UNKNOWN,  // 14
    TOKEN_IDENTIFIER,  // varName 15
    TOKEN_STRING,          // String 16
    TOKEN_EOF, // 17
    //keywords
    
    TOKEN_INT, //18
    TOKEN_STRING_KW, //19
    TOKEN_FN, //20
    TOKEN_RETURN //21
} Token;

typedef struct {
	const char *src;
	int pos;
	char current;
} Lexer;

typedef struct {
	Token type;
	int value;
	char value_str[256];
} TokenInfo;

void lexer_init(Lexer *lexer, const char *src);
TokenInfo lexer_next_token(Lexer *lexer);

#endif
