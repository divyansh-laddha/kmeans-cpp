#ifndef CLUSTERINGMETRICS_H
#define CLUSTERINGMETRICS_H

#include "cluster.h"
using namespace std;

class ClusteringMetrics{
public:
    double inertia(const vector<Cluster>& clusters);
    double silhouette(const vector<Cluster>& clusters);
};

#endif
