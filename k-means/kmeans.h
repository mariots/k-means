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

/* kmeans */
int kmeans(int dim, int ndata, int totalCoordinates, int k, double *data, int *cluster_size, int *cluster_start, double *cluster_radius, double **cluster_centroid, int *cluster_assign, int maxIterations, double minMeanChange);

void initInitialClusters(int dim, int ndata, int totalCoordinates, int k, double *data, double **cluster_centroid);
void assignElementsToCentroids(int dim, int ndata, int totalCoordinates, int k, double *data, int *cluster_size, int *cluster_start, double *cluster_radius, double **cluster_centroid, int *cluster_assign);
void calculateMeanForCluster(int dim, int ndata, int k, int cluster, double *data, double **cluster_centroid, int *cluster_assign);

void getRadiusForClusters(int dim, int ndata, int k, double *data, double *cluster_radius, double **cluster_centroid, int *cluster_assign);
void getClusterSize(int ndata, int k, int *cluster_size, int *cluster_assign);


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


#endif
