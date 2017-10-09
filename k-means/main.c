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
    
    printf("\n\n");
    int i = generateRandomElementIndex(ndata);
    printf("index: %d \n\n", i);
    
    double *newData = getElementAtIndex(dim, i, data);
    for (int i = 0; i < dim; i++) {
        printf("newData[%d]: %f\n", i, newData[i]);
    }
    
    
    return 0;
}

/**
 Test case: Distance Function
 
 Tested with:
 #define dim     3  // Number of Dimensions
 #define ndata   10  // Number of Datapoints
 
 printf("\n");
 double distance = getDistanceBetween(1, 2, data, dim);
 printf("Distance: %f \n\n", distance);
 
 // sqrt( (a1-b1)^2 + (a2-b2)^2 + (a3-b3)^2 )
 // sqrt( (58-44)^2 + (30-78)^2 + (72-23)^2 )
 // sqrt( (14)^2 + (-48)^2 + (49)^2
 // sqrt( 196 + 2304 + 2401 )
 // sqrt( 4901 )
 // 70.007
 
 Console:
 Distance: 70.007142
 
 */
