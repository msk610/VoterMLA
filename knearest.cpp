//
//  knearest.cpp
//  VoterMLA
//
//  Created by MD Shihabul Kabir on 12/5/16.
//  Copyright © 2016 MD Shihabul Kabir. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include "county.h"
#include "knearest.h"

using namespace std;
using namespace CountyStruct;

//K-Nearest Neighbor Namespace
namespace KnearestAlgo{
    
    //constructor
    Knearest::Knearest(vector<County>&train){
        trainingSet = train;
    }
    
    //method to predict whether a county voted a democrat or republican
    int Knearest::predict(County& aCounty){
        //make a pair of distances and counties
        vector<pair<float,float>> distances;
        
        //go through and store each distances with its counties
        for(County c: trainingSet){
            pair<float, float>p;
            p.first = aCounty.distance(c);
            p.second = c.member(0);
            distances.push_back(p);
        }
        
        //sort the vector
        sort(distances.begin(),distances.end());
        //count number or republicans and democrats
        int dems = 0, rep = 0;
        for(int i =0; i < 7; ++i){
            if(distances[i].second > 0) ++dems;
            else ++rep;
        }
        //return which one is greater
        if(dems > rep) return 1;
        return 0;
    }
}
