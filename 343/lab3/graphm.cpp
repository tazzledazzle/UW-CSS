//
//  graphm.cpp
//  Lab3
//
//  Created by Terence Schumacher on 4/19/14.
//  Copyright (c) 2014 Terence Schumacher. All rights reserved.
//

#include "graphm.h"
#include <climits>

//----------------------------------------------------------------
// GraphM()
// Constructor
//
GraphM::GraphM(): size(0){
    for (int i = 1; i < MAXNODES; i++){
        for (int j = 1; j < MAXNODES; j++){
            T[i][j].dist = INT_MAX;
            T[i][j].path = 0;
            T[i][j].visited = false;
        }//end for j
    }//end for i

}//end constructor

//----------------------------------------------------------------
// ~GraphM()
// Destructor:
//
GraphM::~GraphM(){

}//end destructor

//----------------------------------------------------------------
// buildGraph()
// Build Graph:
//
void GraphM::buildGraph(ifstream&){

}//end buildGraph

//----------------------------------------------------------------
// insertEdge()
// Insert Edge:
//
bool GraphM::insertEdge(){
    return false;
}//end insertEdge

//----------------------------------------------------------------
// removeEdge()
// Remove Edge:
//
bool GraphM::removeEdge(){
    return false;
}//end removeEdge

//----------------------------------------------------------------
// findShortestPath()
// Find Shortest Path:
//
void GraphM::findShortestPath(){

}//end findShortestPath

//----------------------------------------------------------------
// displayAll()
// Display All:
//
void GraphM::displayAll(){

}//end displayAll

//----------------------------------------------------------------
// display()
// Display:
//
void GraphM::display(int, int){

}//end display



