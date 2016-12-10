//
//  kmeans.cpp
//  VoterMLA
//
//  Created by MD Shihabul Kabir on 12/5/16.
//  Copyright © 2016 MD Shihabul Kabir. All rights reserved.
//


#include "county.h"
#include "kmeans.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <iostream>

using namespace std;
using namespace CountyStruct;

//K-Means Clustering Namespace
namespace KmeansCluster{
    
    //find the closest cluster to add
    void KMeans:: addToClosest(CountyStruct::County&acounty){
        //check if county passed in centroid
        if(current[0].compare(acounty) || current[1].compare(acounty) || current[2].compare(acounty) ) return;

        
        //get the distance from the centroid to the county
        float distance1 = current[0].distance(acounty);
        float distance2 = current[1].distance(acounty);
        float distance3 = current[2].distance(acounty);
        
        //check which distance is the smallest
        float smallest = distance1;
        if(smallest > distance2){
            smallest = distance2;
        }
        if(smallest > distance3){
            smallest = distance3;
        }
        
        //based on the smallest distance add to cluster
        if(smallest == distance1){
            cluster1.push_back(acounty);
        }
        else if(smallest == distance2){
            cluster2.push_back(acounty);
        }
        else{
            cluster3.push_back(acounty);
        }
    }
    
    //method to initialize
    void KMeans:: initialize(vector<County> counties){
        //initialize random
        srand(time(NULL));
        
        //get three random indexes
        int index1 = rand() % 100;
        int index2 = rand() % 500 + 100;
        int index3 = rand() % 1000 + 500;
        
        //get the three random centroids
        County first = counties[index1];
        County second = counties[index2];
        County third = counties[index3];
        
        //push them into the clusters and setup centroids
        cluster1.push_back(first);
        cluster2.push_back(second);
        cluster3.push_back(third);
        current.push_back(first);
        current.push_back(second);
        current.push_back(third);
        
        //go through counties and add to each cluster
        for(County c : counties){
            addToClosest(c);
            all.push_back(c);
        }
    }
    
    //method to get the mean of a cluster
    vector<float> KMeans::mean(std::vector<CountyStruct::County>&cluster){
        vector<float>totals;
        for(int i =DEMOCRAT; i < TOTAL_ATTR; ++i){
            totals.push_back(0);
        }
        //go through and tally the total sum
        for(County c : cluster){
            for(int i =POPULATION; i < TOTAL_ATTR; ++i){
                totals[i] += c.member(i);
            }
        }
        //calculate the average sums
        for(int i = POPULATION; i < TOTAL_ATTR; ++i){
            totals[i] /= cluster.size();
        }
        
        
        return totals;
    }
    
    //method to get centroid closest to mean of cluster
    County KMeans::getCentroid(std::vector<CountyStruct::County>&cluster,vector<float>mean){
        
        //initialize global difference and centroid to return
        County centroid = cluster[0];
        float diff = 0;
        for(int i =POPULATION; i < TOTAL_ATTR; ++i){
            diff += powf(centroid.member(i)-mean[i],2);
        }
        diff = sqrtf(diff);
        
        //loop through and find county closest to mean
        for(County c : cluster){
            float local = 0;
            for(int i =POPULATION; i < TOTAL_ATTR; ++i){
                local += powf(c.member(i)-mean[i],2);
            }
            local = sqrtf(local);
            
            if(local < diff){
                diff = local;
                centroid = c;
            }
        }
        
        return centroid;
    }
    
     //method to setup centroids
     bool KMeans::setupCentroids(){
        //get the centroids of each initialized clusters
        County c1 = getCentroid(cluster1, mean(cluster1));
        County c2 = getCentroid(cluster2, mean(cluster2));
        County c3 = getCentroid(cluster3, mean(cluster3));
        
        
        //if current and last are the same then return
        if(current[0].compare(c1) && current[1].compare(c2) && current[2].compare(c3)) return false;
        
        //otherwise clear the clusters and push back the clusters
         current[0] = c1;
         current[1] = c2;
         current[2] = c3;
         cluster1.clear();
         cluster2.clear();
         cluster3.clear();
         cluster1.push_back(c1);
         cluster2.push_back(c2);
         cluster3.push_back(c3);
         return true;
    }
    
    //method to make the clusters
    void KMeans:: cluster(){
        //while the centroids update
        while(setupCentroids()){
            //go through all the data set
            for(County c : all){
                //add to closest cluster
                addToClosest(c);
            }

        }
    }
    
    //method to get the distance from a point to rest of cluster
    float KMeans:: avgDistance(vector<County>&cluster,int index){
        //cumilate euclidean distance
        float total = 0;
        for(int i = 0; i < cluster.size(); ++i){
            if(i != index){
                total += cluster[index].distance(cluster[i]);
            }
        }
        //avg distance from a point to cluster
        float avg = total/(cluster.size()-1);
        return avg;
    }
    
    //method to find distance from cluster from a point
    float KMeans:: distanceFromCluster(County&c,vector<County>&cluster){
        //cumilate distance
        float distance = 0;
        for(County& a : cluster){
            distance += c.distance(a);
        }
        //return distance
        return distance;
    }
    
    //method to return silhoute value
    float KMeans:: silh(vector<County>&a,vector<County>&b,int index){
        float aval = avgDistance(a, index);
        float bval = distanceFromCluster(a[index], b);
        float sil = (bval - aval)/max(bval,aval);
        return sil;
    }
    
    //method to print the silhoute for each cluster
    void KMeans:: printSil(){
        //find the value for cluster 1
        float sil = 0;
        for(int i = 0; i < cluster1.size(); ++i){
            if(distanceFromCluster(cluster1[i],cluster2) < distanceFromCluster(cluster1[i],cluster3)){
                sil += silh(cluster1,cluster2,i);
            }else{
                 sil += silh(cluster1,cluster3,i);
            }
        }
        float avsil = sil/cluster1.size();
        cout << "cluster 1 similarity: " << avsil << endl;
        //find the value for cluster 2
        sil = 0;
        for(int i = 0; i < cluster2.size(); ++i){
            if(distanceFromCluster(cluster2[i],cluster3) < distanceFromCluster(cluster2[i],cluster1)){
                sil += silh(cluster2,cluster3,i);
            }else{
                sil += silh(cluster2,cluster1,i);
            }
        }
        avsil = sil/cluster2.size();
        cout << "cluster 2 similarity: " << avsil << endl;
        //find the value for cluster 3
        sil = 0;
        for(int i = 0; i < cluster3.size(); ++i){
            if(distanceFromCluster(cluster3[i],cluster2) < distanceFromCluster(cluster3[i],cluster1)){
                sil += silh(cluster3,cluster2,i);
            }else{
                sil += silh(cluster3,cluster1,i);
            }
        }
        avsil = sil/cluster3.size();
        cout << "cluster 3 similarity: " << avsil << endl;
        
    }

}
