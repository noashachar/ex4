//
// Created by noash on 10/01/2023.
//

#ifndef EX4_CMDALGOSETTINGS_H
#define EX4_CMDALGOSETTINGS_H

#include "Command.h"



class CmdAlgoSettings : public Command {
public:
    CmdAlgoSettings(DefaultIO* dio, Knn* knn) : Command(dio, "algorithm settings", knn) {}
    void execute();
};


#endif //EX4_CMDALGOSETTINGS_H
