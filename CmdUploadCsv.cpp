//
// Created by noash on 10/01/2023.
//

#include "CmdUploadCsv.h"
#include "utils.h"

void CmdUploadCsv::execute(){
    dio->write("Please upload your local train CSV file.");
    ostringstream s_stream;
    path = dio->read()
    zug = readFileToVectors(path);
    auto X = zug.first;
    auto y = zug.second;
    if (!illegal(X, y)) {
        s_stream.clear();
        s_stream <<"invalid input\n"
        dio->write(s_stream.str());
    }
    else{
    Knn->dataKnn(&X, &y);
    s_stream<<"Upload complete\n"<<"Please upload your local test CSV file.\n";
    dio->write(s_stream.str());
    path = dio->read()
    zug = readFileToVectors(path);
    auto PREX = zug.first;
    if (!illegalPred(X)) {
        s_stream.clear();
        s_stream <<"invalid input\n"
        dio->write(s_stream.str());
    }
    else{
        knn->unclass(std::vector<std::vector<double>> &unknnX);
        dio->write("Upload complete\n");
        }
    }
}
