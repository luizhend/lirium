#include "../includes/packet.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

packet_t* create_packet(void* payload, void* header, packet_header_type type){
    printf("[LIRIUM PACKETS] Creating new packet\n");
    packet_t* packet = (packet_t*)malloc(sizeof(packet_t));
    packet->payload = payload;
    packet->header = header;
    return packet;
}

packet_ip_header_t* create_ip_header(size_t payload_len, uint8_t protocol,uint8_t dst[4], uint8_t src[4]){
    printf(
          "[LIRIUM PACKETS] Creating new IP header {\n"
          "\tPayload len: %zu\n"
          "\tProtocol int identifier: %u\n"
          "\tFrom %u.%u.%u.%u\n"
          "\tTo %u.%u.%u.%u\n"
          "}\n",
          payload_len,
          protocol,
          src[0], src[1], src[2], src[3],
          dst[0], dst[1], dst[2], dst[3]
      );
    packet_ip_header_t* header = (packet_ip_header_t*)malloc(sizeof(packet_ip_header_t));
    memcpy(header->dst, dst, sizeof header->dst);
    memcpy(header->src, src, sizeof header->src);
    header->payload_len = payload_len;
    header->protocol = protocol;
    return header;
}
