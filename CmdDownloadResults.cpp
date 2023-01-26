#include "CmdDownloadResults.h"
#include <thread>
#include <vector>

// called in separate thread - so send predsToSend by copy, not by ref!
void sendResultsToClient(DefaultIO *dio, std::vector<std::string> stringsToSend, std::string path)
{
    for (int i = 1; i <= stringsToSend.size(); i++)
    {
        ostringstream ss;
        ss << "$" << path << ": " << i << "  " << stringsToSend[i - 1];
        // $file.txt: this is a line for the file
        dio->write(ss.str());
    }
      
    // std::this_thread::sleep_for(std::chrono::seconds(1));

    dio->write("$" + path + ": " + "!done");
    // $file: !done
}

void CmdDownloadResults::execute()
{
    if (knn->getknnX().empty() || knn->getunknnX().empty())
    {
        dio->write("please upload data");
        return;
    }
    if (knn->getPred().empty())
    {
        dio->write("please classify the data");
        return;
    }

    dio->write("What do you want to name the file?");
    std::string path = dio->read();
    dio->write("!download:" + path);

    thread(sendResultsToClient, dio, knn->getPred(), path).detach();
}