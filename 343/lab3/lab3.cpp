//---------------------------------------------------------------------------
// lab3.cpp
//---------------------------------------------------------------------------
// This code tests the basic functionality of the classes to perform
// Dijkstra's algorihms and depth-first search for CSS 343 Lab 3.
// It is not meant to exhaustively test the class.
//
// Assumptions:
//   -- students can follow the directions to interface with this file
//   -- text files "data31.txt" and "data32.txt" are formatted as described
//   -- Data file data3uwb provides an additional data set for part 1;
//      it must be edited, as it starts with a description how to use it
//---------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include "graphl.h"
#include "graphm.h"
using namespace std;

int main() {
//    // part 1
//    ifstream infile1("data31.txt");
//    if (!infile1) {
//        cout << "File could not be opened." << endl;
//        return 1;
//    }
//    
//    //for each graph, find the shortest path from every node to all other nodes
//    for(;;){
//        GraphM G;
//        G.buildGraph(infile1);
//        if (infile1.eof())
//            break;
//        G.findShortestPath();
//        G.displayAll();              // display shortest distance, path to cout
//        G.display(3,1);              // display path from node 3 to 1 to cout
//        // may be other calls to display
//    }

    // part 2
    ifstream infile2("data32.txt");
    if (!infile2) {
        cout << "File could not be opened." << endl;
        return 1;
    }
    
    //for each graph, find the depth-first search ordering
    for (;;) {
       GraphL G;
        G.buildGraph(infile2);
        if (infile2.eof())
            break;
        G.displayGraph();
        G.depthFirstSearch();    // find and display depth-first ordering to cout
    }
    
    cout << endl;
    return 0;
}

