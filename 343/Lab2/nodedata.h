#ifndef NODEDATA_H
#define NODEDATA_H
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

// simple class containing one string to use for testing
// not necessary to comment further

class NodeData {
   friend ostream & operator<<(ostream &, const NodeData &);

public:
   NodeData();          // default constructor, data is set to an empty string
   ~NodeData();          
   NodeData(const string &);      // data is set equal to parameter
   NodeData(const NodeData &);    // copy constructor
   NodeData& operator=(const NodeData &);

   // set class data from data file
   // returns true if the data is set, false when bad data, i.e., is eof
   bool setData(istream&);                

   bool operator==(const NodeData &) const;
   bool operator!=(const NodeData &) const;
   bool operator<(const NodeData &) const;
   bool operator>(const NodeData &) const;
   bool operator<=(const NodeData &) const;
   bool operator>=(const NodeData &) const;

private:
   string data;          
};

#endif

