//
//  nesting.h
//  VoterMLA
//
//  Created by MD Shihabul Kabir on 12/5/16.
//  Copyright © 2016 MD Shihabul Kabir. All rights reserved.
//

#ifndef nesting_h
#define nesting_h

#include "county.h"
#include <vector>

//Algorithmic Nesting Clustering
namespace NestingClustering {
    //Tree Struct for Nesting
    struct NestNode{
        //members
        NestNode* left;
        NestNode* right;
        std::vector<CountyStruct::County>cluster;
    };
    
    class Nesting{
    public:
        //member to store the cluster
        std::vector<NestNode*>clusters;
        //constructor
        Nesting(std::vector<CountyStruct::County>&counties);
        
        //method to get the mean of a set of countries
        std::vector<float>mean(std::vector<CountyStruct::County>&counties);
        
        //method to get difference between two nodes
        float difference(NestNode* aNode, NestNode* bNode);
        
        //method to get the next closest Node
        NestNode* closestNode(NestNode* aNode);
        
        //method to cluster
        void cluster();
        
    };
}

#endif /* nesting_h */
