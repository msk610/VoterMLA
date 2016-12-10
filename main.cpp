//
//  main.cpp
//  VoterMLA
//
//  Created by MD Shihabul Kabir on 12/3/16.
//  Copyright © 2016 MD Shihabul Kabir. All rights reserved.
//

#include <iostream>
#include "county.h"
#include "perceptron.h"
#include "id3.h"
#include "kmeans.h"
#include "nesting.h"
#include "knearest.h"
#include <vector>
#include <string>
#include <fstream>

using namespace std;
using namespace CountyStruct;
using namespace KnearestAlgo;
using namespace PerceptronAlgo;
using namespace ItreeAlgo;
using namespace KmeansCluster;
using namespace NestingClustering;

vector<County> getData(const string& filename){
    //setup an empty vector
    vector<County>dataset;
    //open the file
    ifstream input(filename);
    //check the file
    if(!input) exit(-1);
    //string buffer
    string line;
    //skip first line
    getline(input,line);
    
    while(getline(input,line)){
        //setup empty vector of floats
        vector<float>datas;
        //get each attribute
        //democrat
        int i1 = line.find_first_of(',');
        datas.push_back(stof(line.substr(0,i1)));
        //population
        int i2 = line.find_first_of(',', i1+1);
        datas.push_back(stof(line.substr(i1+1, i2-i1-1)));
        //population change
        int i3 = line.find_first_of(',', i2+1);
        datas.push_back(stof(line.substr(i2+1, i3-i2-1)));
        //age 65 over
        int i4 = line.find_first_of(',', i3+1);
        datas.push_back(stof(line.substr(i3+1, i4-i3-1)));
        // population black
        int i5 = line.find_first_of(',', i4+1);
        datas.push_back(stof(line.substr(i4+1, i5-i4-1)));
        // population hispanic
        int i6 = line.find_first_of(',', i5+1);
        datas.push_back(stof(line.substr(i5+1, i6-i5-1)));
        // population bachelors degree
        int i7 = line.find_first_of(',', i6+1);
        datas.push_back(stof(line.substr(i6+1, i7-i6-1)));
        // population income
        int i8 = line.find_first_of(',', i7+1);
        datas.push_back(stof(line.substr(i7+1, i8-i7-1)));
        // population poverty
        int i9 = line.find_first_of(',',i8+1);
        datas.push_back(stof(line.substr(i8+1, i9-i8-1)));
        // population density
        int i10 = line.find_first_of(',', i9+1);
        datas.push_back(stof(line.substr(i9+1, i10-i9-1)));
        
        //make the county
        County aCounty = County(datas);
        //normalize the county
        //aCounty.normalize();
        //append it to the set
        dataset.push_back(aCounty);
    }
    
    return dataset;
}

int main(int argc, const char * argv[]) {
    
    /*
     //K-Nearest Neighbor usage
     //==================================================================//
    //get training data
    vector<County>trainingData = getData("/Users/mdkabir/Documents/voter_data_machine_learning/votes-train.csv");
    Knearest knearest = Knearest(trainingData);
    //get testing data
    vector<County>testingData = getData("/Users/mdkabir/Documents/voter_data_machine_learning/votes-test.csv");
    //keep an accuracy counter
    float correct = 0;
    for(County c : testingData){
        if(knearest.predict(c) == c.member(0)) correct += 1;
    }
    cout << "Accuracy: " << (correct/testingData.size())*100 << "%" << endl;
    //==================================================================//
    */
    

    /*
     //Perceptron usage
     //==================================================================//
    //get training data
    vector<County>trainingData = getData("/Users/mdkabir/Documents/voter_data_machine_learning/votes-train.csv");
    //initialize perceptron
    Perceptron perceptron = Perceptron(trainingData,.1);
    //train perceptron 5 times
    for(int i =0; i < 5; ++i){
        perceptron.train();
    }
    //go through testing data
    vector<County>testingData = getData("/Users/mdkabir/Documents/voter_data_machine_learning/votes-test.csv");
    //keep an accuracy counter
    float correct = 0;
    for(County& c : testingData){
        if(perceptron.predict(c) == c.member(0)) correct += 1;
    }
    cout << "Accuracy: " << (correct/testingData.size())*100 << "%" << endl;
    //==================================================================//
    */
    
    /*
    //ID3 usage
    //==================================================================//
    //get training data
    vector<County>trainingData = getData("/Users/mdkabir/Documents/voter_data_machine_learning/votes-train.csv");
    //initialize id3
    ID3 id3 = ID3();
    //make the tree and get the headptr
    Itree* headptr = id3.makeTree(trainingData);
    //go through testing data
    vector<County>testingData = getData("/Users/mdkabir/Documents/voter_data_machine_learning/votes-test.csv");
    //keep an accuracy counter
    float correct = 0;
    for(County& c : testingData){
        Itree* cp = headptr;
        //cout << pred << endl;
        if(id3.predict(c,cp) == c.member(0)) correct += 1;
    }
    cout << "Accuracy: " << (correct/testingData.size())*100 << "%" << endl;
    
     //==================================================================//
     */
     
    
    /*
    //K-Means Clustering
    //==================================================================//
    //get training data
    vector<County>trainingData = getData("Enter Your Path to Training Data");
    //initialize kmeans
    KMeans km = KMeans();
    km.initialize(trainingData);
    km.cluster();
    km.printSil();
    //==================================================================//
     */
    
    
    //Agglomerative Clustering
    //==================================================================//
    /*
    //get training data
    vector<County>trainingData = getData("Enter Your Path to Testing Data");
    //initialize nesting
    Nesting nesting = Nesting(trainingData);
    //build the tree
    nesting.cluster();
    */
    
    //==================================================================//
    return 0;
}
