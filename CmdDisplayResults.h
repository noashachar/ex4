//
// Created by noash on 10/01/2023.
//

#ifndef EX4_CMDDISPLAYRESULTS_H
#define EX4_CMDDISPLAYRESULTS_H

#include "Command.h"

class CmdDisplayResults : public Command {
public:
    CmdDisplayResults(DefaultIO* dio, Knn* knn) : Command(dio, "display results", knn) {}
    void execute();
};


#endif //EX4_CMDDISPLAYRESULTS_H
