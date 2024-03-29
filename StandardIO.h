//
// Created by noash on 10/01/2023.
//

#ifndef EX4_STANDARDIO_H
#define EX4_STANDARDIO_H

#include <string>
#include "DefaultIO.h"

class StandardIO : public DefaultIO {
public:
    std::string read() override;
    void write(std::string msg) override;
};

#endif //EX4_STANDARDIO_H
