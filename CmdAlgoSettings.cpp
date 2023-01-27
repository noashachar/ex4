//
// Created by noash on 10/01/2023.
//
#include "utils.h"
#include "CmdAlgoSettings.h"
using namespace std;
void CmdAlgoSettings::execute()
{
    ostringstream s_stream;
    bool notOk = false;
    int k = knn->getK();
    string n = knn->get_dis_name();

    s_stream << "the current KNN parameters arr k = " << k << ", distance metric = " << n;

    size_t start = 0, end;
    dio->write(s_stream.str());
    s_stream.str("");
    string text = dio->read();

    if (text.empty()) return;

    if (text != "\n")
    {
        int newK;
        string name;
        end = text.find(" ", start);
        try
        {
            newK = stoi(text.substr(start, end - start));
            knn->setK(newK);
        }
        catch (std::exception &e)
        {
            s_stream << "invalid value for K";
            notOk = true;
        }
        try
        {
            start = end + 1;
            name = text.substr(start, end - start);
            s_stream << name << " " << endl;
            DistanceCalculator *dc = createDistCalc(name);
            if (dc == nullptr)
            {
                s_stream << "invalid value for metric";
                delete dc;
                notOk = true;
            }
            else
            {
                knn->setdis(dc);
            }
        }
        catch (std::exception &e)
        {
            s_stream << "invalid value for metric";
            notOk = true;
        }
        if (notOk)
        {
            dio->write(s_stream.str());
        }
    }
}
