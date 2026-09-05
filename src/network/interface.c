#include "../includes/interface.h"
#include "network.h"

#include <stdio.h>
#include <stdlib.h>

network_interface_t* create_interface(size_t identifier){
    network_interface_t* interface = (network_interface_t*)malloc(sizeof(network_interface_t));
    interface->mac_addr[0] = 0x02;
    interface->mac_addr[1] = (identifier >> 32) & 0xff;
    interface->mac_addr[2] = (identifier >> 24) & 0xff;
    interface->mac_addr[3] = (identifier >> 16) & 0xff;
    interface->mac_addr[4] = (identifier >> 8)  & 0xff;
    interface->mac_addr[5] = identifier & 0xff;
    printf("[LIRIUM INTERFACE] Created interface with MAC Address\n\t%02X:%02X:%02X:%02X:%02X:%02X\n\n",
        interface->mac_addr[0],
            interface->mac_addr[1],
            interface->mac_addr[2],
            interface->mac_addr[3],
            interface->mac_addr[4],
            interface->mac_addr[5]);
    return interface;
}


void interface_send_packet(packet_t* packet, network_interface_t* interface){
    printf("[LIRIUM INTERFACE] Interface Identified by MAC Address\n\t%02X:%02X:%02X:%02X:%02X:%02X\n\tRequest packet handling\n\tWith header type: %d\n\n",
        interface->mac_addr[0],
            interface->mac_addr[1],
            interface->mac_addr[2],
            interface->mac_addr[3],
            interface->mac_addr[4],
            interface->mac_addr[5],
            packet->type);

    network_route_packet(interface->network, packet);
}
