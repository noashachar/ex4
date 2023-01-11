#include <sstream>

#include "Command.h"
#include "CmdAlgoSettings.h"
#include "CmdClassify.h"
#include "CmdDisplayResults.h"
#include "CmdDownloadResults.h"
#include "CmdUploadCsv.h"

#include "DefaultIO.h"
#include "StandardIO.h"

using namespace std;

#define NUM_COMMANDS 5

class CLI {
private:
    Command* commands[NUM_COMMANDS];
    DefaultIO* dio;

public:
    CLI(DefaultIO* dio) {
        this->dio = dio;
        commands[0] = new CmdAlgoSettings(dio);
        commands[1] = new CmdClassify(dio);
        commands[2] = new CmdDisplayResults(dio);
        commands[3] = new CmdDownloadResults(dio);
        commands[4] = new CmdUploadCsv(dio);
    }

    ~CLI() {
        for (int i = 0; i < NUM_COMMANDS; i++) {
            delete commands[i];
        }
        delete dio;
    }

    void start() {
        dio->write("Welcome to the KNN Classifier Server. Please choose an option:\n");
        for (int i = 0; i < NUM_COMMANDS; i++) {
            ostringstream s_stream;
            s_stream << i + 1 << ". " << commands[i]->getDescription() << endl;
            dio->write(s_stream.str());
        }
        dio->write("8. exit\n");
    }
};

int main() {
    StandardIO standardIo;
    CLI cli(&standardIo);
    cli.start();
}