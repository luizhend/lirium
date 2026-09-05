#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "../includes/network.h"
#include "../includes/interface.h"
#include "../includes/cli.h"
#include "node.h"

int main(void){

    char input[1024];

    while (1) {
        printf("lirium> ");
        fgets(input, sizeof(input), stdin);
        lex(input);
    }

    network_t* network = create_network();

    node_t* node = create_node(1);
    node_t* node_b = create_node(2);

    add_interface(network, node->interfaces[0]);
    add_interface(network, node_b->interfaces[0]);

    uint8_t ip[] = {192, 1, 7, 100};
    uint8_t ip_b[] = {192, 1, 7, 101};
    set_static_ip(ip, node->interfaces[0]);
    set_static_ip(ip_b, node_b->interfaces[0]);

    char* payload = "oi pessoal\nsaibam que eu sou um payload muito legal e divertido yeye uhul vamos la";
    uint8_t destination[] = {0, 0, 0, 0};
    uint8_t source[] = {0, 0, 0, 0};
    memcpy(source, node->interfaces[0]->ip_addr, sizeof(source));
    memcpy(destination, node_b->interfaces[0]->ip_addr, sizeof(destination));
    node_send_packet(payload, strlen(payload), destination, source, HEADER_IP, node);


    printf("[LIRIUM NETWORK] Process completed\n\n");
    return 0;
}
