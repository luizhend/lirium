#include "../includes/cli.h"
#include "network.h"
#include <stdint.h>
#include <stdio.h>

extern uint8_t networks_len;
extern network_t* networks[128];

void *parse(char *buffer, token_t **tokens, int tokens_len){
    for (int i = 0; i < tokens_len; i++) {
        printf("[LIRIUM CLI] Parsing token %.*s\n", tokens[i]->length, tokens[i]->start);
        switch(tokens[i]->type ){
            case TOK_CREATE:
                switch (tokens[i+1]->type) {
                    case TOK_NETWORK:
                        if(tokens[i + 2]->start == NULL || tokens[i+2]->type != TOK_IDENTIFIER){
                         printf("Invalid syntax, expected identifier\n");
                         return NULL;
                        }
                        char *label = tokens[i + 2]->start;

                        network_t* network = create_network(networks_len, label, tokens[i+2]->length);
                        networks[networks_len-1] = network;
                        printf("[LIRIUM CLI] Created network with label %.*s\n", tokens[i+2]->length, tokens[i+2]->start);
                        break;

                    default:
                    return 0;
                    break;
            }
            break;
            case TOK_SHOW:
                switch (tokens[i+1]->type) {
                    case TOK_NETWORK:
                        printf("Network\tConnected Nodes\t|\n");
                        for (int i = 0; i < networks_len; i++) {
                            printf("%.*s\t%d\n", networks[i]->label_len, networks[i]->label, networks[i]->devices_len);
                        }
                        break;
                    default:
                        return 0;
                        break;
                }
            default:
                return 0;
                break;
        }
    }
}
