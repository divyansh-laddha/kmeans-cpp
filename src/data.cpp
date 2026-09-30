#include <bits/stdc++.h>
#include "include/data.h"

class DataPoint{
    protected:
        vector<double>point;
    public:
        DataPoint(vector<double>&values){
            point=values;
        }
        double dist_square(const DataPoint &other) const{
            double dist=0;
            for(int i=0;i<point.size();i++){
                dist+= (point[i]-other.point[i])*(point[i]-other.point[i]);
            }
            return dist;
        }
        void display_1() const{
            cout << "(";

            for (int i = 0; i < point.size(); i++){
                cout << point[i];

                if (i != point.size() - 1){
                    cout << ", ";
                }
            }
            cout << ")" << endl;
        }
        int getdim() const{
            return point.size();
        }
        vector<double> getvalues() const{
            return point;
        }
};

class DataSet {
    protected:
        vector<DataPoint> points;
    public:
        void loadCSV(string filename){
            ifstream file(filename);

        if (!file.is_open())
            throw runtime_error("Unable to open CSV file");

        points.clear();

        string line;
        // skip header
        // getline reads line by line
        getline(file, line);

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);
            string value;

            vector<double> values;

            while (getline(ss, value, ','))
            {
                values.push_back(stod(value));
            }

            if (!values.empty())
                points.push_back(DataPoint(values));
        }

        file.close();
    }
        void display() const{
            for (const DataPoint& p : points){
                p.display_1();
            }
        };
        const vector<DataPoint>& getPoints() const{
            return points;
        }
};