#include <iostream>
#include <string>
#include <vector>
#include <algorithm>    // sort
#include <unordered_map>
#include "knn.h"
using namespace std;

//init func of knn, inherited from DistanceVector with the input vector
Knn::Knn(int k, vector<vector<double>> &X,vector<string> &y, DistanceCalculator *distance, vector<double> input_vec){
    knnK = k;
    knnX = X;
    knnY = y;
    dis = distance;
    t = input_vec;
}

Knn::Knn(vector<vector<double>> &X,vector<string> &y){
    knnX = X;
    knnY = y;
}

Knn::Knn(){
    dis = new EuclideanDistanceCalculator;
    knnK=5;
}

void Knn::prepareKnn(int k, DistanceCalculator *distance, vector<double> &input_vec){
    delete dis;
    knnK = k;
    dis = distance;
    t = input_vec;
}

void Knn::dataKnn(vector<vector<double>> &X,vector<string> &y){
    knnX = X;
    knnY = y;
}

void Knn::unclass(std::vector<std::vector<double>> &unknnX){
    this->unknnX = unknnX;
}

void Knn::setPred(std::vector<std::string> &y){
    this->pred = y;
}
void Knn::setdis(DistanceCalculator *distance){
    delete dis;
    this->dis = distance;
}
void Knn::setK(int k){
    knnK = k;
}

std::vector<std::string> Knn::getPred(){
    return this->pred;
}
string Knn::get_dis_name(){
        return dis->name;
}

int Knn::getK(){
    return knnK;
}

std::vector<std::vector<double>> Knn::getknnX(){
    return knnX;
}

std::vector<std::string> Knn::getknnY() {
    return knnY;
}

std::vector<std::vector<double>> Knn::getunknnX(){
    return unknnX;
}

//return Distances between self vector to data vectors as a arr
//by the name of the distance func that required from the terminal
vector<double> Knn::getDistances(){
    vector<double> distances;
    for(vector<double>x: knnX ){
        double dist = dis->calculateDistance(x, t);
        distances.push_back(dist);
    }
     return distances;
}

vector<double> Knn::getDistances(int num){
    vector<double> predvec = unknnX[num];
    vector<double> distances;
    for(vector<double>x: knnX ){
        double dist = dis->calculateDistance(x, predvec);
        distances.push_back(dist);
    }
     return distances;
}

//return vector of the k tags that nearest to self.vec  
vector<string> Knn::neighborsLabels(vector<double>  distances){
     vector<int> indexes;
     for (int i=0;i<knnY.size();i++){
         indexes.push_back(i);
     }
    //inner func to sort by comparing the distances
     auto compare = [&](int i, int j){
        if(distances[i]<distances[j]){
            return true;
        }
         return false;
     };
     sort(indexes.begin(), indexes.end(), compare);
     
     //push to vector the k tags that nearest to self.vec 
     vector<string> neighborsLabels;

     if (knnK > indexes.size()) {
         puts("warning: k was too big; reduced to size of input");
         knnK = indexes.size();
     }

     for(int i=0;i<knnK;i++){
         neighborsLabels.push_back(knnY[indexes[i]]);
     }
     return neighborsLabels;
}

//return the tag that appeared the most times
string Knn::getBetterLbels(vector<string> neighborsLabels){
     unordered_map<string, int> umap;
    for(string& label:neighborsLabels){
        // If key not found in map iterator
        if (umap.find(label) == umap.end()){
            umap[label]=1;
        }
        //if key found add +1
        else{
            umap[label]+=1;
        }
    }

     // find the maxValue value
     int maxValue=0;
     for (auto &kv : umap){
         if (maxValue < kv.second){
             maxValue=kv.second;
         }
     }
     
     for(auto &kk :umap){
         if (kk.second==maxValue){
             return kk.first;
         }
     }
    
     return "-1"; // will not happen
}
