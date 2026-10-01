#include "include/RandomInitializer.h"
#include "include/Exceptions.h"
#include <bits/stdc++.h>

using namespace std;

vector<DataPoint> RandomInitializer :: Initialise(DataSet &d,int k){
    const vector<DataPoint>points =d.getPoints();
    if(k<=0 || k>points.size()){
        throw InvalidKException();
    }
    vector<DataPoint>centroids;
    vector<int> indices;

    for (int i = 0; i < points.size(); i++){
        indices.push_back(i);
    }
    random_device rd;
    mt19937 generator(rd());

    shuffle(indices.begin(), indices.end(), generator);

    for (int i = 0; i < k; i++){
        centroids.push_back(points[indices[i]]);
    }
    return centroids;

}