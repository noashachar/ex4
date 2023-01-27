//
// Created by noash on 14/12/2022.
//

#ifndef EX2_UTILS_H
#define EX2_UTILS_H

#include <string>
#include <vector>
#include "distances.h"

DistanceCalculator* createDistCalc(std::string &name) ;
bool is_legal(std::vector<std::vector<double>>& f, std::vector<std::string>& s);
bool is_legalPred(std::vector<std::vector<double>> f);
//is this necessary?
std::vector<std::string> splitBy(const std::string &s, char delimiter);

#endif //EX2_UTILS_H
