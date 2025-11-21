#include <stdio.h>
#include "Graph.hpp"

// Takes in the string label of a vertex and outputs the pointer to the vertex object associated with that key in the
// map of the graph vertices, otherwise returns nullptr.
Vertex* Graph::getVertex(std::string labelkey) const {
    auto it = vertices.find(labelkey);
    if(it != vertices.end()){
        return it->second;
    }
    return nullptr;
}

/*
    Graph class implementation:
==============================================================================================================================
- addVertex(label1): Creates a Vertex object with member label = label1 given that an entry in the map with key = label1
     does not already exist (using getVertex(labelKey)).
*/