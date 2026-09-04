#include "../includes/network.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

network_t* create_network(){
    printf("[LIRIUM NETWORK] Creating new network\n");
    network_t* network = (network_t*)malloc(sizeof(network_t));
    network->nodes = NULL;
    network->nodes_len = 0;
    return network;
}

void add_node(network_t *network, node_t *node){
    printf("[LIRIUM NETWORK] Adding node ID %d to network\n", node->id);
    network->nodes = realloc(network->nodes, (network->nodes_len + 1) * sizeof(node_t*));
    network->nodes[network->nodes_len] = node;
    network->nodes_len++;
}

void set_static_ip(uint8_t* ip, network_interface_t* interface){
    printf("[LIRIUM NETWORK] Setting interface with MAC %02X:%02X:%02X:%02X:%02X:%02X\n\tTo IP %d.%d.%d.%d\n", interface->mac_addr[0],
        interface->mac_addr[1],
        interface->mac_addr[2],
        interface->mac_addr[3],
        interface->mac_addr[4],
        interface->mac_addr[5],
        ip[0],
        ip[1],
        ip[2],
        ip[3]
    );
    interface->ip_addr[0] = ip[0];
    interface->ip_addr[1] = ip[1];
    interface->ip_addr[2] = ip[2];
    interface->ip_addr[3] = ip[3];
}
