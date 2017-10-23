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
        data[i] = (double)(rand() % 100);
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

// Assigns an element from the cluster_centroid at specified index to the dataElement argument
void getClusterCentroidElement(int dim, int cluster, double *dataElement, double **cluster_centroid) {
    for (int i = 0; i < dim; i++) {
        dataElement[i] = cluster_centroid[cluster][i];
    }
}

// Set a size dim data point to a specific cluster of the cluster_centroid
void setClusterCentroid(int dim, int cluster, double *data, double **cluster_centroid) {
    for (int i = 0; i < dim; i++) {
        cluster_centroid[cluster][i] = data[i];
    }
}


/* kmeans */

int kmeans(int dim, int ndata, int totalCoordinates, int k, double *data, int *cluster_size, int *cluster_start, double *cluster_radius, double **cluster_centroid, int *cluster_assign, int maxIterations, double minMeanChange) {
    
    double meanChange = 2.0; // Starts as 2 to pass initial loop condition
    int iterations = 0;
    
    // Get a copy of the old cluster
    double oldCluster[dim];
    // Get element for the new cluster
    double newCluster[dim];
    
    initInitialClusters(dim, ndata, totalCoordinates, k, data, cluster_centroid);
    
//    printf("iteration < maxIteration: %d < %d\n", iterations, maxIterations);
//    printf("meanChange > minMeanChange: %f > %f\n", meanChange, minMeanChange);
    
    while (meanChange > minMeanChange && iterations < maxIterations) {
        
//        printf("\niteration < maxIteration: %d < %d\n", iterations, maxIterations);
//        printf("meanChange > minMeanChange: %f > %f\n", meanChange, minMeanChange);
        
        meanChange = 0.0;
        
        assignElementsToCentroids(dim, ndata, totalCoordinates, k, data, cluster_size, cluster_start, cluster_radius, cluster_centroid, cluster_assign);
        
        // For each cluster, get and assign the mean
        for (int cluster = 0; cluster < k; cluster++) {
            
            getClusterCentroidElement(dim, cluster, oldCluster, cluster_centroid);
            
            // Calculates new mean for the cluster passed in
            calculateMeanForCluster(dim, ndata, k, cluster, data, cluster_centroid, cluster_assign);
            
            getClusterCentroidElement(dim, cluster, newCluster, cluster_centroid);
            
//            for (int i = 0; i < dim; i++) {
//                printf("oldCluster[%d]: %f\n", i, oldCluster[i]);
//            }
//
//            for (int i = 0; i < dim; i++) {
//                printf("newCluster[%d]: %f\n", i, newCluster[i]);
//            }
            
            // meanChange will stack the diffenece values
            meanChange += getDistanceBetween(oldCluster, newCluster, dim);
            // printf("meanChange: %f\n", meanChange);
        }
        
        iterations++;
    }
    
    
    getRadiusForClusters(dim, ndata, k, data, cluster_radius, cluster_centroid, cluster_assign);
    
    // printClusterRadius(cluster_radius, k);
    
    getClusterSize(ndata, k, cluster_size, cluster_assign);
    
    // printClusterSize(cluster_size, k);
    
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
    
    // Step 2
    
    // Get the distance form the first element in the dataset and the first element in the cluster
    currentDistance = getDistanceBetween(dataElement, getElementAtIndex(dim, 0, data), dim);
    
    // For every element in the dataset, find the element with the largest distance.
    for (int i = 1; i < ndata; i++) { // We start at 1 because we already found the currentDistance at element 0
        
        if(chosenElementsForCentroids[0] == i)
            continue; // If the currnet element is the same as the inital element, skip this iteration.
        
        if(largestDistance < currentDistance) {
            furthestElement = i;
            largestDistance = currentDistance;
        }
        // Find the next current distance at the end of every test
        currentDistance = getDistanceBetween(dataElement, getElementAtIndex(dim, i, data), dim);
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
                
                double *element = getElementAtIndex(dim, elementIndex, data);
                double *clusterElement = getElementAtIndex(dim, chosenElementsForCentroids[clusterIndex], data);
                
                currentDistance += getDistanceBetween(element, clusterElement, dim);
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
        //printf("chosenElementsForCentroids[%d]: %d\n", i, chosenElementsForCentroids[i]);
        
        dataElement = getElementAtIndex(dim, chosenElementsForCentroids[i], data);
        
        // Finally we set these centroids to our clusterCentroid
        setClusterCentroid(dim, i, dataElement, cluster_centroid);
    }
}

