// #include <bits/stdc++.h>
// #include "KPlusInitializer.h"
// #include "Exceptions.h"

// using namespace std;

// vector<DataPoint> KPlusInitializer :: Initialise(DataSet &d,int k){
//     const vector<DataPoint>points =d.getPoints();
//     if(points.empty()){
//         throw EmptyDataSet();
//     }
//     if(k<=0 || k>points.size()){
//         throw InvalidKException();
//     }
//     vector<DataPoint>centroids;

//     random_device rd;
//     mt19937 generator(rd());

//     uniform_int_distribution<int> index(0,points.size()-1);
//     int first=index(generator);
//     centroids.push_back(points[first]);

//     while(centroids.size()<k){
//         vector<double>distances(points.size(),0);
//         double total=0;
//         for(int i=0;i<points.size();i++){
//             double mindist=points[i].dist_square(centroids[0]);
//             double dist;
//             for(int j=1;j<centroids.size();j++){
//                 dist=points[i].dist_square(centroids[j]);
//                 if(dist < mindist) mindist=dist;
//             }
//             distances[i]=mindist;
//             total+=distances[i];
//         }


//         if (total==0){
//             for(int i=0;i<points.size();i++){
//                 bool selected=false;
//                 for(int j=0;j<centroids.size();j++){
//                 if(points[i].dist_square(centroids[j])==0){
//                     selected=true;
//                 }
//                 }
//                 if(!selected){
//                     centroids.push_back(points[i]);
//                     break;
//                 }
//             }
//             continue;
//         }


//         double cumdist=0;
//         uniform_real_distribution<double>s(0,total);
//         double random_val=s(generator);

//         for(int i=0;i<distances.size();i++){
//             cumdist+=distances[i];
//             if(random_val < cumdist){
//                 centroids.push_back(points[i]);
//                 break;
//             }
//         }
//     }
//     return centroids;
// }

#include <bits/stdc++.h>
#include "KPlusInitializer.h"
#include "Exceptions.h"

using namespace std;

vector<DataPoint> KPlusInitializer :: Initialise(DataSet &d,int k){
    const vector<DataPoint>points =d.getPoints();
    if(points.empty()){
        throw EmptyDataSet();
    }
    if(k<=0 || k>points.size()){
        throw InvalidKException();
    }
    vector<DataPoint>centroids;

    random_device rd;
    mt19937 generator(rd());

    uniform_int_distribution<int> index(0,points.size()-1);
    int first=index(generator);
    centroids.push_back(points[first]);

    while(centroids.size()<k){
        vector<double>distances(points.size(),0);
        double total=0;
        for(int i=0;i<points.size();i++){
            double mindist=points[i].dist_square(centroids[0]);
            double dist;
            for(int j=1;j<centroids.size();j++){
                dist=points[i].dist_square(centroids[j]);
                if(dist < mindist) mindist=dist;
            }
            distances[i]=mindist;
            total+=distances[i];
        }


        if (total==0){
            for(int i=0;i<points.size();i++){
                bool selected=false;
                for(int j=0;j<centroids.size();j++){
                if(points[i].dist_square(centroids[j])==0){
                    selected=true;
                }
                }
                if(!selected){
                    centroids.push_back(points[i]);
                    break;
                }
            }
            continue;
        }


        double cumdist=0;
        uniform_real_distribution<double>s(0,total);
        double random_val=s(generator);

        for(int i=0;i<distances.size();i++){
            cumdist+=distances[i];
            if(random_val < cumdist){
                centroids.push_back(points[i]);
                break;
            }
        }
    }
    return centroids;
}