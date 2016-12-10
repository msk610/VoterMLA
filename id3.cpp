//
//  id3.cpp
//  VoterMLA
//
//  Created by MD Shihabul Kabir on 12/4/16.
//  Copyright © 2016 MD Shihabul Kabir. All rights reserved.
//

#include <stdio.h>
#include "county.h"
#include "id3.h"
#include "math.h"

using namespace std;
using namespace CountyStruct;

//ID3 Decision Learning Tree Namespace
namespace ItreeAlgo{
    
    //method to return value with number of democrats and republicans
    pair<int,int> ID3:: getPercentages(std::vector<County>&counties){
        //initialize a pair to track democrats and republicans
        pair<int,int>percent;
        percent.first = 0;
        percent.second = 0;
        
        //go through the vector of counties and keep track
        for(County& c : counties){
            if(c.member(0) > 0) percent.first += 1;
            else percent.second += 1;
        }
        
        return percent;
    }
    
    //method to get entropy of a data
    float ID3:: entropyData(std::pair<int,int>info){
        //initialize a value
        float value = 0;
        //sum the total
        float total = info.first + info.second;
        //use formula to calcuale the value
        value = (-1*(info.first/total)*log2f(info.first/total))-(-1*(info.second/total)*log2f(info.second/total));
        return value;
    }
    
    //method to get entropy of the attribute
    float ID3:: entropyAttr(std::pair<int,int>info, int dataTotal){
        //initialize a value
        float value = 0;
        //sum the total
        float total = info.first + info.second;
        //use formula to calcuale the value
        value = (-1*(info.first/total)*log2f(info.first/total))-(-1*(info.second/total)*log2f(info.second/total));
        return (total/dataTotal)*value;
    }
    
    //method to get the best split
    int ID3:: bestSplit(std::vector<County> counties){
        //initialize the attribute to return as a negative value
        int max = 0;
        for(int i =0; i < binCheck.size(); ++i){
            if (binCheck[i] != SENTINEL){
                max = i;
                break;
            }
        }
        
        //setup max gain and total size
        float maxGain = 0;
        int totalSize = (int)counties.size();
        
        //get the data value of gain of the given set
        pair<int,int>dataPercent = getPercentages(counties);
        float dataGain = entropyData(dataPercent);
        
        //for each attribute go through the set
        for(int i = POPULATION; i < TOTAL_ATTR; ++i){
            
            //check if the attribute was already used for splitting the data
            if(binCheck[i] != SENTINEL){
            
            //make two bins
            vector<County>leftBin,rightBin;
            
            //calculate the value to split on
            float splitVal = ((AVG_DEM[i]-MIN_ALL[i])/(MAX_ALL[i]-MIN_ALL[i]));
            //split data into two sets
            for(County& c : counties){
                if(c.member(i) >= splitVal) leftBin.push_back(c);
                else rightBin.push_back(c);
            }
            //get percentages for left and right bins
            pair<int,int>left = getPercentages(leftBin);
            pair<int,int>right = getPercentages(rightBin);
            
            //get the net gain using the sum of the bins
            float netGain = dataGain - (entropyAttr(left,totalSize) + entropyAttr(right,totalSize));
            
            //reassign max gain
            if(netGain > maxGain){
                maxGain = netGain;
                max = i;
            }
          }
        }
        //return max which contains the attribute int
        return max;
    }
    
    //method to make the tree
    Itree* ID3:: makeTree(std::vector<County>&counties){
        
        //count the number of attributes the data has been split by
        int counter = 0;
        for(float v : binCheck){
            if(v == SENTINEL){
                ++counter;
            }
        }
        //base case for recursive call
        if(counter == binCheck.size() || counties.size() == 0) return nullptr;
        
        //find the best attribute to split on
        int bestAttr = bestSplit(counties);
        if(bestAttr == -1) return nullptr;
        
        //make the node
        Itree* node = new Itree(bestAttr);
        
        //make the two smaller sets
        vector<County>left,right;
        for(County& c : counties){
            //push into the node set
            node->bin.push_back(c);
            //calculate the split value
            float splitVal = ((AVG_DEM[bestAttr]-MIN_ALL[bestAttr])/(MAX_ALL[bestAttr]-MIN_ALL[bestAttr]));
            if(c.member(bestAttr) >= splitVal) left.push_back(c);
            else right.push_back(c);
        }
        //check that the attribute was used to split
        binCheck[bestAttr] = SENTINEL;
        
        //make the childs
        Itree* leftChild = makeTree(left);
        Itree* rightChild = makeTree(right);
        node->leftBin = leftChild;
        node->rightBin = rightChild;
        
        //return the node
        return node;
    }
    
    //method to predict given a county which candidate it voted for
    int ID3:: predict(County& aCounty,Itree* headptr){
        //make a copy of the headptr
        Itree* copy = headptr;
        Itree* prev = copy;
        if(copy == nullptr) return -1;
        
        //make the first split
        int fSplit = copy->attr;
        float fsplitVal = ((AVG_DEM[fSplit]-MIN_ALL[fSplit])/(MAX_ALL[fSplit]-MIN_ALL[fSplit]));
        //move based on that value
        if(aCounty.member(copy->attr) >= fsplitVal) copy = copy->leftBin;
        else copy = copy->rightBin;
        
        //move down the tree until you cant
        while (copy != nullptr) {
            prev = copy;
            //calculate the split value
            int attr = copy->attr;
            float splitVal = ((AVG_DEM[attr]-MIN_ALL[attr])/(MAX_ALL[attr]-MIN_ALL[attr]));
            //move based on that value
            if(aCounty.member(copy->attr) >= splitVal) copy = copy->leftBin;
            else copy = copy->rightBin;
        }
        
        //setup democrat and republican counter
        int dem = 0,rep = 0;
        for(County c : prev->bin){
            //track republican and democrats
            if(c.member(DEMOCRAT) > 0){
                ++dem;
            }
            else ++rep;
        }
    
        
        //return who won
        if(dem > rep) return 1;
        return 0;
        
    }
    
    
    
}