/*
 For each element
     For each cluster
         Compare distances from element to each cluster
         save cluster with shortest distance
     Assign element to cluster with shortest distance
*/

void assignElementsToCentroids(int dim, int ndata, int totalCoordinates, int k, double *data, int *cluster_size, int *cluster_start, double *cluster_radius, double **cluster_centroid, int *cluster_assign) {
    
    double currentDistance;
    double smallestDistance;
    int shortestCluster = 0;
    double clusterElement[dim]; // Array to hold each clusterElement
    
    // For each element
    for (int elementIndex = 0; elementIndex < ndata; elementIndex++) {
        
        // printf("element[%d]\n", elementIndex);
        
        // Reset distances for next cluster
        currentDistance = 0.0;
        smallestDistance = 0.0;
        
        // For each cluster
        for (int clusterIndex = 0; clusterIndex < k ; clusterIndex++) {
            // Skip all clusters that have not been set.
            
            double *element = getElementAtIndex(dim, elementIndex, data);
            getClusterCentroidElement(dim, clusterIndex, clusterElement, cluster_centroid);
            
            currentDistance = getDistanceBetween(element, clusterElement, dim);
            
            // printf("currentDistance: %f, shortestDistance: %f\n", currentDistance, smallestDistance);
            // Since smallestDistance starts out as 0, the first time the loop runs I need to set it to currentDistance.
            if (clusterIndex == 0) {
                smallestDistance = currentDistance;
                shortestCluster = clusterIndex;
                // printf("shortestCluster: %d\n\n", shortestCluster);
            } else if(currentDistance < smallestDistance) {
                shortestCluster = clusterIndex;
                // printf("shortestCluster: %d\n\n", shortestCluster);
            }
        }
        
        cluster_assign[elementIndex] = shortestCluster;
    }
    
    // printClusterAssign(cluster_assign, ndata);
}

/*
  For each cluster
     Calculate and return mean
*/
void calculateMeanForCluster(int dim, int ndata, int k, int cluster, double *data, double **cluster_centroid, int *cluster_assign) {
    
    // For each dimension
    for (int dimIndex = 0; dimIndex < dim; dimIndex++) {
        
        // We need to know what elements to test mean on
        int elementsInCluster[ndata];
        int count = 0; // We need a seperate counter to increment up
        
        // For each element that belongs in the specified cluster, add it to the list
        for (int elementIndex = 0; elementIndex < ndata; elementIndex++) {
            if(cluster == cluster_assign[elementIndex]) {
                elementsInCluster[count] = elementIndex;
                count += 1;
            }
        }
        
        // There is one or less elements in this cluster, dont change the mean.
        if (count <= 1) {
            return;
        }
        
//        for(int i = 0; i < count; i++) {
//            printf("elementsInCluster[%d]: %d\n" , i, elementsInCluster[i]);
//        }
        
        double mean = getMeanOfSet(elementsInCluster, count, dimIndex, dim, data);
        
        //printf("Mean: %f\n", mean);
        cluster_centroid[cluster][dimIndex] = mean;
    }
    
    
}

/*
  For each cluster
     For each element in that cluster
         Check to see if that element has the max distance.
             If it does, the distance is the radius to the centroid of the cluster.
*/
void getRadiusForClusters(int dim, int ndata, int k, double *data, double *cluster_radius, double **cluster_centroid, int *cluster_assign) {
    
    double largestDistance;
    double currentDistance;
    double clusterElement[dim]; // Array to hold each clusterElement
    
    // For each cluster
    for (int cluster = 0; cluster < k; cluster++) {
        
        // Reset the count
        largestDistance = 0.0;
        currentDistance = 0.0;
        
        // For each index in clusterAssign
        for (int elementIndex = 0; elementIndex < ndata; elementIndex++) {
            if(cluster == cluster_assign[elementIndex]) {
                
                //printf("Element Index: %d\n", elementIndex);
                double *element = getElementAtIndex(dim, elementIndex, data);
                getClusterCentroidElement(dim, cluster, clusterElement, cluster_centroid);
                
                currentDistance = getDistanceBetween(element, clusterElement, dim);
                //printf("currentDistance: %f, largestDistance: %f\n", currentDistance, largestDistance);
                
                if(largestDistance < currentDistance) {
                    largestDistance = currentDistance;
                }
            }
        }
        
        //printf("\n\n");
        cluster_radius[cluster] = largestDistance; // Set radius for that cluster
    }
}

