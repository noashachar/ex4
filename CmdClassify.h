//
// Created by noash on 10/01/2023.
//

#ifndef EX4_CMDCLASSIFY_H
#define EX4_CMDCLASSIFY_H

#include "Command.h"



class CmdClassify : public Command {
public:
    CmdClassify(DefaultIO* dio, Knn* knn) : Command(dio, "classify data", knn) {}
    void execute();
};


#endif //EX4_CMDCLASSIFY_H
