//
//  county.h
//  VoterMLA
//
//  Created by MD Shihabul Kabir on 12/3/16.
//  Copyright © 2016 MD Shihabul Kabir. All rights reserved.
//

#ifndef county_h
#define county_h

#include <vector>

//setup global variables for attributes
const int DEMOCRAT = 0;
const int POPULATION = 1;
const int POP_CHANGE = 2;
const int AGE_OVER = 3;
const int BLACK = 4;
const int HISPANIC = 5;
const int EDU_B = 6;
const int INCOME = 7;
const int POVERTY = 8;
const int DENSITY = 9;
const int TOTAL_ATTR = 10;

//setup global variables for MAX,MIN,and AVG values of counties found using excel
const std::vector<float>MAX_ALL = {0,10116705,27.5,52.9,.851,.952,74.4,122238,53.2,20553.6};
const std::vector<float>MIN_ALL = {0,86,-17,6,0,.002,5.1,19986,.9,.1};
const std::vector<float>AVG_ALL = {0,98776.5,.39,17.67,.09,.09,19.6,45621.1,16.7,211.96};
const std::vector<float>AVG_DEM = {0,337478.96,1.48,14.70,.23,.15,27.33,48842.17,19.53,839.15};


//County Namespace
namespace CountyStruct {
    
    //County structure to store information about a county
    class County{
    private:
        //Member to store information about county
        std::vector<float>datas;
        
    public:
        //constructor
        County(){}; //default
        County(const std::vector<float>&input); //constructor that takes in a dataset
        
        //method to get total sum of data
        float totalSum();
        
        //method to return whether the county voted for democrat candidate
        const bool democrat();
        
        //method to return eucledian distance from another county
        float distance(County& aCounty);
        
        //method to get an attribute
        float member(int attr);
        
        //operator to compare counties
        bool compare(County& aCounty);
        
        //method to normalize the data
        void normalize();
        
        //method to set the value of a specific attribute
        void setAttribute(int index, float val);
    };

    
}



#endif /* county_h */
