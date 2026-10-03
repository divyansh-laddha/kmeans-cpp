#include <bits/stdc++.h>
#include "data.h"
#include "Exceptions.h"

DataPoint::DataPoint(vector<double>& values){
    point = values;
}

double DataPoint::dist_square(const DataPoint& other) const{
    double dist = 0;

    for(int i = 0; i < int(point.size()); i++){
        dist += (point[i] - other.point[i]) *
                (point[i] - other.point[i]);
    }

    return dist;
}

void DataPoint::display_1() const{
    cout << "(";

    for(int i = 0; i < int(point.size()); i++){
        cout << point[i];

        if(i != int(point.size() - 1)){
            cout << ", ";
        }
    }

    cout << ")" << endl;
}

int DataPoint::getdim() const{
    return point.size();
}

const vector<double>& DataPoint::getvalues() const{
    return point;
}

void DataSet::loadCSV(string filename){
    ifstream file(filename);

    if(!file.is_open()){
        throw ErrorFileOpening();
    }

    points.clear();

    string line;

    getline(file, line);

    while(getline(file, line)){
        if(line.empty()){
            continue;
        }

        stringstream ss(line);
        string value;
        vector<double> values;

        while(getline(ss, value, ',')){
            values.push_back(stod(value));
        }

        if(!values.empty()){
            points.push_back(DataPoint(values));
        }
    }

    file.close();
}

void DataSet::display() const{
    for(const DataPoint& p : points){
        p.display_1();
    }
}

const vector<DataPoint>& DataSet::getPoints() const{
    return points;
}

void DataSet::normalize(){
    if(points.empty()){
        return;
    }

    int dim = points[0].getdim();

    vector<double> minValues(dim);
    vector<double> maxValues(dim);

    for(int i = 0; i < dim; i++){
        minValues[i] = points[0].getvalues()[i];
        maxValues[i] = points[0].getvalues()[i];
    }

    for(const DataPoint& point : points){
        for(int i = 0; i < dim; i++){
            if(point.getvalues()[i] < minValues[i]){
                minValues[i] = point.getvalues()[i];
            }

            if(point.getvalues()[i] > maxValues[i]){
                maxValues[i] = point.getvalues()[i];
            }
        }
    }

    for(DataPoint& point : points){
        vector<double> values = point.getvalues();

        for(int i = 0; i < dim; i++){
            if(maxValues[i] == minValues[i]){
                values[i] = 0;
            }
            else{
                values[i] =
                    (values[i] - minValues[i]) /
                    (maxValues[i] - minValues[i]);
            }
        }

        point= values;
    }
}