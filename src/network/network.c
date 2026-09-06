#include "../includes/network.h"
#include "../includes/interface.h"
#include "node.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

network_t* create_network(uint8_t id, char *label, uint8_t label_len){
    printf("[LIRIUM NETWORK] Creating new network\n");
    network_t* network = (network_t*)malloc(sizeof(network_t));
    network->id = id;
    network->devices = NULL;
    network->devices_len = 0;
    network->label = label;

    network->label_len = label_len;
    return network;
}

void add_interface(network_t *network, network_interface_t *device){
    printf("[LIRIUM NETWORK] Adding node device identified by MAC %02X:%02X:%02X:%02X:%02X:%02X to network\n\n", device->mac_addr[0],
        device->mac_addr[1],
        device->mac_addr[2],
        device->mac_addr[3],
        device->mac_addr[4],
        device->mac_addr[5]);
    network->devices = realloc(network->devices, (network->devices_len + 1) * sizeof(network_interface_t*));
    network->devices[network->devices_len] = device;
    network->devices_len++;
    device->network = network;
}

void set_static_ip(uint8_t* ip, network_interface_t* interface){
    printf("[LIRIUM NETWORK] Setting interface with MAC %02X:%02X:%02X:%02X:%02X:%02X\n\tTo IP %d.%d.%d.%d\n\n", interface->mac_addr[0],
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

network_interface_t* resolve_network_node(network_t* network ,uint8_t interface_ip[4]){
    for (int i=0; i<network->devices_len; i++) {
        network_interface_t* interface = network->devices[i];
        if (memcmp(interface->ip_addr, interface_ip, 4) == 0) {
            return network->devices[i];
        }
    }
    return NULL;
}

void network_route_packet(network_t* network,packet_t* packet){
    switch (packet->type) {
        case HEADER_IP:{
             packet_ip_header_t *header = packet->header;
             network_interface_t *dst_interface =resolve_network_node(network, header->dst);
             if (dst_interface == NULL) {
                 printf(
                     "[LIRIUM NETWORK] Attempt to find destination %d.%d.%d.%d failed\n"
                     "\tPacket from interface identified by MAC %02X:%02X:%02X:%02X:%02X:%02X\n\n",
                     header->dst[0],
                     header->dst[1],
                     header->dst[2],
                     header->dst[3],
                     header->src_mac[0],
                     header->src_mac[1],
                     header->src_mac[2],
                     header->src_mac[3],
                     header->src_mac[4],
                     header->src_mac[5]
                 );
                 return;
             }
             printf("[LIRIUM NETWORK] Successfully resolved packet from %02X:%02X:%02X:%02X:%02X:%02X\n\tTo: %d.%d.%d.%d\n\n",
                 header->src_mac[0],
                 header->src_mac[1],
                 header->src_mac[2],
                 header->src_mac[3],
                 header->src_mac[4],
                 header->src_mac[5],
                 header->dst[0],
                 header->dst[1],
                 header->dst[2],
                 header->dst[3]
             );
             interface_receive_packet(packet, dst_interface);
             break;
            }
        default:
            break;
    }
}
