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
    this->dio = dio;
    commands[0] = new CmdAlgoSettings(dio);
    commands[1] = new CmdClassify(dio);
    commands[2] = new CmdDisplayResults(dio);
    commands[3] = new CmdDownloadResults(dio);
    commands[4] = new CmdUploadCsv(dio);
}

CLI::~CLI() {
    for (int i = 0; i < NUM_COMMANDS; i++) {
        delete commands[i];
    }
    delete dio;
}

void CLI::start() {
    dio->write("Welcome to the KNN Classifier Server. Please choose an option:\n");
    for (int i = 0; i < NUM_COMMANDS; i++) {
        ostringstream s_stream;
        s_stream << i + 1 << ". " << commands[i]->getDescription() << endl;
        dio->write(s_stream.str());
    }
    dio->write("8. exit\n");

    // todo here we should loop:
    // loop:
    //     int number = stoi(dio->read());
    //     commands[number]->execute();

}
};