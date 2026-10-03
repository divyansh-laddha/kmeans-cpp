# Makefile for K-Means Clustering
all: kmeans

data.o: src/data.cpp include/data.h include/Exceptions.h
	g++ -std=c++17 -Iinclude -c src/data.cpp

cluster.o: src/cluster.cpp include/cluster.h include/data.h include/Exceptions.h
	g++ -std=c++17 -Iinclude -c src/cluster.cpp

RandomInitializer.o: src/RandomInitializer.cpp include/RandomInitializer.h include/Initializer.h include/data.h include/Exceptions.h
	g++ -std=c++17 -Iinclude -c src/RandomInitializer.cpp

KPlusInitializer.o: src/KPlusInitializer.cpp include/KPlusInitializer.h include/Initializer.h include/data.h include/Exceptions.h
	g++ -std=c++17 -Iinclude -c src/KPlusInitializer.cpp

KMeans.o: src/KMeans.cpp include/Kmeans.h include/cluster.h include/data.h include/Initializer.h
	g++ -std=c++17 -Iinclude -c src/KMeans.cpp

ClusteringMetrics.o: src/ClusteringMetrics.cpp include/ClusteringMetric.h include/cluster.h include/data.h
	g++ -std=c++17 -Iinclude -c src/ClusteringMetrics.cpp

main.o: src/main.cpp include/Kmeans.h include/KPlusInitializer.h include/RandomInitializer.h include/ClusteringMetric.h include/Exceptions.h
	g++ -std=c++17 -Iinclude -c src/main.cpp

kmeans: data.o cluster.o RandomInitializer.o KPlusInitializer.o KMeans.o ClusteringMetrics.o main.o
	g++ data.o cluster.o RandomInitializer.o KPlusInitializer.o KMeans.o ClusteringMetrics.o main.o -o kmeans

run: kmeans
	./kmeans

clean:
	rm -f *.o kmeans