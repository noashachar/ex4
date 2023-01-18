//
// Created by noash on 10/12/2022.
//


#ifndef EX2_KNN_H
#define EX2_KNN_H

#include <string>
#include "distances.h"

class Knn {
    protected:
        int knnK;
        std::vector<std::vector<double>> knnX;
        std::vector<std::string> knnY;
        DistanceCalculator *dis;
        std::vector<double> t;
        std::vector<std::vector<double>> unknnX;
        std::vector<std::string> pred;
    public:
    Knn();
    Knn(int k, std::vector<std::vector<double>> &X,std::vector<std::string> &y, DistanceCalculator *distance, std::vector<double> input_vec);
    Knn(std::vector<std::vector<double>> &X,std::vector<std::string> &y);
    void unclass(std::vector<std::vector<double>> &unknnX);
    void setPred(std::vector<std::string> &y);
    void setdis(DistanceCalculator *distance);
    void setK(int k);
    std::vector<std::string> getPred();
    string get_dis_name();
    int getK();
    void dataKnn(std::vector<std::vector<double>> &X,std::vector<std::string> &y);
    void prepareKnn(int k, DistanceCalculator *distance, std::vector<double> &input_vec);
    std::vector<double> getDistances();
    vector<double> Knn::getDistances(int num);
    std::vector<std::string> neighborsLabels(std::vector<double> distances);
    std::string getBetterLbels(std::vector<std::string> neighborsLabels);
};

#endif //EX2_KNN_H