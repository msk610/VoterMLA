//
//  perceptron.cpp
//  VoterMLA
//
//  Created by MD Shihabul Kabir on 12/3/16.
//  Copyright © 2016 MD Shihabul Kabir. All rights reserved.
//

#include <stdio.h>
#include "county.h"
#include "perceptron.h"
#include "math.h"

using namespace std;
using namespace CountyStruct;

//Perceptron Namespace
namespace PerceptronAlgo {
    
    //constructor
    Perceptron::Perceptron(vector<County>&train,float rate){
        //initialize members
        learningRate = rate;
        for(int i = 0; i < TOTAL_ATTR; ++i){
            //set weights as 1 to begin
            weights.push_back(1);
        }
        trainingSet = train;
    }
    
    //method to train perceptron
    void Perceptron::train(){
        //go through training set
        for(County c : trainingSet){
            float value = 0.0;
            //go through each attribute
            for(int i = POPULATION; i < TOTAL_ATTR; ++i){
                value += weights[i]*c.member(i);
            }
            //calculate the error
            float error = c.member(0) - value;
            
            //update the weights
            for(int i = POPULATION; i < TOTAL_ATTR; ++i){
                weights[i] = weights[i]+(learningRate*error*c.member(i));
            }
        }
        //update the learning rate
        updateLearningRate();
    }
    
    //method to predict whether a county voted a democrat or republican
    int Perceptron::predict(County &aCounty){
        float value = 0.0;
        //go through each attribute and get the value
        for(int i = POPULATION; i < TOTAL_ATTR; ++i){
            value += weights[i]*aCounty.member(i);
        }
        //round and return
        return round(value);
    }
    
    //method to lower the learning rate after going through the data set once
    void Perceptron::updateLearningRate(){
        //make learning rate 1/10 the previous
        learningRate /= 10;
    }
}
