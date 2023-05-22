# Assigment 01

## **Task 1.1**
* Write an algorithm to check if a node, say A, is good to be the first node to traverse to all the nodes in the network

## **Hints**
* To start with, store the given directed graph using Adjacency Matrix
* Initiate the NodeCovered list with {A}

* Add all nodes reachable in 1-hop from A to NodesCovered list – count the number

* Add all nodes reachable from NodeCovered list in 1 hop – count the number

* Continue the process till one of the following conditions is true 
    - No new node can be explored from current NodesCovered list 
        - Number of covered nodes is less than N
        - A fails as Initiator
    - NodesCovered list has all N nodes in it
        -A qualifies as possible Initiator

## **Task 1.2**
* Improve your solution to list all the nodes for the given use case, that are good to be initiator node for CL algorithm


### Your are requested to upload a single ZIP or RAR file containing the following:
1. Source code with proper remarks 
2. At least two test data sets
3. Screenshot(s) showing execution of your program

The filename should bear your first name followed by "-a1", e.g. the submission from "Piotr" should be a single ZIP (or RAR) file named "Piotr-a1.zip"