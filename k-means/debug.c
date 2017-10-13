//
//  debug.c
//  debug
//
//  Created by Mario Jimenez on 10/13/17.

#include <stdio.h>
#include <stdlib.h>
#include "debug.h"

/* debug functions */
void printSpecificDataPoint(double *data, int requestedElement, int dim) {
    printf("Element %d\n", requestedElement);
    for (int i = 0; i < dim; i++) {
        printf("array[%d]: %f\n", (dim * requestedElement) + i, data[(dim * requestedElement) + i]);
    }
}

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
