#ifndef CLUSTER_H
#define CLUSTER_H

#include "data.h"
#include <bits/stdc++.h>


class Cluster
{
private:
    DataPoint centroid;
    vector<DataPoint> members;

public:
    Cluster(const DataPoint& c);

    void add(const DataPoint& point);
    void clear();
    void updateCentroid();

    const DataPoint& getCentroid() const;
    const vector<DataPoint>& getMembers() const;

    int getSize() const;
};

#endif

