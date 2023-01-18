//
// Created by noash on 10/01/2023.
//

#ifndef EX4_SERVER_H
#define EX4_SERVER_H


#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

class Server
{
private:
    int server_sock_fd;
    int port_no;
    struct sockaddr_in server_sockaddr;
    int client_sock_fd;


public:
    explicit Server(const int port);
    bool openServerSocketAndBindPort();
    bool listenForClients(int MAX_CLIENTS);
    int acceptClient();
    bool sendData(int client_sock_fd, std::string& data);
    std::string receive(int client_sock_fd, int size);
    void closeClientSock(int client_sock_fd);
    void closeServerSock();
};

#endif //EX4_SERVER_H
