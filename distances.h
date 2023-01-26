#ifndef EX2_DISTANCES_H
#define EX2_DISTANCES_H

#include <string>
#include <vector>

void powVector(std::vector<double> &p, double pow_num);

double sumVector(std::vector<double> &vec2);

std::vector<double> makeDiffrencesVector(std::vector<double> &p, std::vector<double> &q);

// --------

class DistanceCalculator {
public:
    std::string name;
    virtual double calculateDistance(std::vector<double> &v1, std::vector<double> &v2) = 0;
    virtual ~DistanceCalculator() = default;
};

class MinkowskiDistanceCalculator : public DistanceCalculator {
public:
    int pow_num;
    //std::string name = "MIN";
    double calculateDistance(std::vector<double> &v1, std::vector<double> &v2) override;
    explicit MinkowskiDistanceCalculator(int pow_num) { this->pow_num = pow_num; this->name="MIN";}
};

class CanberraDistanceCalculator : public DistanceCalculator {
public:
    //std::string name = "CAN";
    double calculateDistance(std::vector<double> &v1, std::vector<double> &v2) override;
    explicit CanberraDistanceCalculator(){this->name="CAN";}
};

class ChebyshevDistanceCalculator : public DistanceCalculator {
public:
    //std::string name = "CHB";
    double calculateDistance(std::vector<double> &v1, std::vector<double> &v2) override;
    explicit ChebyshevDistanceCalculator(){this->name="CHB";}
};

class EuclideanDistanceCalculator : public DistanceCalculator {
public:
    //std::string name = "AUC";
    double calculateDistance(std::vector<double> &v1, std::vector<double> &v2) override;
    explicit EuclideanDistanceCalculator(){this->name="AUC";}
};


class ManhattanDistanceCalculator : public DistanceCalculator {
public:
    //std::string name = "MAN";
    double calculateDistance(std::vector<double> &v1, std::vector<double> &v2) override;
    explicit ManhattanDistanceCalculator(){this->name="MAN";}
};

#endif // EX2_DISTANCES_H
