#include "Kmeans.h"

using namespace std;

KMeans::KMeans(
    DataSet& d,
    int k,
    Initializer* initializer,
    int maxIterations,
    double tolerance)
    : data(d),
      k(k),
      maxIterations(maxIterations),
      tolerance(tolerance),
      initializer(initializer)
{
}

void KMeans::fit()
{
    vector<DataPoint> initialCentroids =
        initializer->Initialise(data, k);

    clusters.clear();

    for (int i = 0; i < k; i++)
    {
        clusters.push_back(Cluster(initialCentroids[i]));
    }

    for (int iteration = 0; iteration < maxIterations; iteration++)
    {
        vector<DataPoint> oldCentroids;

        for (int i = 0; i < k; i++)
        {
            oldCentroids.push_back(clusters[i].getCentroid());
        }

        assignPoints();

        updateCentroids();

        if (hasConverged(oldCentroids))
        {
            break;
        }
    }
}

void KMeans::assignPoints()
{
    for (int i = 0; i < k; i++)
    {
        clusters[i].clear();
    }

    const vector<DataPoint>& points = data.getPoints();

    for (const DataPoint& point : points)
    {
        int nearestCluster = 0;

        double minDistance =
            point.dist_square(clusters[0].getCentroid());

        for (int i = 1; i < k; i++)
        {
            double distance =
                point.dist_square(clusters[i].getCentroid());

            if (distance < minDistance)
            {
                minDistance = distance;
                nearestCluster = i;
            }
        }

        clusters[nearestCluster].add(point);
    }
}

void KMeans::updateCentroids()
{
    for (int i = 0; i < k; i++)
    {
        if (clusters[i].getSize() > 0)
        {
            clusters[i].updateCentroid();
        }
    }
}

bool KMeans::hasConverged(
    const vector<DataPoint>& oldCentroids) const
{
    for (int i = 0; i < k; i++)
    {
        double movement =
            oldCentroids[i].dist_square(
                clusters[i].getCentroid()
            );

        if (movement > tolerance)
        {
            return false;
        }
    }

    return true;
}

const vector<Cluster>& KMeans::getClusters() const
{
    return clusters;
}