//
// Created by noash on 10/01/2023.
//

#ifndef EX4_CMDALGOSETTINGS_H
#define EX4_CMDALGOSETTINGS_H

#include "Command.h"

using namespace std;

class CmdAlgoSettings : public Command {
public:
    CmdAlgoSettings(DefaultIO* dio) : Command(dio, "algorithm settings") {}
    void execute();
};


#endif //EX4_CMDALGOSETTINGS_H
