#include <stddef.h>
typedef enum {
    TOK_STRING,
    TOK_NUMBER,
    TOK_IDENTIFIER,

    TOK_NETWORK,
    TOK_SELECT,
    TOK_NODE,
    TOK_INTERFACE,
    TOK_MAC,
    TOK_IP,
    TOK_PROTOCOL,
    TOK_CONNECT,
    TOK_CREATE,
    TOK_PACKET_SEND,
    TOK_PACKET_HEADER_TYPE,

    TOK_EOF
} token_type;



typedef struct token{
    token_type type;
    char *start;
    size_t length;
} token_t;

typedef struct {
    char *name;
    token_type type;
} Keyword;




void lex(char *buffer);