/*
     For each cluster
         For each element in cluster assign
             Count every time an element appears for a cluster and add it to the total number for that cluster
*/
void getClusterSize(int ndata, int k, int *cluster_size, int *cluster_assign) {
    int count;
    
    // For each cluster
    for (int cluster = 0; cluster < k; cluster++) {
        
        // Reset the count
        count = 0;
        
        // For each index in clusterAssign
        for (int clusterIndex = 0; clusterIndex < ndata; clusterIndex++) {
            if(cluster == cluster_assign[clusterIndex])
                count += 1;
        }
        
        cluster_size[cluster] = count; // Set cluster size for that cluster
    }
}

void search(int dim, int ndata, int totalCoordinates, int k, double *data, int *cluster_size, double *cluster_radius, double **cluster_centroid, int *cluster_assign, double *searchElement, double *returnElement) {
    
    int returnElementIndex = 0;
    double smallestDistance = 0.0;
    double currentDistance = 0.0;
    
    int clustersToSearch[k]; // Which clusters to search
    int clusterCount = 0;
    
    // Find which clusters to check based on the radius
    for (int cluster = 0; cluster < k; cluster++) {
        
        double distanceToCentroid = getDistanceBetween(cluster_centroid[cluster], searchElement, dim);
        
        printf("distanceToCentroid: %f, cluster_radius[cluster]: %f\n", distanceToCentroid, cluster_radius[cluster]);
        
        // We know which clusters to search
        // If distance form searchElement to centroid is less than the radius, it is within the cluster.
        if(distanceToCentroid < cluster_radius[cluster]) {
            clustersToSearch[clusterCount] = cluster;
            clusterCount++;
            
            printf("clustersToSearch[%d]: %d", clusterCount, clustersToSearch[clusterCount]);
        }
    }
    
    for (int i = 0; i < k; i++) {
        printf("clustersToSearch[%d]: %d\n", i, clustersToSearch[i]);
    }
    
    
    
    // For each cluster
    for (int cluster = 0; cluster < clusterCount; cluster++) {
        
        // TODO: If cluster is not in clusterToSearch array, skip this iteration
        
        // We need to know what elements to test mean on
        int elementsInCluster[ndata];
        int count = 0; // We need a seperate counter to increment up
        
        // For each element that belongs in the specified cluster, add it to the list
        for (int elementIndex = 0; elementIndex < ndata; elementIndex++) {
            if(cluster == cluster_assign[elementIndex]) {
                elementsInCluster[count] = elementIndex;
                count += 1;
            }
        }
    }
    
    // Set the closest element by the index
    returnElement = getElementAtIndex(dim, returnElementIndex, data);
}


double getDistanceBetween(double *elementIndexA, double *elementIndexB, int dim) {
    // Euclidian Distance Formula: d(a,b) = sqrt( (a1-b1)^2 + (a2-b2)^2 + (a3-b3)^2 + (a4-b4)^2 )
    double distance = 0.0;
    
    for (int i = 0; i < dim; i++) {
        distance += ((elementIndexA[i] - elementIndexB[i]) * (elementIndexA[i] - elementIndexB[i]));
    }
    
    return sqrt(distance);
}

// For the elements passed in, return the mean of the requested dimension.
double getMeanOfSet(int *dataElements, int numberOfElements, int indexOfDim, int dim, double *data) {
    double totalMean = 0.0;
    
    if(numberOfElements == 0)
        return 0;
    
    // For every data point passed, get the sum(currentDimension)
    for (int i = 0; i < numberOfElements; i++) {
        int elementIndex = dataElements[i]; // Gets each element index
        double *currentElement = getElementAtIndex(dim, elementIndex, data); // Gets the current element at specifed index
        
        totalMean += currentElement[indexOfDim]; // Gets the value of the element at specified dimension
    }
    
    return totalMean / numberOfElements;
}


