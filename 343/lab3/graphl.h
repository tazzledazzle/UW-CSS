//
//  graphl.h
//  Lab3
//
//  Created by Terence Schumacher on 4/19/14.
//  Copyright (c) 2014 Terence Schumacher. All rights reserved.
//

#ifndef _GRAPHL_H_
#define _GRAPHL_H_
#include "nodedata.h"
#include <iostream>
#define MAXNODES 100

using namespace std;

struct EdgeNode;

struct GraphNode{
	EdgeNode * edgeHead;
	bool visited;
	NodeData adjList;
    
};

struct EdgeNode{
	int adjGraphNode;
	EdgeNode * nextEdge;
};
class GraphL{
	
public:
    GraphL();
    ~GraphL();
    void buildGraph(istream& );
    void displayGraph();
    void depthFirstSearch();
    void makeEmpty();
private:
    GraphNode adjList[MAXNODES];
    int size;
};



#endif /* defined(__Lab3__graphl__) */
