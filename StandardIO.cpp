//
// Created by noash on 10/01/2023.
//

#include "StandardIO.h"
#include <iostream>

using namespace std;

// read line from user
string StandardIO::read() {
    string text;
    getline(cin, text);
    return text;
}

// write line to user
void StandardIO::write(string msg) {
    cout << msg << endl;
}