#include "../includes/cli.h"
#include <stdio.h>
#include <stdlib.h>
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

token_t* create_token(token_type type, char *start, size_t length){
    printf("[LIRIUM CLI] Creating token %s\n", start);
    token_t* token = (token_t*)malloc(sizeof(token_t));
    token->type = type;
    token->length = length;
    token->start = start;
    return token;
}

int step(const char *buffer, int *idx) {
    char c = buffer[*idx];

    switch (c) {
        case '\0':
            return 0;
            break;
        case ' ':
        case '\t':
        case '\n':
        case '\r':
            NEXT_CHAR(buffer, c, *idx);
            break;
        case 'a'...'z':
        case 'A'...'Z':
        case '_':
            int start = *idx;
            while ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                NEXT_CHAR(buffer, c, *idx);
            }
            create_token(TOK_IDENTIFIER, &c, start);
            break;
        default:
            printf("[LIRIUM CLI] Unexpected char: %c\n", c);
            return 0;
            break;
    }

}



void lex(const char *buffer) {
    int i = 0;

    while (step(buffer, &i) != 0) {
        ;
    }
}
