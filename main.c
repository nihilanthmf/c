#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define QUEUE_LEN 10

int main(int argc, char *argv[]) {
    int listening_socket, communicating_socket;
    struct addrinfo *p, hints, *res;
    struct sockaddr_in their_addr;
    char buf[1024];

    // configuring for the getaddrinfo 
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;     // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    // get the info about the local network
    getaddrinfo(NULL, "3490", &hints, &res);

    // opening the socket
    listening_socket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    // binding the socket to a port
    bind(listening_socket, res->ai_addr, res->ai_addrlen);

    // listing on that socket with the max queue length of QUEUE_LEN
    listen(listening_socket, QUEUE_LEN);

    // "game loop"
    while(1) {
        // accept their request
        unsigned int addr_size = sizeof(their_addr);
        communicating_socket = accept(listening_socket, (struct sockaddr *)&their_addr, &addr_size);

        int bytes_received = recv(communicating_socket, buf, sizeof buf - 1, 0);
        
        if (bytes_received > 0) {
            buf[bytes_received] = '\0';
            printf("%s", buf);

            char msg[] = "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 14\r\n"
            "\r\n"
            "Hello from C!\n";

            int bytes_sent = send(communicating_socket, msg, sizeof(msg), 0);
        }
    }
}