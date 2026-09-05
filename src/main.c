#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "../includes/network.h"

int main(void){

    network_t* network = create_network();

    node_t* node = create_node(1);

    add_node(network, node);

    uint8_t ip[] = {192, 1, 7, 100};
    set_static_ip(ip, node->interfaces[0]);
    printf("[LIRIUM NETWORK] Node identified by %d HAS ip %d.%d.%d.%d\n", node->id, node->interfaces[0]->ip_addr[0],
        node->interfaces[0]->ip_addr[1],
        node->interfaces[0]->ip_addr[2],
        node->interfaces[0]->ip_addr[3]);
    char* payload = "oi pessoal";
    uint8_t destination[] = {0, 0, 0, 0};
    uint8_t source[] = {0, 0, 0, 0};
    memcpy(source, node->interfaces[0]->ip_addr, sizeof(source));
    send_packet(payload, strlen(payload), destination, source, HEADER_IP, node);


    printf("[LIRIUM NETWORK] Process completed\n");
    return 0;
}
