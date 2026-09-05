#include "../includes/node.h"
#include "stdlib.h"
#include <stddef.h>
#include <stdint.h>
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


void send_packet(void* payload, size_t payload_len,uint8_t *dst,  uint8_t *src, packet_header_type type,node_t* node){
    printf(
            "[LIRIUM NODE] Node identified by %d\n"
            "\tTrying to send packet from IP %d.%d.%d.%d -> %d.%d.%d.%d\n",
            node->id,
            src[0], src[1], src[2], src[3],
            dst[0], dst[1], dst[2], dst[3]
        );
    switch (type) {
        case HEADER_IP:{
            packet_ip_header_t* header = create_ip_header(sizeof(payload_len), 0, dst , src);
            packet_t* packet = create_packet(payload, header, type);
            break;
        }
        case HEADER_ETH:
            //todo
            break;
        default:
            break;
    }

}
