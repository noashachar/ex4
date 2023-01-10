//
// Created by noash on 10/01/2023.
//

#include "Command.h"
using namespace std;

string Command::getDescription() {
    return this->description;
}

Command::Command(DefaultIO *dio, std::string description) {
    this->dio = dio;
    this->description = description;
}