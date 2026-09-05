#include <stdint.h>
#include <stdio.h>
#include "../includes/network.h"
#include "../includes/cli.h"
#include "node.h"

network_t* networks[128];
node_t* nodes[128];
uint8_t nodes_len=0;
uint8_t networks_len = 1;

int main(void){

    char input[1024];

    while (1) {
        printf("lirium> ");
        fgets(input, sizeof(input), stdin);
        lex(input);
    }

    return 0;
}
