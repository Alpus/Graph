#ifndef PATHFINDER_GRAPH_H
#define PATHFINDER_GRAPH_H

#include <vector>
#include <cstdint>
#include <tuple>
#include <limits>
#include <string>
using std::vector;
using std::uint32_t;
using std::uint64_t;
using std::tuple;
using std::numeric_limits;
using std::string;
using std::get;
using std::make_tuple;

class Graph {
public:
    enum class EdgeType {Backward=-1, BiDirect=0, Forward=1};

    class Exeptions;
    class Node;

    Graph(const uint32_t nodesNumber, const vector<tuple<uint32_t, uint32_t>>& raw_edges=
          vector<tuple<uint32_t, uint32_t>>(),
          const bool isDirected=false);
    Graph(const uint32_t nodesNumber, const vector<tuple<uint32_t, uint32_t, double>>& raw_edges=
          vector<tuple<uint32_t, uint32_t, double>>(),
          const bool isDirected=false);
    ~Graph();

    const uint32_t getDimension() const;

    Node* const operator[](const uint32_t number);
    void addDirectedEdge(const uint32_t from, const uint32_t to, const double cost=1);
    void addBiDirectedEdge(const uint32_t from, const uint32_t to, const double cost=1);

    // Get string with name of PathFinder class.
    // Allowed values:
    //
    // - DijkstraSearch
    void setPathFinder(const string&);

    void findPath(const uint32_t begin, const string& pathFinderName="",
                  const uint32_t goal=numeric_limits<uint32_t >::infinity());
    const double getPathCost(const uint32_t goal);
    const vector<Graph::Node*> getFullPath(const uint32_t goal);

protected:
    class PathFinder;
    class HeuristicSearch;
    class DijkstraSearch;

    vector<Node> nodes;
    PathFinder* pathFinder = NULL;
};

class Graph::Exeptions {
public:
    class NoSuchPathFinderName {
    public:
        NoSuchPathFinderName(const string& PathFinder) {}
    };
    class NoPathfinderSet{};
};

class Graph::Node {
public:
    class Edge;

    Node(const uint32_t id);

    const uint32_t getId() const;
    const vector<Edge>* const getEdges() const;

    void addEdge(Node &dest, const double cost = 1, Graph::EdgeType type = Graph::EdgeType::BiDirect);

private:
    uint32_t id;
    vector<Edge> edges;
};

class Graph::Node::Edge {
public:
    Edge(Graph::Node& from, Graph::Node& dest, const double cost=0, Graph::EdgeType type=Graph::EdgeType::BiDirect);

    const double getCost() const;
    Graph::Node* const getFrom() const;
    Graph::Node* const getDest() const;
    const Graph::EdgeType getType() const;

private:
    double cost;
    Graph::Node* from;
    Graph::Node* dest;

    Graph::EdgeType type;
};

#endif //PATHFINDER_GRAPH_H
