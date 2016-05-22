#include <iostream>
#include <stdio.h>

using namespace std;

#include "Headers/Graph.h"
#include "Headers/GridGraph.h"
#include "Headers/PathFinder.h"
#include "Headers/XMLGridGraphParser.h"
#include "Headers/Heuristic.h"
#include "Headers/GridVisualizer.h"
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
    XMLGridGraphParser data("Inputs/DragonAge-Starcraft-somemaps/Starcraft_movingai.com_/Medusa/3868608.xml");
    GridGraph graph(data.getWidth(), data.getHeight(), data.getGrid());
    AStar pathFinder(&graph, Heuristic::chebyshevDistance);

    const GridGraph::Cell* startCell = graph.getCellByCoords(data.getStartHeight(), data.getStartWidth());
    const GridGraph::Cell* endCell = graph.getCellByCoords(data.getEndHeight(), data.getEndWidth());
    pathFinder.findPath(startCell, endCell);

    GridVisualizer map(&graph);
    const vector<const Graph::Node*> path = pathFinder.getFullPath(endCell);
    map.addPath(&path);
    map.drawImage();

    return 0;
}