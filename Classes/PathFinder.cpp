#include "../Headers/Graph.h"
#include "../Headers/PathFinder.h"

#include <algorithm>
#include <set>
#include <math.h>

using std::set;
using std::reverse;

const double* const PathFinder::getPathCost(const Graph::Node* const goal) {
    return costs[goal];
}

PathFinder::Costs::Costs(const Graph* const graph) {
    costs.assign(graph->getSize(), numeric_limits<double>::infinity());
}

PathFinder::PathFinder(Graph* const graph): graph(graph), costs(Costs(graph)) {}

double* const PathFinder::Costs::operator[](const Graph::Node* const node) {
    return &costs[node->getId()];
}

double *const PathFinder::Costs::operator[](const uint64_t number) {
    return &costs[number];
}

const vector<const Graph::Node*> HeuristicSearch::getFullPath(const Graph::Node* const goal) {
    if (*getPathCost(goal) == numeric_limits<double>::infinity()) {
        return vector<const Graph::Node*>();
    }
    vector<const Graph::Node*> pathOrder;
    pathOrder.push_back(goal);

    const Graph::Node* curNode = goal;

    const vector<Graph::Edge>* edges;
    double destCost;
    const Graph::Node* destNode;
    while (curNode != begin) {
        edges = curNode->getEdges();
        for (auto edgeIter = edges->begin(); edgeIter != edges->end(); ++edgeIter) {
            if (edgeIter->getType() == Graph::EdgeType::Backward ||
                edgeIter->getType() == Graph::EdgeType::BiDirect) {

                destNode = edgeIter->getDest();
                destCost = *costs[destNode];
                if (std::abs(*costs[curNode] - edgeIter->getCost() - destCost) < 0.01) {
                    pathOrder.push_back(destNode);
                    curNode = destNode;
                    break;
                }
            }
        }
    }

    reverse(pathOrder.begin(), pathOrder.end());
    return pathOrder;
}

const bool operator<(tuple<double, const Graph::Node*> first,
                     tuple<double, const Graph::Node*> second) {
    return get<0>(first) < get<0>(second);
}

const double HeuristicSearch::getMinCost(const Graph::Edge * const edge) {
    return *costs[edge->getFrom()] + edge->getCost();
}

void HeuristicSearch::findPath(const Graph::Node* const begin, const Graph::Node* const goal) {
    int64_t errCounter = 0;

    this->begin = begin;

    set<tuple<double, const Graph::Node*>, bool(*)(
            tuple<double, const Graph::Node*>,
            tuple<double, const Graph::Node*>)> open(
            [](tuple<double, const Graph::Node*> first,
                tuple<double, const Graph::Node*> second){
            if (get<0>(first) == get<0>(second)) {
                return get<1>(first)->getId() < get<1>(second)->getId();
            } else {
                return get<0>(first) < get<0>(second);
            }
        });

    costs = Costs(graph);
    *costs[begin] = 0;
    open.insert(make_tuple(double(0), begin));

    const Graph::Node* curNode;
    double curCost;
    const vector<Graph::Edge>* edges;
    while (!open.empty()) {
        ++errCounter;
        if (errCounter > 2 * graph->getSize()) {
            throw Graph::Exeptions::EndlessSearch();
        }
        curNode = get<1>(*open.begin());

        open.erase(open.begin());

        if (curNode == goal) {
            break;
        }

        edges = curNode->getEdges();
        tuple<double, const Graph::Node*> oldNode, newNode;
        const Graph::Node* curDest;
        for (auto edgeIter : *edges) {
            if (edgeIter.getType() == Graph::EdgeType::Forward ||
                edgeIter.getType() == Graph::EdgeType::BiDirect) {

                curDest = edgeIter.getDest();

                double curDestCost = *costs[curDest];
                double curDestHeuristic = getHeuristic(curDest, goal);
                if (curDestCost + curDestHeuristic < curDestCost) {
                    oldNode = make_tuple(std::numeric_limits<double>::infinity(), curDest);
                } else {
                    oldNode = make_tuple(curDestCost + curDestHeuristic, curDest);
                }

                double edgeMinCost = getMinCost(&edgeIter);
                if (edgeMinCost + curDestHeuristic < edgeMinCost) {
                    newNode = make_tuple(std::numeric_limits<double>::infinity(), curDest);
                } else {
                    newNode = make_tuple(edgeMinCost + curDestHeuristic, curDest);
                }

                if (newNode < oldNode) {
                    open.find(oldNode);
                    *costs[curDest] = getMinCost(&edgeIter);
                    open.insert(newNode);
                }
            }
        }
    }
}

const double DijkstraSearch::getHeuristic(const Graph::Node* const from, const Graph::Node* const to) {
    return 0;
}


const double AStar::getHeuristic(const Graph::Node* const from, const Graph::Node* const to) {
    return heuristic(dynamic_cast<GridGraph::Cell*>(const_cast<Graph::Node*>(from)),
                     dynamic_cast<GridGraph::Cell*>(const_cast<Graph::Node*>(to)));
}

