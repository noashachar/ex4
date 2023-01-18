//
// Created by noash on 10/01/2023.
//

#include "CmdClassify.h"

CmdClassify::execute(){
    ostringstream s_stream;
    vector<double> dis;
    vector<string> k_tags
    string prediction; 
    vector<string> pred;
    if( knn->unknnX.size()<1){
        s_stream<<"please upload data"<< endl;
    }
    else {
        s_stream<<"classifying data complete\n";
        for (int i = 0; i < knn->unknnX.size() ; i++) {
            dis = knn->getDistances( knn->unknnX[i]);
            k_tags = knn->neighborsLabels(dis);
            prediction = knn->getBetterLbels(k_tags);
            pred.push(prediction);
            knn->setPred(pred);
            }
    }
    dio->write(s_stream.str());
}