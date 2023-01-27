//
// Created by noash on 10/01/2023.
//
#include "CmdClassify.h"


void CmdClassify::execute(){
    std::ostringstream s_stream;
    std::vector<double> dis;
    std::vector<std::string> k_tags;
    std::string prediction; 
    std::vector<std::string> pred;
    if( knn->getunknnX().size()<1){
        s_stream<<"please upload data";
    }
    else {
        s_stream<<"classifying data complete";
        for (int i = 0; i < knn->getunknnX().size() ; i++) {
            dis = knn->getDistances(i);
            k_tags = knn->neighborsLabels(dis);
            prediction = knn->getBetterLbels(k_tags);
            pred.push_back(prediction);
            knn->setPred(pred);
            }
    }
    dio->write(s_stream.str());
}