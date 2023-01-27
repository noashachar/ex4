//
// Created by noash on 10/01/2023.
//
#include "Command.h"
#include "CmdDisplayResults.h"

void CmdDisplayResults::execute()
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

    std::ostringstream s_stream;

    for (int i = 1; i <= knn->getPred().size(); i++)
    {
        s_stream << i << "  " << knn->getPred()[i - 1] << "\n";
    }
    s_stream << "Done";

    dio->write(s_stream.str());
}