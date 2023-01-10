//
// Created by noash on 10/01/2023.
//

#ifndef EX4_CMDUPLOADCSV_H
#define EX4_CMDUPLOADCSV_H

#include "Command.h"
#include "StandardIO.h"

using namespace std;

class CmdUploadCsv : public Command {
public:
    CmdUploadCsv(DefaultIO* dio) : Command(dio, "upload an unclassified csv data file") {}
    void execute();
};

#endif //EX4_CMDUPLOADCSV_H
