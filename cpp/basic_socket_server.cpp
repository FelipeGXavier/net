#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cerrno>
#include <unistd.h>

void handleSocketError(int status, std::string context) {
    if (status == -1) {
        std::cerr << "Socket error: " << context << " " << gai_strerror(status) << std::endl;
        exit(1);
    }
}

int main() {
    pid_t process_id = getpid();

    std::cout << "PID: " << process_id << std::endl;

    struct sockaddr_storage their_addr;
    struct addrinfo hints, *result, *p;
    socklen_t addr_size;
    const char* port = "3090";
    const int backlogSize = 5;
    const char *hostname = "localhost";
    
    std::memset(&hints, 0, sizeof hints);

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int status = getaddrinfo(hostname, port, &hints, &result);
    handleSocketError(status, "getaddrinfo");

    int socketfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    handleSocketError(socketfd, "socket");

    int bindStatus = bind(socketfd, result->ai_addr, result->ai_addrlen);
    handleSocketError(bindStatus, "bind");

    int listenerStatus = listen(socketfd, backlogSize);
    handleSocketError(listenerStatus, "listen");

    addr_size = sizeof(their_addr);
    int newConnectionFd = accept(socketfd, (struct sockaddr *)&their_addr, &addr_size);
    handleSocketError(newConnectionFd, "accept");

    return 0;
}