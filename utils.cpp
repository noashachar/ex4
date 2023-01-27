//
// Created by noash on 14/12/2022.
//

#include "utils.h"

#include <vector>


using namespace std;

DistanceCalculator* createDistCalc(string& name) {
    if (name == "AUC") {
        return new EuclideanDistanceCalculator;
    }
    if (name == "MAN") {
        return new ManhattanDistanceCalculator;
    }
    if (name == "CHB") {
        return new ChebyshevDistanceCalculator;
    }
    if (name == "CAN") {
        return new CanberraDistanceCalculator;
    }
    if (name == "MIN") {
        return new MinkowskiDistanceCalculator(3); // I chose this pow_num.
    }
    return nullptr;
}



bool is_legal(vector<vector<double>>& f, vector<string>& s) {
    if (f.size() != s.size()) {
        return false;
    }
    if (f.size() < 1) {
        return false;
    }
    unsigned int size = f[0].size();
    for (auto& i : f) {
        if (i.size() != size) {
            return false;
        }
    }
    return true;
}
bool is_legalPred(vector<vector<double>> f) {
    if (f.size() < 1) {
        return false;
    }
    unsigned int size = f[0].size();
    for (auto& i : f) {
        if (i.size() != size) {
            return false;
        }
    }
    return true;
}


vector<string> splitBy(const string &s, char delimiter)
{
    size_t pos_start = 0, pos_end;
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + 1;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}