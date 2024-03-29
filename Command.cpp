//
// Created by noash on 10/01/2023.
//

#include <sstream>
#include <iostream>
#include <string>
#include "knn.h"
#include <vector>
#include "Command.h"
using namespace std;

string Command::getDescription() {
    return this->description;
}

Command::Command(DefaultIO *dio, std::string description, Knn *knn) {
    this->dio = dio;
    this->description = description;
    this->knn = knn;
}