#include "ClusteringMetric.h"
#include <cmath>
using namespace std;

double ClusteringMetrics::inertia(const vector<Cluster>& clusters){
    double total = 0;

    int clusterCount = clusters.size();
    for(int i = 0; i < clusterCount; i++){
        const DataPoint& centroid = clusters[i].getCentroid();
        const vector<DataPoint>& members = clusters[i].getMembers();

        int memberCount = members.size();
        for(int j = 0; j < memberCount; j++){
            total = total + members[j].dist_square(centroid);
        }
    }

    return total;
}

double ClusteringMetrics::silhouette(const vector<Cluster>& clusters){
    int totalPoints = 0;

    int clusterCount = clusters.size();
    for(int i = 0; i < clusterCount; i++){
        totalPoints = totalPoints + clusters[i].getSize();
    }

    if(totalPoints == 0 || clusterCount <= 1){
        return 0;
    }

    double totalScore = 0;
    int count = 0;

    for(int c = 0; c < clusterCount; c++){
        const vector<DataPoint>& members = clusters[c].getMembers();

        int memberCount = members.size();
        for(int p = 0; p < memberCount; p++){
            if(members.size() == 1){
                continue;
            }

            double a = 0;

            for(int j = 0; j < memberCount; j++){
                if(j != p){
                    a = a + sqrt(members[p].dist_square(members[j]));
                }
            }

            a = a / (memberCount - 1);

            double b = 1e100;

            for(int otherCluster = 0; otherCluster < clusterCount; otherCluster++){
                if(otherCluster == c || clusters[otherCluster].getSize() == 0){
                    continue;
                }

                const vector<DataPoint>& otherMembers = clusters[otherCluster].getMembers();
                double average = 0;

                int otherMemberCount = otherMembers.size();
                for(int j = 0; j < otherMemberCount; j++){
                    average = average + sqrt(members[p].dist_square(otherMembers[j]));
                }

                average = average / otherMemberCount;

                if(average < b){
                    b = average;
                }
            }

            double denominator = max(a, b);

            if(b < 1e99 && denominator > 0){
                totalScore = totalScore + (b - a) / denominator;
                count++;
            }
        }
    }

    if(count == 0){
        return 0;
    }

    return totalScore / count;
}
