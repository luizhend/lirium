#pragma once
#include "./node.h"

#include <stddef.h>
typedef struct network{
    network_interface_t **devices;
    size_t devices_len;
} network_t;

void add_interface(network_t*, network_interface_t*);
network_t* create_network();
void network_route_packet(network_t*,packet_t*);
void set_static_ip(uint8_t*, network_interface_t*);
