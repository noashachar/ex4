//
// Created by noash on 10/01/2023.
//

#ifndef EX4_CMDDOWNLOADRESULTS_H
#define EX4_CMDDOWNLOADRESULTS_H


#include "Command.h"
#include "knn.h"

using namespace std;

class CmdDownloadResults : public Command {
public:
    CmdDownloadResults(DefaultIO* dio, Knn* knn) : Command(dio, "download results", knn) {}
    void execute();
};


#endif //EX4_CMDDOWNLOADRESULTS_H
