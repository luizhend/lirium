#include "../includes/node.h"
#include "stdlib.h"
#include <stddef.h>
#include <stdio.h>

node_t* create_node(size_t identifier){
    printf("[LIRIUM NODE] Creating node with identifier %ld\n", identifier);
    node_t* node = (node_t*)malloc(sizeof(node_t));
    node->interfaces_count = 1;
    node->id = identifier;
    network_interface_t* interface = (network_interface_t*)malloc(sizeof(network_interface_t));
    node->interfaces = (network_interface_t**)malloc(sizeof(*node->interfaces));

    interface->mac_addr[0] = 0x02;
    interface->mac_addr[1] = (identifier >> 32) & 0xff;
    interface->mac_addr[2] = (identifier >> 24) & 0xff;
    interface->mac_addr[3] = (identifier >> 16) & 0xff;
    interface->mac_addr[4] = (identifier >> 8)  & 0xff;
    interface->mac_addr[5] = identifier & 0xff;

    node->interfaces[0] = interface;

    return node;
}
