#include <iostream>
#include <vector>
#include "Graph.hpp"

using namespace std;

int main() {
    // ============================================================
    // TEST 1 — PROVIDED SAMPLE GRAPH
    // Expected:
    // Cost: 20
    // Path: 1 -> 3 -> 6 -> 5
    // ============================================================
    {
        cout << "===== TEST 1: Provided Example =====\n";

        Graph g;
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

        vector<string> path;
        unsigned long cost = g.shortestPath("1", "5", path);

        cout << "Cost = " << cost << "\nPath: ";
        for (auto& s : path) cout << s << " ";
        cout << "\n\n";
    }


    // ============================================================
    // TEST 2 — DIRECT CONNECTION
    // Expected:
    // Cost = 5
    // Path: A B
    // ============================================================
    {
        cout << "===== TEST 2: Direct Connection =====\n";

        Graph g;
        g.addVertex("A");
        g.addVertex("B");
        g.addEdge("A", "B", 5);

        vector<string> path;
        unsigned long cost = g.shortestPath("A", "B", path);

        cout << "Cost = " << cost << "\nPath: ";
        for (auto& s : path) cout << s << " ";
        cout << "\n\n";
    }


    // ============================================================
    // TEST 3 — NO PATH EXISTS
    // Expected:
    // Cost = infinity
    // Output message: "Correct: No path found."
    // ============================================================
    {
        cout << "===== TEST 3: No Path Exists =====\n";

        Graph g;
        g.addVertex("A");
        g.addVertex("B");
        g.addVertex("C");

        g.addEdge("A", "B", 3);
        // C is isolated

        vector<string> path;
        unsigned long cost = g.shortestPath("A", "C", path);

        if (cost == infinity)
            cout << "Correct: No path found.\n\n";
        else
            cout << "ERROR: Expected no path.\n\n";
    }


    // ============================================================
    // TEST 4 — EDGE REMOVAL CHANGES SHORTEST PATH
    // Expected:
    // Before removal: cost = 2 (1 → 2 → 3)
    // After removal:  cost = 10 (1 → 3)
    // ============================================================
    {
        cout << "===== TEST 4: Edge Removal =====\n";

        Graph g;
        g.addVertex("1");
        g.addVertex("2");
        g.addVertex("3");

        g.addEdge("1", "2", 1);
        g.addEdge("2", "3", 1);
        g.addEdge("1", "3", 10);

        vector<string> path;

        unsigned long cost1 = g.shortestPath("1", "3", path);
        cout << "Before removal: cost=" << cost1 << ", Path: ";
        for (auto& s : path) cout << s << " ";
        cout << "\n";

        g.removeEdge("2", "3");

        unsigned long cost2 = g.shortestPath("1", "3", path);
        cout << "After removal:  cost=" << cost2 << ", Path: ";
        for (auto& s : path) cout << s << " ";
        cout << "\n\n";
    }


    // ============================================================
    // TEST 5 — LARGE GRAPH (CHAIN OF 10)
    // Expected:
    // Cost = 9
    // Path: 1 2 3 4 5 6 7 8 9 10
    // ============================================================
    {
        cout << "===== TEST 5: Large 10-Node Chain =====\n";

        Graph g;
        for (int i = 1; i <= 10; i++)
            g.addVertex(to_string(i));

        for (int i = 1; i < 10; i++)
            g.addEdge(to_string(i), to_string(i+1), 1);

        vector<string> path;
        unsigned long cost = g.shortestPath("1", "10", path);

        cout << "Cost = " << cost << "\nPath: ";
        for (auto& s : path) cout << s << " ";
        cout << "\n\n";
    }


    // ============================================================
    // TEST 6 — MULTIPLE EQUAL SHORTEST PATHS
    // Expected (either OK):
    // Cost = 2
    // Path: A B D
    // OR
    // Path: A C D
    // ============================================================
    {
        cout << "===== TEST 6: Multiple Equal Shortest Paths =====\n";

        Graph g;
        g.addEdge("A", "B", 1);
        g.addEdge("B", "D", 1);

        g.addEdge("A", "C", 1);
        g.addEdge("C", "D", 1);

        vector<string> path;
        unsigned long cost = g.shortestPath("A", "D", path);

        cout << "Cost = " << cost << "\nPath: ";
        for (auto& s : path) cout << s << " ";
        cout << "\n\n";
    }


    // ============================================================
    // TEST 7 — REMOVE VERTEX
    // Expected:
    // Removing Y breaks X → Z connection.
    // Cost = infinity
    // Message: "Correct: No path (Y removed)"
    // ============================================================
    {
        cout << "===== TEST 7: Remove Vertex =====\n";

        Graph g;

        g.addEdge("X", "Y", 4);
        g.addEdge("Y", "Z", 4);

        g.removeVertex("Y");

        vector<string> path;
        unsigned long cost = g.shortestPath("X", "Z", path);

        if (cost == infinity)
            cout << "Correct: No path (Y removed)\n\n";
        else
            cout << "ERROR: Path should not exist.\n\n";
    }

    return 0;
}
