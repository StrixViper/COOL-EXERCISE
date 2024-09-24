#include <stdio.h>
#include <stdlib.h>

void block_ip(const char* ip) {
    char command[256];
    snprintf(command, sizeof(command), "iptables -A INPUT -s %s -j DROP", ip);
    system(command);
}

int main() {
    char ip_to_block[16];
    printf("Enter IP to block: ");
    scanf("%15s", ip_to_block);
    block_ip(ip_to_block);
    printf("Blocked IP: %s\n", ip_to_block);
    return 0;
}
