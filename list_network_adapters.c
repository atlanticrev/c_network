#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    struct ifaddrs *addresses;

    // Allocate memory for addresses and fill it in a list of addresses
    if (getifaddrs(&addresses) == -1)
    {
        printf("getifaddrs call failed\n");
        return -1;
    }

    // Pointer for walking through linked-list of addresses
    struct ifaddrs *address = addresses;

    while (address)
    {
        int family = address->ifa_addr->sa_family;
        // Pass all not "IPv4" and "IPv6 addresses
        if (family == AF_INET || family == AF_INET6)
        {
            printf("%s\t", address->ifa_name);
            printf("%s\t", family == AF_INET ? "IPv4" : "IPv6");

            // Buffer for textual address
            char ap[100];

            const int family_size = family == AF_INET
                ? sizeof(struct sockaddr_in)
                : sizeof(struct sockaddr_in6);

            // Fill the buffer of the textual address
            getnameinfo(address->ifa_addr, family_size, ap, sizeof(ap), 0, 0, NI_NUMERICHOST);
            printf("\t%s\n", ap);
        }
        // Go to the next address
        address = address->ifa_next;
    }

    freeifaddrs(addresses);
    return 0;

}