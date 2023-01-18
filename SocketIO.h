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
    int client_sock_fd;
public:
    SocketIO(int client_sock_fd);
    ~SocketIO();
    std::string read();
    bool write(std::string& msg);
};



#endif //EX4_SOCKETIO_H
