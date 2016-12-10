//
//  county.cpp
//  VoterMLA
//
//  Created by MD Shihabul Kabir on 12/3/16.
//  Copyright © 2016 MD Shihabul Kabir. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include "county.h"
#include "math.h"

using namespace std;

//County Namespace
namespace CountyStruct {
    
        //constructor
        County::County(const vector<float>&input){
            //initialize data member
            for(float data : input){
                datas.push_back(data);
            }
        }
    
        //method to get total sum of data
        float County:: totalSum(){
            //cummilate sum
            float total = 0;
            for(float data : datas){
                total += data;
            }
            return total;
        }
    
        //method to return whether the county voted for democrat candidate
        const bool County:: democrat(){
            //check if the first member is 1
            return datas[DEMOCRAT] > 0;
        }
    
        //method to get an attribute
        float County:: member(int attr){
            //check for edge case
            if(attr < DEMOCRAT || attr > DENSITY) return -1.0;
            //return attribute
            return datas[attr];
        }
    
        //method to return eucledian distance from another county
        float County::distance(County& aCounty){
            float val = 0;
            for(int i =0; i < 10; ++i){
                //accumulate the difference squared
                val += powf(datas[i]-aCounty.member(i),2);
            }
            //return the sqrt of the differences
            return sqrtf(val);
        }
    
        //operator to compare counties
        bool County::compare(County& aCounty){
            //loop through and check each attribute
            for(int i = 0; i < datas.size(); ++i){
                //if one the the attributes don't match return false
                if(member(i) != aCounty.member(i))return false;
            }
            //at the end return true
            return true;
        }
    
        //method to normalize the data
        void County::normalize(){
            for(int i = POPULATION; i < TOTAL_ATTR; ++i){
                //normalize each attribute using the min and max of the set
                datas[i] = ((datas[i]-MIN_ALL[i])/(MAX_ALL[i]-MIN_ALL[i]));
            }
        }
    
        //method to set attribute of a county
        void County::setAttribute(int index, float val){
            //check edge case
            if(index < DEMOCRAT || index > DENSITY) return;
            datas[index] = val;
        }

}
