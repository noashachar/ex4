//
// Created by noash on 10/01/2023.
//

#ifndef EX4_SOCKETIO_H
#define EX4_SOCKETIO_H


#include <string>
#include "DefaultIO.h"

class SocketIO : public DefaultIO {
public:
    std::string read();
    void write(std::string);
};



#endif //EX4_SOCKETIO_H
