#ifndef data_h
#define data_h

#include <bits/stdc++.h>
using namespace std;

class DataPoint{
    protected:
        vector<double>point;
    public:
        DataPoint(vector<double>&values);
        double dist_square(const DataPoint &other) const;
        void display_1() const;
        int getdim() const;
        vector<double> &getvalues() const;
};

class DataSet {
    protected:
        vector<DataPoint> points;
    public:
        void loadCSV(string filename);
        void display() const;
        vector<DataPoint>& getPoints() const;
};


#endif