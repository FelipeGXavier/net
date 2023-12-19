#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h> // addrinfo stuff
#include <arpa/inet.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/un.h>

void printFileDescriptor(struct stat fdInfo) {
    printf("File Descriptor Information:\n");
    printf("  File type:                %d\n", (int)fdInfo.st_mode);
    printf("  Device ID:                %lu\n", (unsigned long)fdInfo.st_dev);
    printf("  Inode number:             %lu\n", (unsigned long)fdInfo.st_ino);
    printf("  Number of hard links:     %lu\n", (unsigned long)fdInfo.st_nlink);
    printf("  User ID of owner:         %u\n", (unsigned int)fdInfo.st_uid);
    printf("  Group ID of owner:        %u\n", (unsigned int)fdInfo.st_gid);
    printf("  File size:                %ld bytes\n", (long)fdInfo.st_size);

}

int main(int argc, char const *argv[])
{
    struct addrinfo hints, *result, *p;
    std::memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_UNSPEC; // IPv6 or IPv4
    hints.ai_socktype = SOCK_STREAM; // Set type of socket, in this case stream socket
    hints.ai_flags = AI_PASSIVE; // Say to get the IP from running machine

    getaddrinfo(NULL, "3490", &hints, &result);

    int sockfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (bind(sockfd, result->ai_addr, result->ai_addrlen)) {
         perror("bind");
         close(sockfd);
         return 1;
    }

    struct stat fdInfo;
    if (fstat(sockfd, &fdInfo) == -1) {
        close(sockfd);
        perror("fstat err");
        return 1;
    }

    printFileDescriptor(fdInfo);

    pid_t process_id = getpid();

    std::cout << "PID: " << process_id << std::endl;

    while(1) {

    }

    close(sockfd);

    return 0;
}

