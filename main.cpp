#include <iostream>
#include <vector>
#include "Graph.hpp"

int main() {
    Graph g;

    //  a sample graph 
    g.addVertex("1");
    g.addVertex("2");
    g.addVertex("3");
    g.addVertex("4");
    g.addVertex("5");
    g.addVertex("6");

    g.addEdge("1", "2", 7);
    g.addEdge("1", "3", 9);
    g.addEdge("1", "6", 14);
    g.addEdge("2", "3", 10);
    g.addEdge("2", "4", 15);
    g.addEdge("3", "4", 11);
    g.addEdge("3", "6", 2);
    g.addEdge("4", "5", 6);
    g.addEdge("5", "6", 9);

    std::vector<std::string> path;

    unsigned long cost = g.shortestPath("1", "5", path);

    if (cost == infinity) {
        std::cout << "No path found between given vertices.\n";
        return 0;
    }

    std::cout << "Shortest Path Cost: " << cost << "\n";
    std::cout << "Path: ";

    for (size_t i = 0; i < path.size(); i++) {
        std::cout << path[i];
        if (i < path.size() - 1)
            std::cout << " -> ";
    }

    std::cout << "\n";

    return 0;
}