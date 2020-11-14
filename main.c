//
// Created by ido & jacob on 08/11/2020.
//
# include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//#define N   100
//#define D   1
//#define K 5
//#define MAX_ITER    1000


int findClosestCluster(float *x, float **centroids, int k , int d);

int updateCentroid(int *clusterVec, float *centroidVec, float **allVecs, int d);

float getDistance(float *vec1, float *vec2, int d);

int main(int argc, char* argv[]) {
    assert(argc == 5);
    const int k = atoi(argv[1]);
    const int n = atoi(argv[2]);
    const int d = atoi(argv[3]);
    const int MAX_ITER = atoi(argv[4]);
    assert(k != 0 && n != 0 && d != 0 && MAX_ITER != 0);

    float *p;
    float **vectors;
    p =(float *) calloc(n * d, sizeof(float ));
    vectors= calloc(n, sizeof(float *));
    for (int i = 0; i < n; ++i) {
        vectors[i] = p + i * d;
    }

    char c;
    while (scanf("%f%c", p++, &c) == 2);

    float centroids [k] [d];
    int clusters [k] [n+1];
    //copy the first K vectors to the centroids
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < d; ++j) {
            centroids[i][j]=vectors[i][j];
        }
    }
    for (int tries = 0; tries < MAX_ITER; ++tries) {
        int change = 0; //tell us if clusters change

        for (int i = 0; i < n; ++i) {
            //put vectors in clusters

            int index = findClosestCluster(vectors[i],  centroids, k, d);
            clusters[index][++clusters[index][0]] = i;//add the cluster
        }
        //calculate cent
        for (int i = 0; i < k; ++i) {
            if (updateCentroid(clusters[i],centroids[i],vectors,d)){
                change = 1;
            }
        }
        if (!change){break;}
        for (int i = 0; i < k; ++i) {// resetting the clusters
            clusters[i][0] = 0;
        }
    }
    //printing the clusters results:
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < d; ++j) {
            printf("%.2f", centroids[i][j]);
            if (j != (d-1)) printf(",");
        }
        printf("\n");
    }
    free(centroids);
    free(vectors);
    free(clusters);
    return 0;
}

float getDistance(float *vec1, float *vec2, int d) { //returns the norm squared
    float sum = 0;
    for (int i = 0; i < d; ++i) {
        sum += (float )pow(vec1[i] + vec2[i], 2);
     //   printf("vec1 %lf vec2 %lf",vec1[i],vec2[i]); debugging
        //sum += (*(vec1+(i*sizeof(float))) - *(vec2+(i*sizeof(float))))
    }
    return sum;
}

int updateCentroid(int *clusterVec, float *centroidVec, float **allVecs, int d) {
    int numOfElms = (int) *clusterVec; //first elm indicates number of vectors in cluster
    float vecOfSums[d];
    int flag = 0;
    float *curr;
    for (int i = 1; i <= numOfElms; ++i) {
        curr = allVecs[clusterVec[i]];
        for (int j = 0; j < d; ++j) {
            vecOfSums[j] += curr[j];
        }
    }
    for (int i = 0; i < d; ++i) {
        vecOfSums[i] = (vecOfSums[i] / (float)numOfElms);
        if (centroidVec[i] != vecOfSums[i]) {
            centroidVec[i] = vecOfSums[i];
            flag = 1;
        }
    }
    return flag;
}


int findClosestCluster(float* x, float** centroids,int k,int d) {

    float distances[k];
    for (int i = 0; i < k; ++i) {
        distances [i] = getDistance(x, (float *) (centroids+i), d);//calculat all the distences to x
    }

    float min = distances[0];
    int minIndex = 0;
    for (int i = 0; i < k; ++i) {
        if (distances[i]<=min){minIndex = i;}
    }
    return minIndex;
}