//
//  debug.h
//  Debug functions used for the purpose of testing
//
//  Created by Mario Jimenez on 10/13/17.

#ifndef DEBUG   /* Include guard */
#define DEBUG

/* debug functions */
void printSpecificDataPoint(double *data, int requestedElement, int dim);
void printData(double *data, int totalElements, int dim);
void printBoundry(double **cluster_bdry, int k, int dim);
void printCentroid(double **cluster_centroid, int k, int dim);
void printClusterSize(int *clusterSize, int k);
void printClusterStart(int *clusterStart, int k);

#endif

