//
//  kmeans.h
//  VoterMLA
//
//  Created by MD Shihabul Kabir on 12/5/16.
//  Copyright © 2016 MD Shihabul Kabir. All rights reserved.
//

#ifndef kmeans_h
#define kmeans_h

#include "county.h"
#include <vector>

//K-Means Clustering Namespace
namespace KmeansCluster {
    //Data Structure to help K-Means Clustering
    class KMeans{
    private:
    //setup three clusters for the clustering and two for last centroids and current centroids
    std::vector<CountyStruct::County>cluster1,cluster2,cluster3,last,current,all;
    
    public:
    //method find the closest cluster to add
    void addToClosest(CountyStruct::County&acounty);
        
    //method to initialize rand centroids and clusters
    void initialize(std::vector<CountyStruct::County> counties);
    
    //method to get the mean of a cluster
    std::vector<float> mean(std::vector<CountyStruct::County>&cluster);
        
    //method to get centroid closest to mean of cluster
    CountyStruct::County getCentroid(std::vector<CountyStruct::County>&cluster,std::vector<float> mean);
    
    //method to get the centroid of a cluster
    CountyStruct::County centroid(std::vector<CountyStruct::County>&counties);
        
    //method to setup centroids
    bool setupCentroids();
    
    //method to make the clusters
    void cluster();
    
    //method to get the distance from a point to rest of cluster
    float avgDistance(std::vector<CountyStruct::County>&cluster,int index);
    
    //method to find distance from cluster from a point
    float distanceFromCluster(CountyStruct::County&c,std::vector<CountyStruct::County>&cluster);
        
    //method to return silhoute value
    float silh(std::vector<CountyStruct::County>&a,std::vector<CountyStruct::County>&b,int index);
        
    //method to print the silhoute for each cluster
    void printSil();

    
    };

}


#endif /* kmeans_h */
