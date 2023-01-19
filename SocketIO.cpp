//
// Created by noash on 10/01/2023.
//

#include "SocketIO.h"

using namespace std;

SocketIO::SocketIO(int client_sock_fd) {
    this->client_sock_fd = client_sock_fd;
}

SocketIO::~SocketIO() {
    int result = close(client_sock_fd);
    if (result < 0) {
        perror("could not close socket with client");
    }
}

string SocketIO::read() {
    char buffer[4096];
    string reply;
    int read_bytes = recv(client_sock_fd, buffer, sizeof(buffer), 0);
    reply = buffer;
    memset(buffer, 0, sizeof(buffer));
    if (read_bytes <= 0) {
        throw std::exception();
    }
    return reply;
}

bool SocketIO::write(string msg) {
        if (send(client_sock_fd, msg.c_str(), msg.length(), 0) < 0) {
        perror("Send failed :( ");
        return false;
    }

    return true;
}
