

/**
 Test case: getElementAtIndex function
 
 Tested with:
 #define dim     3  // Number of Dimensions
 #define ndata   10  // Number of Datapoints
 
 printf("\n\n");
 int i = generateRandomElementIndex(ndata);
 printf("index: %d \n\n", i);
 
 double *newData = getElementAtIndex(dim, i, data);
 for (int i = 0; i < dim; i++) {
 printf("newData[%d]: %f\n", i, newData[i]);
 }
 
 Console:
 
 index: 7
 
 newData[0]: 69.000000
 newData[1]: 9.000000
 newData[2]: 57.000000
 
 */

/**
 Test case: getDistanceBetween function
 
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

/**
 Test case: setClusterCentroid function
 
 Tested with:
 #define dim     3   // Number of Dimensions
 #define ndata   10  // Number of Datapoints
 #define k       3   // Number of Clusters
 
 int randomIndex = generateRandomElementIndex(ndata);
 double *dataPoint = getElementAtIndex(dim, randomIndex, data);
 setClusterCentroid(dim, 0, dataPoint, cluster_centroid);
 
 printf("Random Index: %d\n", randomIndex);
 printCentroid(cluster_centroid, k, dim);
 
 Console:
 
 // NOTE: ** printData() was called above to see this **
 Element 7
 array[21]: 69.000000
 array[22]: 9.000000
 array[23]: 57.000000
 
 Random Index: 7
 
 cluster_centroid[0][0]: 69.000000
 cluster_centroid[0][1]: 9.000000
 cluster_centroid[0][2]: 57.000000
 cluster_centroid[1][0]: 0.000000
 cluster_centroid[1][1]: 0.000000
 cluster_centroid[1][2]: 0.000000
 cluster_centroid[2][0]: 0.000000
 cluster_centroid[2][1]: 0.000000
 cluster_centroid[2][2]: 0.000000
 
 */

/**
 Test case: getMeanOfSet function
 
 Tested with:
 #define dim     3   // Number of Dimensions
 #define ndata   10  // Number of Datapoints
 #define k       3   // Number of Clusters
 
 int dataElements[3] = {2, 7, 9}; // Create array requesting mean of elements 2 and 7.
 int numberOfElements = 3; // We are requesting the mean of 2 total elements.
 int indexOfDim = 3; // We are requesting the x dimension.
 
 double mean = getMeanOfSet(dataElements, numberOfElements, indexOfDim, dim, data);
 printf("\nTotal Mean: %f\n", mean);
 
 Console:
 
 // NOTE: I HAVE TAKEN THE DEBUG PRINTS OUT OF THE FUNCTION
 // Just add this code:
 printf("\n");
 printSpecificDataPoint(data, elementIndex, dim);
 
 
 Mean Function
 
 Element 2
 array[6]: 44.000000
 array[7]: 78.000000
 array[8]: 23.000000
 
 Element 7
 array[21]: 69.000000
 array[22]: 9.000000
 array[23]: 57.000000
 
 Element 9
 array[27]: 78.000000
 array[28]: 16.000000
 array[29]: 35.000000
 
 Total Mean: 23.000000
 
 */
