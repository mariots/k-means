//
//  kmeans.h
//  kmeans
//
//  Created by Mario Jimenez on 10/6/17.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "kmeans.h"


/* Element Data Stucture */

// Generates 'random' data for the dataset
void generateData(int totalCoordinates, double *data)
{
    srand(1);
    
    for(int i = 0; i < totalCoordinates; i++)
    {
        double temp = (double)(rand() % 100);
        data[i] = temp;
    }
}

// Generate 'random' element index
int generateRandomElementIndex(int ndata) {
    srand(1);
    return (rand() % ndata);
}

// Returns element at specified index
double *getElementAtIndex(int dim, int elementIndex, double *data) {
    return &data[dim*elementIndex]; // [dim * elementIndex]: will give the starting index of the element requested
}

// Sets the element at index i, to the data provided
void setElementAtIndex(int dim, double *data, double *insert, int index) {
    // TODO
}

// Set a size dim data point to a specific cluster of the cluster_centroid
void setClusterCentroid(int dim, int cluster, double *data, double **cluster_centroid) {
    for (int i = 0; i < dim; i++) {
        cluster_centroid[cluster][i] = data[i];
    }
}

/* kmeans */
int kmeans(int dim, int ndata, int totalCoordinates, int k, int *cluster_size, int *cluster_start, double *cluster_radius, double **cluster_centroid, int *cluster_assign) {
    
    return 0;
}


/*
 Setting Inital Clusters.
 1. Choose random point as Centroid 1
 2. Choose Centroid 2 to be the largest distance from Centroid 1
 3. Until k Centroids are chosen
     a. Get mean of all chosen centroids
     b. Using the calculated mean (x, y, .., dim) find largest distance and add to Centroid list
 */
void initInitialClusters(int dim, int ndata, int totalCoordinates, int k, double **cluster_centroid) {
    int randomIndex = generateRandomElementIndex(ndata);
    cluster_centroid[0][0] = randomIndex;
    
}

double getDistanceBetween(int elementIndexA, int elementIndexB, double *data, int dim) {
    // Euclidian Distance Formula: d(a,b) = sqrt( (a1-b1)^2 + (a2-b2)^2 + (a3-b3)^2 + (a4-b4)^2 )
    
    double distance = 0.0;
    double *tempElementA = getElementAtIndex(dim, elementIndexA, data);
    double *tempElementB = getElementAtIndex(dim, elementIndexB, data);
    
    for (int i = 0; i < dim; i++) {
        distance += ((tempElementA[i] - tempElementB[i]) * (tempElementA[i] - tempElementB[i]));
    }
    
    return sqrt(distance);
}



// Find mean of dataset
double getMean(double *data, int ndata, int indexOfDim, int dim, double bdry[2]) {
    
    // index will be used to get the specific dimention
    // dim will be used to iterate over the current dimension
    
    double total = 0;
    double min = data[indexOfDim];
    double max = data[indexOfDim];
    
    for (int i = 0; i < ndata; i++) {
        
        // The index moves every dim elements plus the current dimension
        total += data[(i * dim) + indexOfDim];
        if(data[i] < min) {
            min = data[(i * dim) + indexOfDim];
        }
        
        if(data[i] > max) {
            max = data[(i * dim) + indexOfDim];
        }
    }
    
    // For each dim, set the min/max
    bdry[0] = min;
    bdry[1] = max;
    
    return (total / ndata);
}


double getVariance(double *data, int ndata, int mean, int indexOfDim, int dim) {
    
    double total = 0;
    
    for (int i = 0; i < ndata; i++) {
        total += (data[(i * dim) + indexOfDim] - mean) * (data[(i * dim) + indexOfDim] - mean);
    }
    
    return (total / ndata);
}


/*
 
 Swap takes in the number of dimensions, an array and the
 index's of the elements to be swaped.
 
 ex: swap(3, data, 1, 3); // Elements 1, and 3 are swaped.
 
 */
void swap(int dim, double *a, int x, int y) {
    
    double tmp;
    x *= dim; // Setting x and y index to the correct index to swap
    y *= dim;
    
    for (int i = 0; i < dim; i++) {
        tmp = a[x+i];
        a[x+i] = a[y+i];
        a[y+i] = tmp;
    }
}


/* debug functions */
void printData(double *data, int totalElements, int dim) {
    
    for (int i = 0; i < totalElements; i++) {
        if(i % dim == 0) {
            printf("Element %d\n", i / dim);
        }
        printf("array[%d]: %f\n", i, data[i]);
    }
    
}

void printBoundry(double **cluster_bdry, int k, int dim) {
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < dim*2; j++) {
            printf("cluster_bdry[%d][%d]: %f\n", i, j, cluster_bdry[i][j]);
        }
    }
}

void printCentroid(double **cluster_centroid, int k, int dim) {
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < dim; j++) {
            printf("cluster_centroid[%d][%d]: %f\n", i, j, cluster_centroid[i][j]);
        }
    }
}

void printClusterSize(int *clusterSize, int k) {
    for (int i = 0; i < k; i++) {
        printf("cluster_size[%d]: %d\n", i, clusterSize[i]);
    }
}

void printClusterStart(int *clusterStart, int k) {
    for (int i = 0; i < k; i++) {
        printf("cluster_start[%d]: %d\n", i, clusterStart[i]);
    }
}

void printClusterAssign(int *clusterAssign, int ndata, int dim) {
    for (int i = 0; i < ndata * dim; i++) {
        if(i % dim == 0) {
            printf("Element %d\n", i / dim);
        }
        printf("cluster_assign[%d]: %d\n", i, clusterAssign[i]);
    }
}
