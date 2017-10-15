//
//  kmeans.h
//  kmeans
//
//  Created by Mario Jimenez on 10/6/17.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "kmeans.h"
#include "debug.h"

/* Element Data Stucture */

// Generates 'random' data for the dataset
void generateData(int totalCoordinates, double *data) {
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

int kmeans(int dim, int ndata, int totalCoordinates, int k, double *data, int *cluster_size, int *cluster_start, double *cluster_radius, double **cluster_centroid, int *cluster_assign) {
    
    initInitialClusters(dim, ndata, totalCoordinates, k, data, cluster_centroid);
    
    return 0;
}


/*
 Setting Inital Clusters.
 1. Choose random point as Centroid 1
 2. Choose Centroid 2 to be the largest distance from Centroid 1
 3. Until k Centroids are chosen
     a. For each element, get distances to all known centroids
     b. Assign the element with the largest distance to be the next chosen centroid
 */
void initInitialClusters(int dim, int ndata, int totalCoordinates, int k, double *data, double **cluster_centroid) {
    
    int chosenElementsForCentroids[k];
    double largestDistance = 0.0;
    double currentDistance = 0.0;
    int furthestElement = 0; // I am using this name to remember what this does.
    
    // This is a little bit of a hack. In C I can't dynamically find the length of the array,
    // so I dont know how many elements are set at a given time.
    // I am making all the starting elements to be -1 to check against it at runtime
    // and skip looking up elements whose values are not set.
    for (int i = 0; i < k; i++) {
        chosenElementsForCentroids[i] = -1;
    }
    
    // Step 1
    chosenElementsForCentroids[0] = generateRandomElementIndex(ndata);
    double *dataElement = getElementAtIndex(dim, chosenElementsForCentroids[0], data); // Inital Cluster
    setClusterCentroid(dim, 0, dataElement, cluster_centroid);
    // printCentroid(cluster_centroid, k, dim); // TODO: Remove debug
    
    currentDistance = getDistanceBetween(chosenElementsForCentroids[0], 0, data, dim);
    
    // Step 2
    // For every element in the dataset, find the element with the largest distance.
    for (int i = 1; i < ndata; i++) { // We start at 1 because we already found the currentDistance at element 0
        
        if(chosenElementsForCentroids[0] == i)
            continue; // If the currnet element is the same as the inital element, skip this iteration.
        
        if(largestDistance < currentDistance) {
            furthestElement = i;
            largestDistance = currentDistance;
        }
        // Find the next current distance at the end of every test
        currentDistance = getDistanceBetween(chosenElementsForCentroids[0], i, data, dim);
    }
    
    // I technically could have used this in the loop, but I wanted to remember exactly what the
    // furthest element variable does.
    chosenElementsForCentroids[1] = furthestElement;
    
    // If there is only 1 cluster. We are done.
    if(k == 1)
        return;
    
    // Found largest distance cluster
    dataElement = getElementAtIndex(dim, furthestElement, data); // Inital Cluster
    setClusterCentroid(dim, 1, dataElement, cluster_centroid); // Set 2nd Cluster
    // printCentroid(cluster_centroid, k, dim);
    
    // If there are 2 clusters. We are also done.
    if(k == 2)
        return;
    
    // Step 3
    // We have set 2 clusters up to this point.
    int numberOfSetClusters = 2;
    
    // While not k dims
    while (numberOfSetClusters < k) {
        
        // Reset largestDistance
        largestDistance = 0.0;
        
        // For each element
        for (int elementIndex = 0; elementIndex < ndata; elementIndex++) {
            
            // Reset currentDistance
            currentDistance = 0.0;
            
            // For each cluster
            for (int clusterIndex = 0; clusterIndex < k ; clusterIndex++) {
                // Skip all clusters that have not been set.
                if (chosenElementsForCentroids[clusterIndex] == -1)
                    continue;
                
                currentDistance += getDistanceBetween(elementIndex, chosenElementsForCentroids[clusterIndex], data, dim);
            }
            
            if(largestDistance < currentDistance) {
                largestDistance = currentDistance;
                furthestElement = elementIndex;
            }
        }
        
        // Found furthest element and set it to next cluster
        chosenElementsForCentroids[numberOfSetClusters] = furthestElement;
        
        numberOfSetClusters += 1;
    }
    
    for (int i = 0; i < k; i++) {
        printf("chosenElementsForCentroids[%d]: %d\n", i, chosenElementsForCentroids[i]);
        
        dataElement = getElementAtIndex(dim, chosenElementsForCentroids[i], data);
        
        // Finally we set these centroids to our clusterCentroid
        setClusterCentroid(dim, i, dataElement, cluster_centroid);
    }
}

void assignElementsToCentroids(int dim, int ndata, int totalCoordinates, int k, double *data, int *cluster_size, int *cluster_start, double *cluster_radius, double **cluster_centroid, int *cluster_assign) {
    
    
    
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

// For the elements passed in, return the mean of the requested dimension.
double getMeanOfSet(int *dataElements, int numberOfElements, int indexOfDim, int dim, double *data) {
    double totalMean = 0.0;
    
    // For every data point passed, get the sum(currentDimension)
    for (int i = 0; i < numberOfElements; i++) {
        int elementIndex = dataElements[i]; // Gets each element index
        double *currentElement = getElementAtIndex(dim, elementIndex, data); // Gets the current element at specifed index
        
        totalMean += currentElement[indexOfDim]; // Gets the value of the element at specified dimension
    }
    
    return totalMean / numberOfElements;
}



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

