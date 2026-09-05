#include "../includes/cli.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NEXT_CHAR(buffer, c, idx) c = buffer[++idx]

static const Keyword keywords[] = {
    {"network", TOK_NETWORK},
    {"select", TOK_SELECT},
    {"node", TOK_NODE},
    {"interface", TOK_INTERFACE},
    {"mac", TOK_MAC},
    {"ip", TOK_IP},
    {"protocol", TOK_PROTOCOL},
    {"connect", TOK_CONNECT},
    {"create", TOK_CREATE},
    {"packet", TOK_PACKET_SEND},
    {"header", TOK_PACKET_HEADER_TYPE},
};

int get_keyword(char *word, int len){
    for(int i = 0; i < *(&keywords + 1) - keywords;i++){

        printf("[LIRIUM CLI] Comparing %.*s, to keyword %s\n", len + 1 , word, keywords[i].name);
        if(strncmp(word, keywords[i].name, len) == 0){
            printf("[LIRIUM CLI] Find keyword %s\n", keywords[i].name);
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

int step(char *buffer, int *idx) {
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
            create_token((kw > 0 ? kw : TOK_IDENTIFIER), &buffer[start], start);
            break;
            }
        case '"':{
            int start = *idx;
            NEXT_CHAR(buffer, c, *idx);
            while (c != '"') {
                NEXT_CHAR(buffer, c, *idx);
            }
            char *literal = buffer + start;
            NEXT_CHAR(buffer, c, *idx);
            create_token(TOK_STRING, literal, *idx - start);
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

    while (step(buffer, &i) != 0) {
        ;
    }
}
