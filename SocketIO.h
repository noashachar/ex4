//
// Created by noash on 10/01/2023.
//

#ifndef EX4_SOCKETIO_H
#define EX4_SOCKETIO_H


#include <string>
#include "DefaultIO.h"
#include "server.h"

class SocketIO : public DefaultIO {
private:
    Server *server;
    int client_sock_fd;
public:
    SocketIO(Server* server, int client_sock_fd) {
        this->server = server;
        this->client_sock_fd = client_sock_fd;
    }

    ~SocketIO() {
        this->server->closeClientSock(client_sock_fd);
    }

    std::string read();
    void write(std::string);
};



#endif //EX4_SOCKETIO_H
