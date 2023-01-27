//
// Created by noash on 10/01/2023.
//
#include "utils.h"
#include "CmdUploadCsv.h"
#include "utils.h"

void CmdUploadCsv::execute()
{
    dio->write("Please upload your local train CSV file.");
    string path = dio->read();

    // read the file
    dio->write("!upload:" + path);

    vector<string> lines;
    string line;
    while (line = dio->read(), line != "!done")
    {
        lines.push_back(line);
        // cout << "got this line from file: " << line << endl;
    }

    vector<vector<double>> X;
    vector<string> y;

    bool linesWereOk = true;

    for (const auto &line : lines)
    {
        auto parts = splitBy(line, ',');

        vector<double> resVec;
        for (size_t i = 0; i < parts.size() - 1; i++)
        {
            try
            {
                resVec.push_back(stod(parts[i]));
            }
            catch (std::invalid_argument &)
            {
                linesWereOk = false;
            }
        }

        X.push_back(resVec);
        y.push_back(parts[parts.size() - 1]);
    }

    if (!linesWereOk || !is_legal(X, y))
    {
        dio->write("invalid input");
        return;
    }

    knn->dataKnn(X, y);

    dio->write("Upload complete");
    dio->write("Please upload your local test CSV file.");

    path = dio->read();


    ////////////////////////////////
    dio->write("!upload:" + path);

    lines.clear();
    while (line = dio->read(), line != "!done")
    {
        lines.push_back(line);
    }

    vector<vector<double>> preX;

    linesWereOk = true;

    for (const auto &line : lines)
    {
        auto parts = splitBy(line, ',');

        vector<double> resVec;
        for (size_t i = 0; i < parts.size(); i++)
        {
            try
            {
                resVec.push_back(stod(parts[i]));
            }
            catch (std::invalid_argument &)
            {
                linesWereOk = false;
            }
        }

        preX.push_back(resVec);
    }

    if (!linesWereOk || !is_legalPred(preX))
    {
        dio->write("invalid input");
        return;
    }

    knn->unclass(preX);
    dio->write("Upload complete");
}
