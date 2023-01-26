#include <sstream>

#include "Command.h"
#include "CmdAlgoSettings.h"
#include "CmdClassify.h"
#include "CmdDisplayResults.h"
#include "CmdDownloadResults.h"
#include "CmdUploadCsv.h"
#include "cli.h"
#include "DefaultIO.h"
#include "knn.h"

using namespace std;

#define NUM_COMMANDS 5

CLI::CLI(DefaultIO *dio)
{
    knn = new Knn();
    this->dio = dio;
    commands[0] = new CmdUploadCsv(dio, knn);
    commands[1] = new CmdAlgoSettings(dio, knn);
    commands[2] = new CmdClassify(dio, knn);
    commands[3] = new CmdDisplayResults(dio, knn);
    commands[4] = new CmdDownloadResults(dio, knn);
}

CLI::~CLI()
{
    for (int i = 0; i < NUM_COMMANDS; i++)
    {
        delete commands[i];
    }
    delete dio;
    delete knn;
}

void CLI::start()
{
    while (true)
    {
        ostringstream s_stream;
        s_stream << "Welcome to the KNN Classifier Server. Please choose an option:\n";

        for (int i = 0; i < NUM_COMMANDS; i++)
        {
            s_stream << (i + 1) << ". " << commands[i]->getDescription() << "\n";
        }
        s_stream << "8. exit";
        dio->write(s_stream.str());

        string user_input = dio->read();
        int user_number;

        try
        {
            user_number = stoi(user_input);
        }
        catch (std::exception &)
        {
            dio->write("invalid option.");
            continue;
        }

        // if (user_number == 636)
        // {
        //     stringstream ss;
        //     ss << "the size of my X is " << knn->getknnX().size() << "\n";
        //     ss << "the size of my y is " << knn->getknnY().size() << "\n";
        //     ss << "the size of my  is test is " << knn->getunknnX().size();
        //     ;
        //     dio->write(ss.str());
        //     continue;
        // }

        if (user_number <= 0 || user_number > NUM_COMMANDS)
        {
            dio->write("invalid option.");
            continue;
        }

        commands[user_number - 1]->execute();
    }
}
