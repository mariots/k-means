//
//  debug.h
//  k-means
//
//  Created by Mario Jimenez on 10/13/17.
//  Copyright © 2017 mariot. All rights reserved.
//

#ifndef debug_h
#define debug_h

#include <stdio.h>

/* debug functions */
void printSpecificDataPoint(double *data, int requestedElement, int dim);
void printData(double *data, int totalElements, int dim);
void printBoundry(double **cluster_bdry, int k, int dim);
void printCentroid(double **cluster_centroid, int k, int dim);
void printClusterSize(int *clusterSize, int k);
void printClusterStart(int *clusterStart, int k);
void printClusterAssign(int *clusterAssign, int ndata);
void printClusterRadius(double *clusterRadius, int k);


#endif /* debug_h */
