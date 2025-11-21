#include "GraphBase.hpp"
#include "Graph.hpp"
#include <limits>
#include <queue>
#include <algorithm>

// ---------------- PriorityQueue Helpers ----------------

void PriorityQueue::bubbleUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index].first >= heap[parent].first) break;

        std::swap(heap[index], heap[parent]);
        index = parent;
    }
}

void PriorityQueue::bubbleDown(int index) {
    int size = heap.size();
    while (true) {
        int left = 2*index + 1;
        int right = 2*index + 2;
        int smallest = index;

        if (left < size && heap[left].first < heap[smallest].first)
            smallest = left;
        if (right < size && heap[right].first < heap[smallest].first)
            smallest = right;
        if (smallest == index) break;

        std::swap(heap[index], heap[smallest]);
        index = smallest;
    }
}

void PriorityQueue::push(unsigned long dist, Vertex* v) {
    heap.push_back({dist, v});
    bubbleUp(heap.size() - 1);
}

std::pair<unsigned long, Vertex*> PriorityQueue::pop() {
    if (heap.empty()) return {infinity, nullptr};

    auto top = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    if (!heap.empty()) bubbleDown(0);

    return top;
}

// ---------------- Graph Functions ----------------

void Graph::addVertex(std::string label) {
    if (vertices.count(label)) return;
    Vertex* v = new Vertex();
    v->label = label;
    v->resetState();
    vertices[label] = v;
}

void Graph::removeVertex(std::string label) {
    if (!vertices.count(label)) return;

    Vertex* target = vertices[label];

    for (auto& [lbl, v] : vertices) {
        v->adjEdges.erase(
            std::remove_if(
                v->adjEdges.begin(),
                v->adjEdges.end(),
                [&](Edge* e){ return e->u == target || e->v == target; }
            ),
            v->adjEdges.end()
        );
    }

    delete target;
    vertices.erase(label);
}

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight) {
    if (!vertices.count(label1)) addVertex(label1);
    if (!vertices.count(label2)) addVertex(label2);

    Vertex* u = vertices[label1];
    Vertex* v = vertices[label2];

    Edge* e = new Edge();
    e->u = u;
    e->v = v;
    e->weight = weight;

    u->adjEdges.push_back(e);
    v->adjEdges.push_back(e);
}

void Graph::removeEdge(std::string label1, std::string label2) {
    if (!vertices.count(label1) || !vertices.count(label2)) return;

    Vertex* u = vertices[label1];
    Vertex* v = vertices[label2];

    auto removeFrom = [&](Vertex* x) {
        x->adjEdges.erase(
            std::remove_if(
                x->adjEdges.begin(),
                x->adjEdges.end(),
                [&](Edge* e){ return (e->u == u && e->v == v) || (e->u == v && e->v == u); }
            ),
            x->adjEdges.end()
        );
    };

    removeFrom(u);
    removeFrom(v);
}

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string>& path) {
    if (!vertices.count(startLabel) || !vertices.count(endLabel)) return infinity;

    for (auto& [lbl, v]: vertices) v->resetState();

    Vertex* start = vertices[startLabel];
    Vertex* goal = vertices[endLabel];

    PriorityQueue pq;
    start->distance = 0;
    pq.push(0, start);

    while (!pq.isEmpty()) {
        auto [dist, current] = pq.pop();
        if (!current || current->visited) continue;

        current->visited = true;
        if (current == goal) break;

        for (Edge* e : current->adjEdges) {
            Vertex* next = e->getOtherVertex(current);
            if (!next || next->visited) continue;

            unsigned long newDist = current->distance + e->weight;
            if (newDist < next->distance) {
                next->distance = newDist;
                next->previous = current;
                pq.push(newDist, next);
            }
        }
    }

    if (goal->distance == infinity) return infinity;

    std::vector<std::string> rev;
    for (Vertex* v = goal; v; v = v->previous) rev.push_back(v->label);
    std::reverse(rev.begin(), rev.end());
    path = rev;

    return goal->distance;
}