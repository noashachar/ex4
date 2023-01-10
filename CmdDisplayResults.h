//
// Created by noash on 10/01/2023.
//

#ifndef EX4_CMDDISPLAYRESULTS_H
#define EX4_CMDDISPLAYRESULTS_H

#include "Command.h"

using namespace std;

class CmdDisplayResults : public Command {
public:
    CmdDisplayResults(DefaultIO* dio) : Command(dio, "display results") {}
    void execute();
};


#endif //EX4_CMDDISPLAYRESULTS_H
