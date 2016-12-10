//
//  nesting.cpp
//  VoterMLA
//
//  Created by MD Shihabul Kabir on 12/5/16.
//  Copyright © 2016 MD Shihabul Kabir. All rights reserved.
//

#include <stdio.h>
#include "county.h"
#include "nesting.h"
#include <cmath>
#include <iostream>

using namespace std;
using namespace CountyStruct;

//Algorethmic Nesting Clustering Namespace
namespace NestingClustering {
    //constructor
    Nesting::Nesting(std::vector<County>&counties){
        for(County c : counties){
            //make a node for each county
            NestNode* node = new NestNode();
            node->left = nullptr;
            node->right = nullptr;
            node->cluster.push_back(c);
            clusters.push_back(node);
        }
    }
    
    //method to get the mean of a set of countries
    vector<float>Nesting::mean(std::vector<CountyStruct::County>&counties){
        vector<float>totals;
        for(int i =0; i < TOTAL_ATTR; ++i){
            totals.push_back(0);
        }
        //go through and tally the total sum
        for(County& c : counties){
            for(int i =POPULATION; i < TOTAL_ATTR; ++i){
                totals[i] += c.member(i);
            }
        }
        //calculate the average sums
        for(int i =POPULATION; i < TOTAL_ATTR; ++i){
            totals[i] /= counties.size();
        }
        
        return totals;
    }
    
    //function to get difference between two nodes
    float Nesting::difference(NestNode* aNode, NestNode* bNode){
        float diff = 0;
        vector<float>mean1 = mean(aNode->cluster);
        vector<float>mean2 = mean(bNode->cluster);
        for(int i = POPULATION; i < TOTAL_ATTR; ++i){
            diff += powf(mean1[i]-mean2[i],2);
        }
        //return sum of distance
        return sqrtf(diff);
    }
    
    //function to get the next closest Node
    NestNode* Nesting::closestNode(NestNode* aNode){
        //setup node to return
        NestNode* b = clusters[0];
        float diff = difference(aNode,b);
        
        //go through and find closest
        for(NestNode* n : clusters){
            float local = difference(aNode, n);
            if(local < diff){
                diff = local;
                b = n;
            }
        }
        return b;
    }

    
    //method to cluster
    void Nesting::cluster(){
        //found the biggest cluster
        bool found = false;
        int index = 0;
        while (!found) {
            //get the first item of the vector
            NestNode* l = clusters[index];
            //get the next best node
            NestNode* r = closestNode(l);
            //make a bigger cluster
            NestNode* bigger = new NestNode();
            for(County c : l->cluster){
                bigger->cluster.push_back(c);
            }
            for(County d : r->cluster){
                //add if it isn't already in the bigger cluster
                bool notFound = false;
                for(County i : bigger->cluster){
                    if(i.compare(d)){
                        notFound = true;
                    }
                }
                if(!notFound) bigger->cluster.push_back(d);
                
            }
            //make the child nodes
            bigger->right = r;
            bigger->left = l;
            clusters.push_back(bigger);
            if(bigger->left->cluster.size() + bigger->right->cluster.size() >= 2334){
                found = true;
                break;
            }
            ++index;
        }
    }
    

    
}
