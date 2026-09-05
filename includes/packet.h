#ifndef LIRIUM_PACKET_H
#define LIRIUM_PACKET_H

#include <stdint.h>
#include <stddef.h>

typedef enum packet_header_type {
    HEADER_IP,
    HEADER_ETH,
    HEADER_IDK
} packet_header_type;

typedef struct packet_ip_header {
    uint8_t src[4];
    uint8_t dst[4];
    uint8_t protocol;
    size_t payload_len;
} packet_ip_header_t;

typedef struct packet {
    packet_header_type type;
    void *header;
    void *payload;
} packet_t;

packet_ip_header_t *create_ip_header(
    size_t payload_len,
    uint8_t protocol,
    uint8_t dst[4],
    uint8_t src[4]
);

packet_t *create_packet(
    void *payload,
    void *header,
    packet_header_type type
);

#endif
