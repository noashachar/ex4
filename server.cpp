#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "server.h"
#include <vector>
#include <thread>
#include <algorithm>

#include "SocketIO.h"
#include "cli.h"

using namespace std;


Server::Server(const int port) {
    server_sock_fd = -1;
    port_no = port;
}

/*
    Connect to a host on a certain port number
*/
bool Server::openServerSocketAndBindPort() {
    // create socket if it is not already created
    if (server_sock_fd == -1) {
        //Create socket
        server_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_sock_fd < 0) {
            perror("error creating socket");
            return false;
        }
        memset(&server_sockaddr, 0, sizeof(server_sockaddr));
        server_sockaddr.sin_family = AF_INET;
        server_sockaddr.sin_addr.s_addr = INADDR_ANY;
        server_sockaddr.sin_port = htons(port_no);
        if (::bind(server_sock_fd, (struct sockaddr *) &server_sockaddr, sizeof(server_sockaddr)) < 0) {
            perror("error binding socket");
            return false;
        }
    }
    return true;
}

bool Server::listenForClients(int MAX_CLIENTS = 5) {
    if (listen(server_sock_fd, MAX_CLIENTS) < 0) {
        perror("error listening to a socket");
        return false;
    }
    return true;
}


/*
    Send data to the connected host
*/
bool Server::sendData(int client_sock_fd, string &data) {
    // Send some data
    if (send(client_sock_fd, data.c_str(), data.length(), 0) < 0) {
        perror("Send failed :( ");
        return false;
    }

    return true;
}

// returns client_sock_fd or 0 if failed
int Server::acceptClient() {
    unsigned int addr_len = sizeof(server_sockaddr);
    int client_sock_fd = accept(server_sock_fd, (struct sockaddr *) &server_sockaddr, &addr_len);
    if (client_sock_fd < 0) {
        perror("error accepting client");
        return 0;
    }
    return client_sock_fd;
}


void Server::closeClientSock(int client_sock_fd) {
    int result = close(client_sock_fd);
    if (result < 0) {
        perror("could not close socket with client");
    }
}

void Server::closeServerSock() {
    int result = close(server_sock_fd);
    if (result < 0) {
        perror("could not close server socket");
    }
}

// this function cannot be a Server method because it's invoked as a new thread,
// and a new thread can only accept static functions
void handle_client(DefaultIO* dio) {
    CLI cli(dio);
    try {
        cli.start();
    }
    catch (SocketIoConnectionEnded&) {} // if client disconnects, ignore.
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " port" << std::endl;
        return 1;
    }

    try {
        stoi(argv[1]);
    }
    catch (std::exception&) {
        std::cout << "usage: " << argv[0] << " port" << std::endl;
        return 1;
    }

    int server_port = stoi(argv[1]);
    Server s(server_port);
    if (!s.openServerSocketAndBindPort()) {
        perror("server could not connect");
        return 1;
    }
    if (!s.listenForClients()) {
        perror("could not listen for clients");
        return 2;
    }
    // this loop for each client
    while (true) {     
        int client_sock_fd = s.acceptClient();
        if (!client_sock_fd) {
            perror("could not accept client");
            continue;
        }

        DefaultIO* dio = new SocketIO(client_sock_fd);
        thread(handle_client, dio).detach();// run in parallel
    }

    s.closeServerSock();
    return 0;
}