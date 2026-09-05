#include "../includes/cli.h"
#include "network.h"
#include "node.h"
#include <stdint.h>
#include <stdio.h>

extern uint8_t networks_len;
extern network_t* networks[128];
extern node_t* nodes[128];
extern uint8_t nodes_len;
void parse(char *buffer, token_t **tokens, int tokens_len){
    for (int i = 0; i < tokens_len; i++) {
        printf("[LIRIUM CLI] Parsing token %.*s\n", (int)tokens[i]->length, tokens[i]->start);
        switch(tokens[i]->type ){
            case TOK_CREATE:
                        if(tokens[i + 2]->start == NULL || tokens[i+2]->type != TOK_IDENTIFIER){
                         printf("Invalid syntax, expected identifier\n");
                         return;
                        }
                    char *label = tokens[i + 2]->start;
                switch (tokens[i+1]->type) {
                    case TOK_NETWORK: {
                        network_t* network = create_network(networks_len, label, tokens[i+2]->length);
                        networks[networks_len] = network;
                        networks_len +=1;
                        printf("[LIRIUM CLI] Created network with label %s", tokens[i+2]->start);
                        break;
                        }
                    case TOK_NODE: {
                         node_t *node = create_node(networks_len + 1, label,  tokens[i+2]->length);
                         nodes[nodes_len] = node;
                         nodes_len +=1;
                        printf("[LIRIUM CLI] Created node with label %s", tokens[i+2]->start);
                        break;
                        }
                    default:
                        return;
                        break;
            }
            break;
            case TOK_SHOW:
                switch (tokens[i+1]->type) {
                    case TOK_NETWORK:
                        printf("Network\tConnected Nodes\t|\n");
                        for (int i = 0; i < networks_len; i++) {
                            printf("%.*s\t%ld\n", networks[i]->label_len, networks[i]->label, networks[i]->devices_len);
                        }
                        break;
                    case TOK_NODE:
                        printf("Node\tConnected Interfaces\t|\n");
                        for (int i = 0; i < nodes_len; i++) {
                            printf("%.*s\t%ld\n", nodes[i]->hostname_len, nodes[i]->hostname, nodes[i]->interfaces_count);
                        }
                        break;
                    default:
                        return;
                        break;
                }
            default:
                return;
                break;
        }
    }
}
