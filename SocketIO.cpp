//
// Created by noash on 10/01/2023.
//

#include "SocketIO.h"

// for sleep
#include <chrono>
#include <thread>

using namespace std;

SocketIO::SocketIO(int client_sock_fd)
{
    this->client_sock_fd = client_sock_fd;
}

SocketIO::~SocketIO()
{
    int result = close(client_sock_fd);
    if (result < 0)
    {
        perror("could not close socket with client");
    }
}

string SocketIO::read()
{
    char buffer[4096];

    int read_bytes = recv(client_sock_fd, buffer, sizeof(buffer), 0);

    if (read_bytes <= 0)
    {
        throw SocketIoConnectionEnded();
    }

    string reply(buffer);
    return reply;
}

void SocketIO::write(string msg)
{
    sendGuard.lock();

    // the +1 is essential, all messages must end with \0
    if (send(client_sock_fd, msg.c_str(), msg.length() + 1, 0) < 0)
    {
        perror("Send failed");
        sendGuard.unlock();
        throw SocketIoConnectionEnded();
    }

    // to disable msg batching (Nagle's Algorithm)
    std::this_thread::sleep_for(std::chrono::milliseconds(150));

    sendGuard.unlock();
}

const char *SocketIoConnectionEnded::what() const throw()
{
    const static char *msg = (char *)"client disconnected";
    return msg;
}