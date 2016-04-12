#include <iostream>
#include <stdio.h>

using namespace std;

#include "Headers/Graph.h"
#include "Headers/PathFinder.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void readWeightedGraph(uint32_t* const nodeNumber, vector<tuple<uint32_t, uint32_t, double>>* const edges) {
    cout << "Number of nodes: ";
    cin >> *nodeNumber;
    uint32_t edgeNumber;
    cout << "Number of edges: ";
    cin >> edgeNumber;
    cout << "Edges: \n";

    uint32_t from, to;
    double cost;
    for (int i = 0; i < edgeNumber; ++i) {
        cin >> from >> to >> cost;
        edges->push_back(make_tuple(from, to, cost));
    }
}

int main() {
    freopen ("input","r", stdin);
    uint32_t n = 0;
    vector<tuple<uint32_t, uint32_t, double>> edges;
    readWeightedGraph(&n, &edges);
    Graph graph(n, edges);
    DijkstraSearch pathFinder(graph);
    pathFinder.findPath(*graph[0], *graph.getInfiniteNode());
    cout << pathFinder.getPathCost(*graph[4]) << endl;
    for (auto node: pathFinder.getFullPath(*graph[4])) {
        cout << node->getId() << " ";
    }

    return 0;
}