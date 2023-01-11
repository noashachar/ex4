//
// Created by noash on 10/01/2023.
//

#include "SocketIO.h"

using namespace std;

string SocketIO::read() {
    return server->receive(client_sock_fd, 4096);
}

void SocketIO::write(string msg) {
    server->sendData(client_sock_fd, msg);
}
