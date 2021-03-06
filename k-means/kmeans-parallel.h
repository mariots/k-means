//
//  kmeans-parallel.h
//  k-means
//
//  Created by Mario Jimenez on 10/16/17.
//  Copyright © 2017 mariot. All rights reserved.
//

#ifndef kmeans_parallel_h
#define kmeans_parallel_h

/* Element Data Stucture */
void generateData(int totalCoordinates, double *data);
int generateRandomElementIndex(int ndata);
double *getElementAtIndex(int dim, int elementIndex, double *data);
void setClusterCentroid(int dim, int cluster, double *data, double **cluster_centroid);

/* kmeans */
int kmeans(int dim, int ndata, int totalCoordinates, int k, double *data, int *cluster_size, int *cluster_start, double *cluster_radius, double **cluster_centroid, int *cluster_assign, int maxIterations, double minMeanChange);

void initInitialClusters(int dim, int ndata, int totalCoordinates, int k, double *data, double **cluster_centroid);
void assignElementsToCentroids(int dim, int ndata, int totalCoordinates, int k, double *data, int *cluster_size, int *cluster_start, double *cluster_radius, double **cluster_centroid, int *cluster_assign);
void calculateMeanForCluster(int dim, int ndata, int k, int cluster, double *data, double **cluster_centroid, int *cluster_assign);

void getRadiusForClusters(int dim, int ndata, int k, double *data, double *cluster_radius, double **cluster_centroid, int *cluster_assign);
void getClusterSize(int ndata, int k, int *cluster_size, int *cluster_assign);

// search
// Given an element
// Find which clusters contain that element
// Search
void search(int dim, int ndata, int totalCoordinates, int k, double *data, int *cluster_size, double *cluster_radius, double **cluster_centroid, int *cluster_assign, double *searchElement, double *returnElement);

double getDistanceBetween(double *elementIndexA, double *elementIndexB, int dim);

// This is a specialized mean function.
// Return the mean of the dimension of the individual elements passed in.
double getMeanOfSet(int *dataElements, int numberOfElements, int indexOfDim, int dim, double *data);


#endif /* kmeans_parallel_h */
