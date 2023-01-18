#include <sstream>

#include "Command.h"
#include "CmdAlgoSettings.h"
#include "CmdClassify.h"
#include "CmdDisplayResults.h"
#include "CmdDownloadResults.h"
#include "CmdUploadCsv.h"

#include "DefaultIO.h"

using namespace std;

#define NUM_COMMANDS 5


CLI::CLI(DefaultIO* dio) {
     //  todo - the commands' constructors should accept more things
    // for example, CmdClassify should accept a ptr to the vectors,
    // and algoSettings should accepts pointers to metric and k
    this->knn = new knn();
    this->dio = dio;
    commands[0] = new CmdUploadCsv(dio,knn);
    commands[1] = new CmdAlgoSettings(dio,knn);
    commands[2] = new CmdClassify(dio,knn);
    commands[3] = new CmdDisplayResults(dio,knn);
    commands[4] = new CmdDownloadResults(dio,knn);
}

CLI::~CLI() {
    for (int i = 0; i < NUM_COMMANDS; i++) {
        delete commands[i];
    }
    delete dio;
    delete knn;
}

void CLI::start() {
    int number = 0
    ostringstream s_stream;
    while(true){
    s_stream<<("Welcome to the KNN Classifier Server. Please choose an option:\n");
    for (int i = 0; i < NUM_COMMANDS; i++) {
        s_stream << i + 1 << ". " << commands[i]->getDescription() << endl;
    }
    s_stream<<"8. exit\n";
    dio->write(s_stream.str());

    // todo here we should loop:
    // loop:
    //     int number = stoi(dio->read())+1;
    //     commands[number]->execute();
    
    number = stoi(dio->read())-1;
    if (number == 7){
        break;
    }
    commands[number]->execute();
    }

}
