#include "../includes/cli.h"
#include "network.h"
#include "node.h"
#include "interface.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

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
                         node_t *node = create_node(nodes_len + 1, label,  tokens[i+2]->length);
                         nodes[nodes_len] = node;
                         nodes_len +=1 ;
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
                    case TOK_INTERFACE:
                        printf("Host\t\tMAC\t\tIP\t\t|\n");
                        for(int i = 0; i<nodes_len;i++){
                            for(int j=0;j<nodes[i]->interfaces_count;j++){

                            printf("%s\t%02X:%02X:%02X:%02X:%02X:%02X\t%d.%d.%d.%d\n",
                                nodes[i]->hostname,
                                nodes[i]->interfaces[j]->mac_addr[0],
                                nodes[i]->interfaces[j]->mac_addr[1],
                                nodes[i]->interfaces[j]->mac_addr[2],
                                nodes[i]->interfaces[j]->mac_addr[3],
                                nodes[i]->interfaces[j]->mac_addr[4],
                                nodes[i]->interfaces[j]->mac_addr[5],
                                nodes[i]->interfaces[j]->ip_addr[0],
                                nodes[i]->interfaces[j]-> ip_addr[1],
                                nodes[i]->interfaces[j]->ip_addr[2],
                                nodes[i]->interfaces[j]->ip_addr[3]);

                            }
                        }
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
