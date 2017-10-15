//
//  kmeans.h
//  kmeans
//
//  Created by Mario Jimenez on 10/6/17.

#ifndef KMEANS   /* Include guard */
#define KMEANS

/* Element Data Stucture */
void generateData(int totalCoordinates, double *data);
int generateRandomElementIndex(int ndata);
double *getElementAtIndex(int dim, int elementIndex, double *data);
void setElementAtIndex(int dim, double *data, double *insert, int elementIndex);
void setClusterCentroid(int dim, int cluster, double *data, double **cluster_centroid);
void setClusterAssign(int dim, int cluster, int elementIndex, int *clusterAssign);

/* kmeans */
int kmeans(int dim, int ndata, int totalCoordinates, int k, double *data, int *cluster_size, int *cluster_start, double *cluster_radius, double **cluster_centroid, int *cluster_assign);

void initInitialClusters(int dim, int ndata, int totalCoordinates, int k, double *data, double **cluster_centroid);
void assignElementsToCentroids(int dim, int ndata, int totalCoordinates, int k, double *data, int *cluster_size, int *cluster_start, double *cluster_radius, double **cluster_centroid, int *cluster_assign);

double getDistanceBetween(double *elementIndexA, double *elementIndexB, int dim);

// search
// pick closest centroid as started
// search that cluster
// If theres a boundary closer to that point, search that cluster.


// This is a specialized mean function.
// Return the mean of the dimension of the individual elements passed in.
double getMeanOfSet(int *dataElements, int numberOfElements, int indexOfDim, int dim, double *data);

// Returns the mean of the data set passed in.
double getMean(double *data, int ndata, int indexOfDim, int dim, double bdry[2]);

// Return the variance of the data set passed in.
double getVariance(double *data, int ndata, int mean,  int indexOfDim, int dim);

// Swap takes in the number of dimensions, an array and the index's of the elements to be swaped.
void swap(int dim, double *a, int i, int j);


#endif
