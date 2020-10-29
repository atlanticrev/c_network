#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA d;

    // The WSADATA (d) structure will be filled in by WSAStartup() with
    // details about the Windows Sockets implementation
    if (WSAStartup(MAKEWORD(2, 2), &d)) 
    {
        printf("Failed to initialize.\n");
        return -1;
    }

    WSACleanup();
    printf("Ok.\n");

    return 0;
}