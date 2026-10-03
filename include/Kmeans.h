#ifndef KMEANS_H
#define KMEANS_H

#include "data.h"
#include "cluster.h"
#include "Initializer.h"

#include <bits/stdc++.h>

using namespace std;

class KMeans
{
private:
    DataSet& data;
    int k;
    int maxIterations;
    double tolerance;

    Initializer* initializer;

    vector<Cluster> clusters;

public:
    KMeans(DataSet& d, int k, Initializer* initializer,
           int maxIterations = 100, double tolerance = 0.000001);

    void fit();

    void assignPoints();
    void updateCentroids();

    bool hasConverged(const vector<DataPoint>& oldCentroids) const;

    const vector<Cluster>& getClusters() const;
};

#endif
