/*
* A very simple HTTP server in C aka C frontend framework :)
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/errno.h>

#define QUEUE_LEN 10

int atoi(char s[], int s_len) {
    int multiplier = 1;
    int res = 0;
    
    for (int i = s_len - 1; i >= 0; --i) {
        if (s[i] != '\0' && s[i] >= '0' && s[i] <= '9') {
            res += (s[i] - '0') * multiplier;
           multiplier *= 10;
        }
    }

    return res;
}

void itoa(int n, char* s, int s_buffer) {
    char temp_s[s_buffer];
    for (int a = 0; a < s_buffer; ++a) {
        temp_s[a] = '\0';
    }

    int i = 0;
    while (n > 0) {
        char c = '0' + (n % 10);
        temp_s[i++] = c;
        n /= 10;
    }

    // setting the i to be the index of the first (last in the reversed order) digit
    i = s_buffer;
    char c;
    while ((c = temp_s[--i]) == '\0') 
        ;

    // reversing the string
    for (int a = i; a >= 0; --a) {
        *(s++) = temp_s[a];
    }
}

int main(int argc, char *argv[]) {
    int listening_socket, communicating_socket;
    struct addrinfo *p, hints, *res;
    struct sockaddr_in their_addr;

    char buf[4096];
    char request[8192]; 

    // configuring for the getaddrinfo 
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;     // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; 
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    // get the info about the local network
    int getaddrinfo_res = getaddrinfo(NULL, "40222", &hints, &res);
    if (getaddrinfo_res == -1) {
        printf("getaddrinfo error");
        return 1;
    }

    // opening the socket
    listening_socket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (listening_socket == -1) {
        printf("socket error");
        return 1;
    }

    // binding the socket to a port
    int bind_res = bind(listening_socket, res->ai_addr, res->ai_addrlen);
    while (bind_res == -1) {
        // printf("bind error %d\n", errno);
        bind_res = bind(listening_socket, res->ai_addr, res->ai_addrlen);
        // return 1;
    }
    printf("Socket bound!\n\n");

    // listening on that socket with the max queue length of QUEUE_LEN
    listen(listening_socket, QUEUE_LEN);

    // "game loop"
    while(1) {
        // accept their request
        unsigned int addr_size = sizeof(their_addr);
        communicating_socket = accept(listening_socket, (struct sockaddr *)&their_addr, &addr_size);

        int bytes_received;
        if ((bytes_received = recv(communicating_socket, buf, sizeof buf - 1, 0)) > 0) {      
            buf[bytes_received] = '\0';
            printf("%s\n\n", buf);
        }

        char response[] = 
        "<html>"
        "<head><title>badass C frontend framework</title><style>h1 {color: #ff0000;} </style></head>"
        "<body><h1>Welcome to C frontend framework</h1><h2>The sum of the two numbers you sent is exactly 13</h2></body>"
        "</html>\n";

        // send the response back once the whole request has been received
        char msg[1024];
        sprintf(msg, "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: %d\r\n"
            "\r\n"
            "%s", (int)sizeof(response), response);

        int bytes_sent = send(communicating_socket, msg, sizeof(msg), 0);
    }
}