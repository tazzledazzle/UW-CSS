//
//  graphm.h
//  Lab3
//
//  Created by Terence Schumacher on 4/19/14.
//  Copyright (c) 2014 Terence Schumacher. All rights reserved.
//

#ifndef __Lab3__graphm__
#define __Lab3__graphm__
#define MAXNODES 100

#include <iostream>
#include "nodedata.h"


struct TableType{
    bool visited;       //whether node has been visited
    int dist;           //currently known shortest distance from source
    int path;           //previous node in path of min dist
};
class GraphM {
public:
    
    GraphM();                   //Constructor
    ~GraphM();                  //Destructor
    void buildGraph(ifstream&);          //constructs the graph from the text file
    bool insertEdge();          //inserts an edge between two nodes
    bool removeEdge();          //removes an edge between two nodes
    void findShortestPath();    //constructs from dijkstra's algorithm
    void displayAll();          //displays the results from the shortestPath method
    void display(int, int);     //displays the edge value for spedific 
    
private:
    NodeData data[MAXNODES];            //data for graph nodes information
    int C[MAXNODES][MAXNODES];          //Cost array, the adjacency matrix
    int size;                           //number of nodes in the graph
    TableType T[MAXNODES][MAXNODES];    //stores visited, distance, path
};


#endif /* defined(__Lab3__graphm__) */
