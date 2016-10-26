
#ifdef WIN32
#include <pthread.h>
#include <iostream>
#include <cygwin/socket.h>
#include <sys/socket.h>
#include <cstring>
#include <asm/byteorder.h>
#include <cygwin/in.h>
#include <vector>
#include <unistd.h>
#include <w32api/fibersapi.h>
#include <w32api/ntdef.h>
#include "server.h"
#else
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <cstring>
#include <asm/byteorder.h>
#include <vector>
#include <unistd.h>
#include "server.h"
#endif


#define BUFF_SIZE 500

Server::Server() {
    server_sock = socket(AF_INET, SOCK_STREAM, 0);

}

int Server::start(int port) {

    struct sockaddr_in local_addr;
    memset(&local_addr, 0, sizeof(struct sockaddr_in));

    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(port);
    local_addr.sin_addr.s_addr = INADDR_ANY;

    int err = bind(server_sock, (struct sockaddr *) &local_addr, sizeof(struct sockaddr_in));
    if (err == 0)
        printf("Bind OK\n");
    else {
        printf("Bind ER\n");
        return err;
    }

    err = listen(server_sock, 5);
    if (err == 0)
        printf("Listen OK\n");
    else {
        printf("Listen ER\n");
        return err;
    }

    running = true;

    return 0;
}

void Server::stop() {

}

bool Server::isRunning() {
    return running;
}

void Server::loop() {
    accepting_loop();

}

void Server::accepting_loop() {

    struct sockaddr_in remote_addr;
    socklen_t remote_addr_len;
    pthread_t t;
    int *th_socket;
    
    while (1) {
        int client_sock = accept(server_sock, (struct sockaddr *) &remote_addr, &remote_addr_len);
        if (client_sock > 0) {
            th_socket = (int *) malloc(sizeof(int));
            *th_socket = client_sock;
            pthread_create(&t, NULL, (void *(*)(void *)) (void *)&serve_request, (void *)th_socket);

        } else {
            printf("Socket error\n");
            return;

        }
    }
}

void *serve_request(void *arg) {
    int client_sock;
    char *buffer = new char[BUFF_SIZE];
    ssize_t count = 0;
    std::string message = "";
    client_sock = *(int *) arg;


    count = BUFF_SIZE + 1;
    while (count>=BUFF_SIZE){
        count = recv(client_sock, buffer, BUFF_SIZE, 0);
        message.append(buffer,count);
    };
    std::cout << "received:" << message << std::endl;

    std::string output(message.rbegin(), message.rend()); // ¯\_(ツ)_/¯, just std thing

    send(client_sock, output.c_str(), output.length(), 0);
    std::cout << "sended:" << output << std::endl;
    close(client_sock);
    delete buffer;
    free(arg);
    return 0;
}
