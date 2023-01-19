//
// Created by noash on 10/01/2023.
//

#ifndef EX4_COMMAND_H
#define EX4_COMMAND_H

#include <sstream>
#include <string>
#include "DefaultIO.h"
#include <iostream>
#include "knn.h"
#include <vector>

class Command {
protected:
    DefaultIO* dio;
    Knn* knn;
private:
    std::string description;
public:
    std::string getDescription();
    Command(DefaultIO* dio, std::string description, Knn* knn);
    virtual void execute() = 0;

    // this doesn't delete dio, because many commands share the same dio;
    // also the commands' parent share the same dio. hence the parent will delete it.
    //same in knn
    virtual ~Command() {}
};


#endif //EX4_COMMAND_H
