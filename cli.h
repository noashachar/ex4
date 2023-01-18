#ifndef EX3_cli_H
#define EX3_cli_H

#include <sstream>
#include "Command.h"
#include "CmdAlgoSettings.h"
#include "CmdClassify.h"
#include "CmdDisplayResults.h"
#include "CmdDownloadResults.h"
#include "CmdUploadCsv.h"
#include "DefaultIO.h"
#include "knn.h"


#define NUM_COMMANDS 5

class CLI {
private:
    Command* commands[NUM_COMMANDS];
    DefaultIO* dio;
    Knn* knn;

    // todo add members here:
    //  metric, k
    //  vectors train_X, train_y (which the client sent in csv)
    //  vectors uploaded_X (which the client sent in csv)

public:
    CLI(DefaultIO* dio);

    ~CLI();

    void start();
};