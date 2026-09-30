#include "include/cluster.h"
#include "Exceptions.h"
#include <bits/stdc++.h>

Cluster :: Cluster(const DataPoint &c): centroid(c){}

void Cluster ::add(const DataPoint &point){
    if (!members.empty() && point.getdim() != members[0].getdim())
    {
        throw DimensionMismatchException();
    }
    members.push_back(point);
} 

void Cluster :: clear(){
    members.clear();
}

void Cluster :: updateCentroid(){
    int dim=members[0].getdim();
    vector<double>mean(dim,0);
    for(const DataPoint &d:members){
        const vector<double>&values=d.getvalues();
        for(int i=0;i<dim;i++){
            mean[i]+=values[i];
        }
        for(int i=0;i<dim;i++){
            mean[i]=mean[i]/members.size();
        }
        centroid =DataPoint(mean);
    }
}

const DataPoint& Cluster :: getCentroid() const{
    return centroid;
}

const vector<DataPoint>& Cluster :: getMembers() const{
    return members;
}

int Cluster:: getSize() const{
    return members.size();
}