#pragma once
#include <stddef.h>
#include <stdint.h>
#include "./network.h"

typedef struct network_interface {
    uint8_t  mac_addr[6];
    uint8_t ip_addr[4];
    network_t* network;
} network_interface_t;

void interface_send_packet(packet_t*, network_interface_t*);
network_interface_t* create_interface(size_t);
