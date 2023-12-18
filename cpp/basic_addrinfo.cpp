#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{

    const char *hostname = "example.com";
    const char *port = "http";

    struct addrinfo hints, *result, *p;

    // Set up hints for the type of addresses we want
    std::memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;    // Allow IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP socket

    // Call getaddrinfo to get a linked list of addresses
    int status = getaddrinfo(hostname, port, &hints, &result);
    if (status != 0) {
        std::cerr << "getaddrinfo error: " << gai_strerror(status) << std::endl;
        return 1;
    }

    // Iterate through the linked list
    // Is linked list for some reasons, like a domain server can point to more than one IP
    // Or because a server may have a IPv4 and a IPv6
    for (p = result; p != nullptr; p = p->ai_next) {
        // Access the address information in p

        // Print the IP address as a string (IPv4 or IPv6)
        char ipStr[INET6_ADDRSTRLEN];
        void *addr;
        if (p->ai_family == AF_INET) {
            addr = &reinterpret_cast<struct sockaddr_in*>(p->ai_addr)->sin_addr;
        } else {
            addr = &reinterpret_cast<struct sockaddr_in6*>(p->ai_addr)->sin6_addr;
        }

        inet_ntop(p->ai_family, addr, ipStr, sizeof ipStr);

        std::cout << "IP Address: " << ipStr << std::endl;
    }

    // Don't forget to free the memory allocated by getaddrinfo
    freeaddrinfo(result);
}
