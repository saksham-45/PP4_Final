#ifndef GRAPH_H
#define GRAPH_H

#include "GraphBase.hpp"
#include <unordered_map>
#include <utility>
#include <vector>
#include <string>

class Vertex;

// Define a value of infinity for comparison/initialization
#define infinity static_cast<unsigned long>(~0)

/*PriorityQueue Class: Unique Indexed priority queue implementation for performing Dijkstra's algorithm
- Uses vector heap for storage
- Stores pairs of (distance, vertex)
- Uses "distance" as the key for sorting entries
*/
class PriorityQueue {
    std::vector<std::pair<unsigned long, Vertex*>> heap;
    void bubbleUp(int index);
    void bubbleDown(int index);

public:
    PriorityQueue() = default;

    bool isEmpty() const{return heap.empty();};
    void push(unsigned long dist, Vertex* v);
    std::pair<unsigned long, Vertex*> pop();
};
/*Edge Class: implementation of undirected edge 
*/
class Edge{
    public:
    Vertex* u;
    Vertex* v;
    unsigned long weight;
    
    // returns the other vertex in the pair (u,v) given that the input is u or v
    // otherwise returns nullptr.
    // 'inline' in case of override (header file function implementation)
    inline Vertex* getOtherVertex(Vertex* currentVertex){
        if(currentVertex == u){
            return v;
        }else if(currentVertex == v){
            return u;
        }
        return nullptr;
    }

};
/*Vertex Class: 
*/
class Vertex{
    public:
    std :: string label;
    std::vector<Edge*> adjEdges; //adjacency list (label.adjEdges.begin() for iterator)

    // For Dijkstra's 
    unsigned long distance;
    Vertex* previous;
    bool visited;
    // Resets/sets state for new shortestPath calculation
    // i.e. for(auto const& [label, v]: vertices) {v->resetState();}
    // 'inline' in case of override (header file function implementation)
    inline void resetState(){ 
        distance = infinity; 
        previous = nullptr;
        visited = false;
    }


};
class Graph : public GraphBase{
public:
    // Using std::unordered_map for the vertex sequence
    // provides ease of use in retrieving by lable
    // without sacrificing constant time complexity.
    std::unordered_map<std::string, Vertex*> vertices;

    Graph() = default; // default in case of memcpy
    ~Graph() override = default;

    void addVertex(std::string label) override;
    void removeVertex(std::string label) override;
    void addEdge(std::string label1, std::string label2, unsigned long weight) override;
    void removeEdge(std::string label1, std::string label2) override;
    /*shortestPath(): 
    - finds shortest path between two vertexes by performing dijkstra's algorithm
      over a 
    algorithm:
      Input: Weighted graph G ()
    */
    unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) override;

};

#endif
