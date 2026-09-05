#pragma once
#include "./node.h"

#include <stddef.h>
#include <stdint.h>
typedef struct network{
    uint8_t id;
    char *label;
    uint8_t label_len;
    network_interface_t **devices;
    size_t devices_len;
} network_t;

void add_interface(network_t*, network_interface_t*);
network_t* create_network(uint8_t, char*,uint8_t);
void network_route_packet(network_t*,packet_t*);
void set_static_ip(uint8_t*, network_interface_t*);
