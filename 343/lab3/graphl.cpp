//
//  graphl.cpp
//  Lab3
//
//  Created by Terence Schumacher on 4/19/14.
//  Copyright (c) 2014 Terence Schumacher. All rights reserved.
//

#include "graphl.h"

using namespace std;

// Uses getline from string class, included in nodedata.h .
// Be sure to include nodedata.h which includes <string> .

void GraphL::buildGraph(istream& infile) {
    int fromNode, toNode;              // from and to node ends of edge
    
    makeEmpty();                       // clear the graph of memory
    
    infile >> size;                    // read the number of nodes
    if (infile.eof()) return;          // stop if no more data
    
    string s;                          // used to read through to end of line
    getline(infile, s);
    
    // read graph node information
    for (int i=1; i <= size; i++) {
        // read using setData of the NodeData class,
        // something like:
        //    adjList[i].data.setData(infile);
        // where adjList is the array of GraphNodes and
        // data is the NodeData object inside of GraphNode
    }
    
    // read the edge data and add to the adjacency list
    for (;;) {
        infile >> fromNode >> toNode;
        if (fromNode ==0 && toNode ==0) return;     // end of edge data
        
        // insert the edge into the adjacency list for fromNode
    }
}

