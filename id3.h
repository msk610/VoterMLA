//
//  id3.h
//  VoterMLA
//
//  Created by MD Shihabul Kabir on 12/3/16.
//  Copyright © 2016 MD Shihabul Kabir. All rights reserved.
//

#ifndef id3_h
#define id3_h

#include "county.h"
#include <vector>

//ID3 Decision Learning Tree Namespace
namespace ItreeAlgo {
    //set a sentinel value that will be used to check whether an attribute was used to split
    const float SENTINEL = -9999.9999;
    
    //Node Structure to build and traverse the tree
    struct Itree{
        //members
        Itree* leftBin;
        Itree* rightBin;
        
        //int to store the attribute
        int attr;
        std::vector<CountyStruct::County>bin;
        
    public:
        //constructor
        Itree(int at, Itree* first = nullptr, Itree* second = nullptr){
            //initialize members
            attr = at;
            leftBin = first;
            rightBin = second;
        }
    };
    
    //Data Structure to process ID3 algorithm
    class ID3{
    private:
        //use vector to check if an attribute was already used for splitting
        std::vector<float>binCheck = {SENTINEL,0,0,0,0,0,0,0,0,0};
    public:
        //method to return value with number of democrats and republicans
        std::pair<int,int> getPercentages(std::vector<CountyStruct::County>&counties);
        
        //method to get entropy of the data
        float entropyData(std::pair<int,int>info);
        
        //method to get entropy of the attribute
        float entropyAttr(std::pair<int,int>info, int dataTotal);
        
        //method to get the best split
        int bestSplit(std::vector<CountyStruct::County> counties);
        
        //method to make the tree
        Itree* makeTree(std::vector<CountyStruct::County>&counties);
        
        //method to predict given a county
        int predict(CountyStruct::County& aCounty,Itree* headptr);
    };
    
    
}




#endif /* id3_h */
