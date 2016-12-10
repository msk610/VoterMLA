//
//  knearest.h
//  VoterMLA
//
//  Created by MD Shihabul Kabir on 12/5/16.
//  Copyright © 2016 MD Shihabul Kabir. All rights reserved.
//

#ifndef knearest_h
#define knearest_h

#include "county.h"
#include <vector>


//K-Nearest Neighbor Namespace
namespace KnearestAlgo {
    
    //Data structure to process knn algorithm
    class Knearest{
        
    private:
        //Member to store training set
        std::vector<CountyStruct::County>trainingSet;
        
    public:
        //constructor
        Knearest(std::vector<CountyStruct::County>&train);
        
        //method to predict whether a county voted a democrat or republican
        int predict(CountyStruct::County& aCounty);
    };
    
    
}

#endif /* knearest_h */
