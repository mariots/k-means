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

/* kmeans */
int kmeans(int dim, int ndata, int totalCoordinates, int k, int *cluster_size, int *cluster_start, double *cluster_radius, double **cluster_centroid, int *cluster_assign);


double getDistanceBetween(int elementIndexA, int elementIndexB, double *data, int dim);

// Returns the mean of the data set passed in.
double getMean(double *data, int ndata, int indexOfDim, int dim, double bdry[2]);

// Return the variance of the data set passed in.
double getVariance(double *data, int ndata, int mean,  int indexOfDim, int dim);

// Swap takes in the number of dimensions, an array and the index's of the elements to be swaped.
void swap(int dim, double *a, int i, int j);



/* debug functions */
void printData(double *data, int totalElements, int dim);
void printBoundry(double **cluster_bdry, int k, int dim);
void printCentroid(double **cluster_centroid, int k, int dim);
void printClusterSize(int *clusterSize, int k);
void printClusterStart(int *clusterStart, int k);

#endif
