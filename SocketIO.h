//
// Created by noash on 10/01/2023.
//

#ifndef EX4_SOCKETIO_H
#define EX4_SOCKETIO_H

#include <string>
#include "DefaultIO.h"
#include "server.h"
#include <mutex>


class SocketIO : public DefaultIO
{
private:
    int client_sock_fd;
    std::mutex sendGuard;

public:
    SocketIO(int client_sock_fd);
    ~SocketIO();
    std::string read();
    void write(std::string msg);
};

struct SocketIoConnectionEnded : public std::exception
{
    const char *what() const throw();
};

#endif // EX4_SOCKETIO_H
