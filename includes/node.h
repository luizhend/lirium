#include <stdint.h>
#include <stddef.h>

typedef struct network_interface {
    uint8_t  mac_addr[6];
    uint8_t ip_addr[4];
} network_interface_t;

typedef struct node {
    uint32_t id;
    char* hostname;
    network_interface_t **interfaces;
    size_t interfaces_count;
} node_t;


node_t* create_node(size_t);
