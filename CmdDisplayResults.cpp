//
// Created by noash on 10/01/2023.
//
#include "Command.h"
#include "CmdDisplayResults.h"

void CmdDisplayResults::execute(){
    ostringstream s_stream;
    if(knn->getknnX().size()<1 || knn->getunknnX().size()<1){
        s_stream<<"please upload data"<< endl;
    }
    else if(knn->getPred().size()<1){
       s_stream<<"please classify the data"<< endl;
    }
    else{
    for (int i = 0; i < knn->getPred().size() ; i++) {
        s_stream << i + 1 << "  " << knn->getPred()[i] << endl;
    }
    s_stream<<"Done\n";
    }
    dio->write(s_stream.str());
    string end = dio->read();
    while (end=="\n"){
        end = dio->read();
    }
}