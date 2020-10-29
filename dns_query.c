#include "include/cross_platform.h"

// char dns_query[] = {
//     0xAB, 0xCD,                           /* ID */
//     0x01, 0x00,                           /* Recursion */
//     0x00, 0x01,                           /* QDCOUNT */
//     0x00, 0x00,                           /* ANCOUNT */
//     0x00, 0x00,                           /* NSCOUNT */
//     0x00, 0x00,                           /* ARCOUNT */
//     7, 'e', 'x', 'a', 'm', 'p', 'l', 'e', /* label */
//     3, 'c', 'o', 'm',                     /* label */
//     0,                                    /* End of name */
//     0x00, 0x01,                           /* QTYPE = A */
//     0x00, 0x01                            /* QCLASS */
// }

const unsigned char *print_name(const unsigned char *msg,
    const unsigned char *p,
    const unsigned char *end)
{
    // check that "p" is at least 2 bytes from the end.
    if (p + 2 > end) 
    {
        fprintf(stderr, "End of message.\n"); 
        exit(1);
    }

    // Check the bitmask 1100_0000 (is it name a pointer?)
    if ((*p & 0xC0) == 0xC0) 
    {
        const int k = ((*p & 0x3F) << 8) + p[1];
        p += 2;
        printf(" (pointer %d) ", k);
        print_name(msg, msg + k, end);
        return p;
    }
    // Name is not a pointer
    else
    {
        const int len = *p++;
        if (p + len + 1 > end) 
        {
            fprintf(stderr, "End of message.\n"); exit(1);
        }
        
        printf("%.*s", len, p);

        p += len;
        // If the next byte isn't 0
        if (*p)
        {
            printf(".");
            return print_name(msg, p, end);
        } 
        else 
        {
            return p + 1;
        }
    }
}

void print_dns_message(const char *message, int msg_length)
{

}