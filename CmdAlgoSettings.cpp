//
// Created by noash on 10/01/2023.
//

#include "CmdAlgoSettings.h"

CmdAlgoSettings::execute(){
    int k = knn->getK();
    string n = knn->get_dis_name();
    size_t start = 0, end;
    dio->write("the current KNN parameters arr k = "<< k <<", distance metric = "<< n <<endl);
    ostringstream s_stream;
    string text = dio->read();
    if(text!="\n"){
        endtext = text.find("   ", start)
        try{
            int newK = stoi(text.substr(start, end - start));
        }
        catch{
            s_stream<<"invalid value for K\n";
        }
        try{
            start = end + 1;
            int newK = stoi(text.substr(start, end - start));
        }
        catch{
            s_stream<<"invalid value for metric\n";
        }
        dio->write(s_stream.str());
    }
}
