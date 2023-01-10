//
// Created by noash on 10/01/2023.
//

#ifndef EX4_CMDCLASSIFY_H
#define EX4_CMDCLASSIFY_H

#include "Command.h"

using namespace std;

class CmdClassify : public Command {
public:
    CmdClassify(DefaultIO* dio) : Command(dio, "classify data") {}
    void execute();
};


#endif //EX4_CMDCLASSIFY_H
