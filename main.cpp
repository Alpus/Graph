#include <iostream>
#include <stdio.h>

using namespace std;

#include "Headers/Graph.h"
#include "Headers/PathFinder.h"
#include "Headers/XMLGridGraphParser.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void readWeightedGraph(uint64_t* const nodeNumber, vector<tuple<uint64_t, uint64_t, double>>* const edges) {
    cout << "Number of nodes: ";
    cin >> *nodeNumber;
    uint64_t edgeNumber;
    cout << "Number of edges: ";
    cin >> edgeNumber;
    cout << "Edges: \n";

    uint64_t from, to;
    double cost;
    for (int i = 0; i < edgeNumber; ++i) {
        cin >> from >> to >> cost;
        edges->push_back(make_tuple(from, to, cost));
    }
}

int main() {
//    freopen ("Inputs/graph_test","r", stdin);
//    uint64_t n = 0;
//    vector<tuple<uint64_t, uint64_t, double>> edges;
//    readWeightedGraph(&n, &edges);
//    Graph graph(n, edges);
//    DijkstraSearch pathFinder(graph);
//    pathFinder.findPath(*graph[0], *graph.getInfiniteNode());
//    cout << pathFinder.getPathCost(*graph[4]) << endl;
//    for (auto node: pathFinder.getFullPath(*graph[4])) {
//        cout << node->getId() << " ";
//    }


    XMLGridGraphParser data("/home/alpus/Work/Course_work/Implementation/Inputs/Starcraft_movingai.com_/EbonLakes/small_lakes.xml");
    GridGraph graph(data.getWidth(), data.getHeight(), data.getGrid());
    DijkstraSearch pathFinder(graph);
    pathFinder.findPath(*graph.getCellByCoords(data.getStartX(), data.getStartY()), *graph.getInfiniteNode());
    cout << pathFinder.getPathCost(*graph[4]) << endl;
    for (auto node: pathFinder.getFullPath(*graph[4])) {
        cout << node->getId() << " ";
    }
    return 0;
}