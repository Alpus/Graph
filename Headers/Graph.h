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
    class Exeptions;
    class Edge;
    enum class EdgeType {Backward=-1, BiDirect=0, Forward=1};

    class Node {
    public:
        Node(const uint32_t id);

        const uint32_t getId() const;
        virtual const vector<Edge>* const getEdges() const;

        const Edge* const operator[](const uint32_t number) const;

        virtual void addEdge(Node &dest, const double cost = 0, EdgeType type = EdgeType::BiDirect);

    private:
        uint32_t id;
        vector<Edge> edges;
    };

    Graph(const uint32_t nodesNumber, const vector<tuple<uint32_t, uint32_t, double>>& raw_edges=
          vector<tuple<uint32_t, uint32_t, double>>(),
          const bool isDirected=false);
    ~Graph();

    const uint32_t getSize() const;

    const Node* const operator[](const uint32_t number) const ;
    void addDirectedEdge(const Node* const from, const Node* const to, const double cost=0);
    void addBiDirectedEdge(const Node* const from, const Node* const to, const double cost=0);

    // Get string with name of PathFinder class.
    // Allowed values:
    //
    // - DijkstraSearch
    void setPathFinder(const string&);

    void findPath(const Node *const begin, const Node *const end);
    const double getPathCost(const uint32_t goal);
    const vector<const Graph::Node*> getFullPath(const uint32_t goal);

    virtual const Node* const getInfiniteNode() const;

protected:
    class PathFinder;
    class HeuristicSearch;
    class DijkstraSearch;

    vector<Node> nodes;
    PathFinder* pathFinder = NULL;

    Node* infiniteNode;
};

class Graph::Exeptions {
public:
    class NoSuchPathFinderName {
    public:
        NoSuchPathFinderName(const string& PathFinder) {}
    };
    class NoPathfinderSet{};
    class EndlessSearch{};
};

class Graph::Edge {
public:
    Edge(Graph::Node& from, Graph::Node& dest, const double cost=0,
         Graph::EdgeType type=Graph::EdgeType::BiDirect);

    const double getCost() const;
    const Graph::Node* const getFrom() const;
    const Graph::Node* const getDest() const;
    const Graph::EdgeType getType() const;

private:
    double cost;
    Graph::Node* from;
    Graph::Node* dest;

    Graph::EdgeType type;
};

#endif //PATHFINDER_GRAPH_H
