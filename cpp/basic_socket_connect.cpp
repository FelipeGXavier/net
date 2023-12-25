#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cerrno>   

int main() {
    const char *hostname = "localhost";
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

    int socketfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (socketfd == -1) {
        std::cerr << "Error creating socket: " << strerror(errno) << std::endl;
        freeaddrinfo(result);
        return 1;
    }

    int connectStatus = connect(socketfd, result->ai_addr, result->ai_addrlen);
    
    if (connectStatus == -1) {
        std::cerr << "Error connecting: " << strerror(errno) << std::endl;
        freeaddrinfo(result);
        return 1;
    }

    // Do something with the connected socket...

    freeaddrinfo(result);

    return 0;
}