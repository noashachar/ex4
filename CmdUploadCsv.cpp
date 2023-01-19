//
// Created by noash on 10/01/2023.
//
#include "utils.h"
#include "CmdUploadCsv.h"
#include "utils.h"

void CmdUploadCsv::execute(){
    std::pair<vector<vector<double>>, vector<string>> zug;
    ostringstream s_stream;
    s_stream<<"Please upload your local train CSV file.\n";
    dio->write(s_stream.str());
    s_stream.str("");
    string path = dio->read();
    zug = readFileToVectors(path);
    vector<vector<double>> X = zug.first;
    vector<string> y = zug.second;
    if (!illegal(X, y)) {
        s_stream.str("");
        s_stream <<"invalid input\n";
        dio->write(s_stream.str());
    }
    else{
    knn->dataKnn(X, y);
    s_stream<<"Upload complete\n"<<"Please upload your local test CSV file.\n";
    dio->write(s_stream.str());
    path = dio->read();
    zug = readFileToVectors(path);
    vector<vector<double>> preX = zug.first;
    if (!illegalPred(preX)) {
        s_stream.str("");
        s_stream <<"invalid input\n";
        dio->write(s_stream.str());
    }
    else{
        knn->unclass(preX);
        dio->write("Upload complete\n");
        }
    }
}
