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
#include "kmeans.h"

#define dim     3  // Number of Dimensions
#define ndata   10  // Number of Datapoints
#define k       3  // Number of Clusters

// Max Clusters: 128
// Max size: 1000
// Threshhold: Discretionary.. perhaps .01 movement on clusters

// Definition: An Element is a set of coordinates (x, y, z, ..., n) of size dim.

int main(int argc, const char * argv[]) {
    
    int totalCoordinates = ndata*dim; // Total number of coordinates (x, y, z, ..., n)
    double data[ndata * dim]; // Number of data points
    
    int cluster_size[k] = { ndata }; // Size of each k cluster
    int cluster_start[k]; // Array start of each k cluster
    
    double **cluster_centroid; // For each cluster, have a mean for each dimension
    double *cluster_radius;
    int cluster_assign[totalCoordinates]; // Assigns each datapoint to a cluster, 0...k clusters
    
    // set clusters and cluster_start to 0
    for (int i = 0; i < k; i++) {
        cluster_start[i] = 0;
    }
    
    // set cluster_assign to all 0s
    for (int i = 0; i < totalCoordinates; i++) {
        cluster_assign[i] = 0;
    }
    
    // init cluster_centroid
    cluster_centroid = (double **)calloc(k, sizeof(double *));
    
    for (int i = 0; i < k; i++) {
        cluster_centroid[i] = (double *)calloc(dim, sizeof(double));
    }
    
    // Generate our dataset
    generateData(totalCoordinates, data);
    
    printData(data, totalCoordinates, dim);
    
    //kmeans(dim, ndata, totalCoordinates, k, data, cluster_size, cluster_start, cluster_radius, cluster_centroid, cluster_assign);
    
    
    
    int dataElements[3] = {2, 7, 9}; // Create array requesting mean of elements 2 and 7.
    int numberOfElements = 3; // We are requesting the mean of 2 total elements.
    int indexOfDim = 3; // We are requesting the x dimension.
    
    double mean = getMeanOfSet(dataElements, numberOfElements, indexOfDim, dim, data);
    printf("\nTotal Mean: %f\n", mean);
    
    
    return 0;
}

