#ifndef PATHFINDER_PATHFINDER_H
#define PATHFINDER_PATHFINDER_H

#include "Graph.h"

class Graph::PathFinder {
public:
    class Costs {
        vector<double> costs;

    public:
        Costs(const Graph&);
        double* const operator[](const Graph::Node&);
    };

    PathFinder(Graph&);

    virtual void findPath(const Graph::Node& begin, const Graph::Node& goal) = 0;

    const double getPathCost(const Graph::Node& goal);
    virtual const vector<Graph::Node*> getFullPath(Node &goal)=0;
protected:
    Costs costs;

    Graph* graph;
    const Graph::Node* begin;
};

class Graph::HeuristicSearch : protected PathFinder {
protected:
    const double getMinCost(const Graph::Node::Edge&);

    virtual const double getHeuristic(const Graph::Node&)=0;

public:
    HeuristicSearch(Graph& graph) : PathFinder(graph) {};

    void findPath(const Graph::Node& begin, const Graph::Node& goal);
    const vector<Graph::Node*> getFullPath(Node &goal);
};

class Graph::DijkstraSearch : private HeuristicSearch {
    const double getHeuristic(const Graph::Node&);

public:
    DijkstraSearch(Graph& graph) : HeuristicSearch(graph){};
};


#endif //PATHFINDER_PATHFINDER_H
