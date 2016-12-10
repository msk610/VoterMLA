# VoterMLA
*Machine Learning Algorithms to determine whether a county in U.S would vote for a Republican or Democrat candidate for president using data such as population size and density and candidate voted for in the 2016 election*

##Table of Contents
* [Dataset](#dataset)
* [Supervised Learning] (#supervised-learning)
  * K-Nearest-Neighbor(#knn)
  * Perceptron(#perceptron)
  * ID3 (#id3)
* [Unsupervised Learning] (#unsupervised)
  * K-Means (#k-means)
  * Agglomerative Nesting(#agnes)

##Dataset
The dataset that wase used for [training](https://github.com/msk610/VoterMLA/blob/master/votes-train.csv) and [testing] (https://github.com/msk610/VoterMLA/blob/master/votes-test.csv) the algorithms were taken from Kaggle. Each dataset has 10 attributes. The first column shows Democrat and it is 1 or 0, if it is 1 it means that the county voted for the Democrat candidate (Clinton) and if it is 0 then the county voted for Republican candidate (Trump) during 2016 election. The dataset is somewhat biased as most of the counties that were used to train and test the data were counties that voted for the Republican candidate. In order to train and test a specific algorithm simply remove uncomment the specific algorithm that you wish to use.

##Supervised-Learning
For this project three supervised algorithms were implemented, K-Nearest-Neighbor(KNN), Perceptron, and ID3 (Decision Tree). Out of all of those algorithms KNN performed the best as it achieved an accuracy of 100% for the testing set after normalizing the data. The normalization fo the data was implemented by discovering the MAX, MIN, and AVG values of the dataset using excel. Of course a simple a script can be utilized to do that as well. The formula for normalizing the data is:
```
normalized_attr_val = (data[attr]-MIN[attr])/(MAX[attr]-MIN[attr])
```
Normalization is necessary for the perceptron algorithm and it is already implemented in the County data structure, for example for an instance of the County class aCounty you would simply write: `aCounty.normalize()`. Following shows the accuracy statistics attained from the three algorithms with and without the normalization of the data:

| Algorithm        | Not Normalized           | Normalized  |
| ------------- |:-------------:| -----:|
| KNN      | 87.25%      |   100% |
| Perceptron      |    N/A   |   89.96% |
| ID3 | 83.78%      |    83.78% |


