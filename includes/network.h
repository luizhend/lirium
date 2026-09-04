#include "./node.h"
#include <stddef.h>
typedef struct network{
    node_t **nodes;
    size_t nodes_len;
} network_t;

void add_node(network_t*, node_t*);
network_t* create_network();
void set_static_ip(uint8_t*, network_interface_t*);
