# VoterMLA
*Machine Learning Algorithms to determine whether a county in U.S would vote for a Republican or Democrat candidate for president using data such as population size and density and candidate voted for in the 2016 election*

##Table of Contents
* [Dataset](#dataset)
* [Supervised Learning] (#supervised-learning)
  * [K-Nearest-Neighbor](#knn)
  * [Perceptron](#perceptron)
  * [ID3] (#id3)
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
| ID3 | 86.23%      |    83.78% |


##KNN
For KNN algorithm a simple eucledian distance formula was used for the attribute values to determine the set of nearby neighbors. For this algorithms various sizes of neighbor set were utilized. The best neighbor set size according to statistics was determined to be 7. Based on which candidate majority of candidate voted, the algorithm made prediction. This algorithm had the best performance with respect to accuracy but to make a prediction for one instance it would iterate through the entire dataset, so for each instance in testing set it would iterate through the entire training set.

##Perceptron
Unlike KNN, the Perceptron algorithm went through the data set only based on the number of times it was trained. For my implementaion, the Perceptron was trained about 5 times. For this algorithm the dataset whether training or testing needs to normalized because it uses this list of weights for each attribute. I initialized a list of weights with the value .1 and set a learning rate of 1, and every iteration of the training set it would attempt to predict 0 or 1 as in which candidate using the weight values and if it guess incorrectly then the weights would be modified based on the learning rate and the error. Every time I trained using Perceptron, I would divide the learning rate by 10 since the next time it goes through the set you would want a smaller effect on the weights. I trained it only 5 times because that returned the best accuracy for the training set.

##ID3
ID3 is a decision tree that makes smaller subsets of the bigger dataset. It essentially splits the data into smaller subsets using the attribute value. For example, if you set split value to 10,000 for the population size attribute, then every county that has a larger population than that would be in right node otherwise, it would be in left node. For this algorithm, the nodes are rather called bins. This algorithm would split until there is no more attribute to split the data on. The best split 


