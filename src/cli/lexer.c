#include "../includes/cli.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NEXT_CHAR(buffer, c, idx) c = buffer[++idx]

token_t* tokens[128];

int get_keyword(char *word, int len){
    for(int i = 0; i < *(&keywords + 1) - keywords;i++){

        if(strncmp(word, keywords[i].name, len) == 0){
            printf("[LIRIUM CLI] Found keyword %s\n", keywords[i].name);
            return keywords[i].type;
        }
    }
    return 0;
}

token_t* create_token(token_type type, char *start, int length){
    printf("[LIRIUM CLI] Creating token %.*s\n", length, start);
    token_t* token = (token_t*)malloc(sizeof(token_t));
    token->type = type;
    token->length = length;
    token->start = start;

    return token;
}

int step(char *buffer, int *idx, int *tk_idx) {
    char c = buffer[*idx];
    switch (c) {
        case '\0':
            return 0;
            break;
        case ' ':
        case '\n':
        case '\t':
        case '\r':
            NEXT_CHAR(buffer, c, *idx);
            break;
        case 'a'...'z':
        case 'A'...'Z':
        case '_':{
            int start = *idx;
            while ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                NEXT_CHAR(buffer, c, *idx);
            }

            char *word = buffer + start;
            int kw = (int)get_keyword(word, *idx - 1 - start);
            token_t* token = create_token((kw > 0 ? kw : TOK_IDENTIFIER), &buffer[start], *idx - start);
            tokens[*tk_idx] = token;
            *tk_idx += 1;
            break;
            }
        case '"':{
            NEXT_CHAR(buffer, c, *idx);
            int start = *idx;
            while (c != '"') {
                NEXT_CHAR(buffer, c, *idx);
            }
            char *literal = buffer + start;
            NEXT_CHAR(buffer, c, *idx);
            token_t* token = create_token(TOK_STRING, literal, *idx - start);
            tokens[*tk_idx] = token;
            *tk_idx += 1;
            break;
        }

        default:
            printf("[LIRIUM CLI] Unexpected char: %c\n", c);
            return 0;
            break;
    }
    return 1;
}

void lex(char *buffer) {
    int i = 0;
    int tk_idx=0;
    while (step(buffer, &i, &tk_idx) != 0) {

        ;
    }


    parse(buffer, tokens, tk_idx);

    tk_idx = 0;;

    memset(tokens, 0, 128);

}
