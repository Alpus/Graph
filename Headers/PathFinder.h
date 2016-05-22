#ifndef PATHFINDER_PATHFINDER_H
#define PATHFINDER_PATHFINDER_H

#include "Graph.h"

class PathFinder {
public:
    class Costs {
        vector<double> costs;

    public:
        Costs(const Graph* const);
        double* const operator[](const Graph::Node* const);
        double* const operator[](const uint64_t);
    };

    PathFinder(Graph* const);

    virtual void findPath(const Graph::Node* const begin, const Graph::Node* const goal) = 0;

    const double* const getPathCost(const Graph::Node* const goal);
    virtual const vector<const Graph::Node*> getFullPath(const Graph::Node * const goal)=0;
protected:
    Costs costs;

    Graph* graph;
    const Graph::Node* begin;
};

class HeuristicSearch : public PathFinder {
protected:
    const double getMinCost(const Graph::Edge* const);
    virtual const double getHeuristic(const Graph::Node* const)=0;

public:
    HeuristicSearch(Graph* const graph) : PathFinder(graph) {};

    void findPath(const Graph::Node* const begin, const Graph::Node* const goal);
    const vector<const Graph::Node*> getFullPath(const Graph::Node * const goal);
};

class DijkstraSearch : public HeuristicSearch {
    const double getHeuristic(const Graph::Node* const);

public:
    DijkstraSearch(Graph* const graph) : HeuristicSearch(graph) {};
};


#endif //PATHFINDER_PATHFINDER_H
