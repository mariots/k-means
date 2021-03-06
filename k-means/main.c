//
//  main.c
//  k-means
//
//  Created by Mario Jimenez on 10/6/17.
//  Copyright © 2017 mariot. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include "kmeans-sequential.h"
#include "kmeans-parallel.h"
#include "debug.h"

#define dim     2           // Number of Dimensions
#define ndata   24          // Number of Datapoints
#define k       3           // Number of Clusters
#define maxIterations 20    // Max number of k-means iterations
#define minMeanChange 1.5   // Minimum amount of change before iterations cease

// To visualize results
void writeResults(double *data, int *cluster_assign);

// Max Clusters: 128
// Max size: 1000
// Threshhold: Discretionary.. perhaps .01 movement on clusters

// Definition: An Element is a set of coordinates (x, y, z, ..., n) of size dim.

int main(int argc, const char * argv[]) {
    
    // Setup variables
    int totalCoordinates = ndata*dim; // Total number of coordinates (x, y, z, ..., n)
    double data[ndata * dim]; // Number of data points
    
    int cluster_size[k] = { ndata }; // Size of each k cluster
    int cluster_start[k]; // Array start of each k cluster
    
    double **cluster_centroid; // For each cluster, have a mean for each dimension
    double cluster_radius[k];
    int cluster_assign[ndata]; // Assigns each element (note an element is ndata*dim values) to a cluster, 0...k clusters
    
    // set clusters and cluster_start to 0
    for (int i = 0; i < k; i++) {
        cluster_start[i] = 0;
    }
    
    // set cluster_assign to all 0s
    for (int i = 0; i < ndata; i++) {
        cluster_assign[i] = 0;
    }
    
    // init cluster_centroid
    cluster_centroid = (double **)calloc(k, sizeof(double *));
    
    for (int i = 0; i < k; i++) {
        cluster_centroid[i] = (double *)calloc(dim, sizeof(double));
    }
    
    // Generate our dataset
    generateData(totalCoordinates, data);
    
    // printData(data, totalCoordinates, dim);
    
    kmeans(dim, ndata, totalCoordinates, k, data, cluster_size, cluster_start, cluster_radius, cluster_centroid, cluster_assign, maxIterations, minMeanChange);
    
    double searchElement[dim] = { 1, 1 }; // test case only works for 2 dimensions
    double returnElement[dim];
    
    search(dim, ndata, totalCoordinates, k, data, cluster_size, cluster_radius, cluster_centroid, cluster_assign, searchElement, returnElement);
    
    for (int i = 0; i < dim; i++) {
        printf("returnElement[%d]: %f\n", i, returnElement[i]);
    }
    
    // writes results to file to be visualized
    writeResults(data, cluster_assign);
    
    return 0;
}


// Franks python visualization
void writeResults(double *data, int *cluster_assign) {
    int i;
    FILE *file;
    //fopen_s(&file, "data.txt", "w");
    file = fopen("data.txt", "w");
    if (file == NULL)
        printf("error");
    
    fprintf(file, "%d\n", dim);
    fprintf(file, "%d\n", ndata);
    for (i = 0; i < dim * ndata; i++)
        fprintf(file, "%lf\n", data[i]);
    
    for (i = 0; i < ndata; i++)
        fprintf(file, "%d\n", cluster_assign[i]);
    
    fclose(file);
}

