//
//  perceptron.h
//  VoterMLA
//
//  Created by MD Shihabul Kabir on 12/3/16.
//  Copyright © 2016 MD Shihabul Kabir. All rights reserved.
//

#ifndef perceptron_h
#define perceptron_h


#include "county.h"
#include <vector>


//Perceptron Namespace
namespace PerceptronAlgo {
    
    //Data structure to process the perceptron algorithm
    class Perceptron{
    
    private:
        //Member to manage learning rate
        float learningRate;
        //Member to store weights
        std::vector<float>weights;
        //Member to store training data set
        std::vector<CountyStruct::County>trainingSet;
    
    public:
        //constructor
        Perceptron(std::vector<CountyStruct::County>&train,float rate);
        
        //method to train perceptron
        void train();
        
        //method to predict whether a county voted a democrat or republican
        int predict(CountyStruct::County& aCounty);
        
        //method to update learning rate
        void updateLearningRate();
    };

    
}





#endif /* perceptron_h */
