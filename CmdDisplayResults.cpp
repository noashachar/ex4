//
// Created by noash on 10/01/2023.
//

#include "CmdDisplayResults.h"

CmdDisplayResults::execute(){
    ostringstream s_stream;
    if(knn->knnX.size()<1 || knn->unknnX.size()<1){
        s_stream<<"please upload data"<< endl;
    }
    else if(knn->pred.size()<1){
       s_stream<<"please classify the data"<< endl;
    }
    else{
    for (int i = 0; i < knn->pred.size() ; i++) {
        s_stream << i + 1 << "  " << knn->pred[i] << endl;
    }
    s_stream<<"Done\n";
    }
    dio->write(s_stream.str());
    string end = dio->read();
    while (end=="\n"){
        end = dio->read();
    }
}