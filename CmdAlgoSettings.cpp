//
// Created by noash on 10/01/2023.
//
#include "utils.h"
#include "CmdAlgoSettings.h"

using namespace std;

void CmdAlgoSettings::execute() {
    int k = knn->getK();
    string n = knn->get_dis_name();

    ostringstream sStream;
    sStream << "the current KNN parameters arr k = " << k << ", distance metric = " << n;
    dio->write(sStream.str());

    string text = dio->read();

    if (text.empty()) return;

    int newK;
    string name;

    size_t start = 0, end;
    end = text.find(' ', start);
    try {
        newK = stoi(text.substr(start, end - start));
        knn->setK(newK);
    }
    catch (std::exception &e) {
        dio->write("invalid value for K");
    }

    start = end + 1;
    name = text.substr(start, end - start);
    DistanceCalculator *dc = createDistCalc(name);
    if (dc == nullptr) {
        dio->write("invalid value for metric");
        delete dc;
    } else {
        knn->setdis(dc);
    }
}
