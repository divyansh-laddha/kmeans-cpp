#include <bits/stdc++.h>
#include "Kmeans.h"
#include "KPlusInitializer.h"
#include "RandomInitializer.h"
#include "ClusteringMetric.h"
#include "Exceptions.h"

using namespace std;

int main()
{
    DataSet data;
    string filename="data/mall_customer.csv";

    try
    {
        data.loadCSV(filename);
        data.normalize();
    }
    catch (const ProjectException& e)
    {
        cout << "\nError: " << e.what() << endl;
        return 1;
    }
    catch (const exception& e)
    {
        cout << "\nUnexpected Error: " << e.what() << endl;
        return 1;
    }

    cout << "Loaded " << data.getPoints().size() << " points.\n";

    RandomInitializer randomInit;
    KPlusInitializer kPlusInit;
    ClusteringMetrics metrics;

    int choice = 0;

    while (choice != 5)
    {
        cout << "\n===== MENU =====\n";
        cout << "1. Run with Random initializer\n";
        cout << "2. Run with K-Means++ initializer\n";
        cout << "3. Run with both (compare)\n";
        cout << "4. Elbow table (Random and K-Means++)\n";
        cout << "5. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 5)
        {
            break;
        }

        if (choice < 1 || choice > 4)
        {
            cout << "Invalid choice.\n";
            continue;
        }

        try
        {
            int k, maxIter;

            cout << "Enter number of clusters (K): ";
            cin >> k;

            cout << "Enter max iterations (e.g. 100): ";
            cin >> maxIter;

            if (cin.fail() || maxIter <= 0)
            {
                cout << "Invalid input for K or iterations.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }

            if (choice == 4)
            {
                cout << "\n===== ELBOW TABLE (Inertia) =====\n";

                for (int kk = 1; kk <= k; kk++)
                {
                    KMeans randomModel(data, kk, &randomInit, maxIter);
                    randomModel.fit();

                    KMeans kPlusModel(data, kk, &kPlusInit, maxIter);
                    kPlusModel.fit();

                    cout << "K = " << kk
                         << " -> Random: " << metrics.inertia(randomModel.getClusters())
                         << " | K-Means++: " << metrics.inertia(kPlusModel.getClusters())
                         << endl;
                }

                continue;
            }

            char showMembers;

            cout << "Display points of each cluster? (y/n): ";
            cin >> showMembers;

            vector<Initializer*> inits;
            vector<string> names;

            if (choice == 1 || choice == 3)
            {
                inits.push_back(&randomInit);
                names.push_back("Random");
            }

            if (choice == 2 || choice == 3)
            {
                inits.push_back(&kPlusInit);
                names.push_back("K-Means++");
            }

            vector<double> inertias;
            vector<double> silhouettes;

            for (int r = 0; r < (int)inits.size(); r++)
            {
                KMeans model(data, k, inits[r], maxIter);

                model.fit();

                const vector<Cluster>& clusters = model.getClusters();

                cout << "\n===== K-MEANS RESULT (" << names[r] << ") =====\n";

                for (int i = 0; i < (int)clusters.size(); i++)
                {
                    cout << "\nCluster " << i + 1 << endl;
                    cout << "Size: " << clusters[i].getSize() << endl;

                    cout << "Centroid: ";
                    clusters[i].getCentroid().display_1();

                    if (showMembers == 'y' || showMembers == 'Y')
                    {
                        cout << "Points:\n";

                        const vector<DataPoint>& members = clusters[i].getMembers();

                        for (int j = 0; j < (int)members.size(); j++)
                        {
                            cout << "  ";
                            members[j].display_1();
                        }
                    }
                }

                double inertia = metrics.inertia(clusters);
                double silhouette = metrics.silhouette(clusters);

                inertias.push_back(inertia);
                silhouettes.push_back(silhouette);

                cout << "\n----- Metrics (" << names[r] << ") -----\n";
                cout << "Inertia (WCSS): " << inertia << endl;
                cout << "Silhouette Score: " << silhouette << endl;
            }

            if (inits.size() == 2)
            {
                cout << "\n===== COMPARISON =====\n";
                cout << "Random    -> Inertia: " << inertias[0]
                     << ", Silhouette: " << silhouettes[0] << endl;
                cout << "K-Means++ -> Inertia: " << inertias[1]
                     << ", Silhouette: " << silhouettes[1] << endl;

                if (inertias[0] < inertias[1])
                {
                    cout << "Lower inertia: Random\n";
                }
                else if (inertias[1] < inertias[0])
                {
                    cout << "Lower inertia: K-Means++\n";
                }
                else
                {
                    cout << "Inertia is equal for both.\n";
                }

                if (silhouettes[0] > silhouettes[1])
                {
                    cout << "Higher silhouette: Random\n";
                }
                else if (silhouettes[1] > silhouettes[0])
                {
                    cout << "Higher silhouette: K-Means++\n";
                }
                else
                {
                    cout << "Silhouette is equal for both.\n";
                }
            }
        }
        catch (const ProjectException& e)
        {
            cout << "\nError: " << e.what() << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        catch (const exception& e)
        {
            cout << "\nUnexpected Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    cout << "\nExiting program.\n";

    return 0;
}