#ifndef PATHFINDER_GRAPH_H
#define PATHFINDER_GRAPH_H

#include <vector>
#include <cstdint>
#include <tuple>
#include <limits>
#include <string>
using std::vector;
using std::int32_t;
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
        Node(const uint64_t id);

        const uint64_t getId() const;
        const vector<Edge>* const getEdges() const;

        virtual const Edge* const operator[](const uint64_t number) const;

        void addEdge(Node* const dest, const double cost = 0, EdgeType type = EdgeType::BiDirect);

    protected:
        uint64_t id;
        vector<Edge> edges;

    private:

    };

    Graph();
    Graph(const uint64_t nodesNumber, const vector<tuple<uint64_t, uint64_t, double>>& raw_edges=
          vector<tuple<uint64_t, uint64_t, double>>(),
          const bool isDirected=false);
    ~Graph();

    virtual const uint64_t getSize() const;

    virtual const Node* operator[](const uint64_t number) const;
    const Node* getNodeById(const uint64_t number);
    void addDirectedEdge(const Node* const from, const Node* const to, const double cost=0);
    void addBiDirectedEdge(const Node* const from, const Node* const to, const double cost=0);

    virtual const Node* const getInfiniteNode() const;
    vector<Node> nodes;

protected:
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
    Edge(Graph::Node* const from, Graph::Node* const dest, const double cost=0,
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
