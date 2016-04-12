#include "../Headers/Graph.h"
#include "../Headers/PathFinder.h"

Graph::Graph(const uint32_t nodesNumber,
             const vector<tuple<uint32_t, uint32_t, double>> &rawEdges,
             const bool isDirected) {
    infiniteNode = new Graph::Node(numeric_limits<uint32_t>::infinity());
    nodes.reserve(nodesNumber);
    for (uint32_t i = 0; i < nodesNumber; ++i) {
        nodes.push_back(Node(i));
    }
    for (auto rawEdge: rawEdges) {
        if (isDirected) {
            addDirectedEdge(&this->nodes[get<0>(rawEdge)], &this->nodes[get<1>(rawEdge)], get<2>(rawEdge));
        } else {
            addBiDirectedEdge(&this->nodes[get<0>(rawEdge)], &this->nodes[get<1>(rawEdge)], get<2>(rawEdge));
        }
    }
}

Graph::~Graph() {
    delete infiniteNode;
}

const uint32_t Graph::getSize() const {
    return uint32_t(nodes.size());
}

void Graph::addDirectedEdge(const Node* const from, const Node* const to, const double cost) {
    this->nodes[from->getId()].addEdge(this->nodes[to->getId()], cost, Graph::EdgeType::Forward);
    this->nodes[to->getId()].addEdge(this->nodes[from->getId()], cost, Graph::EdgeType::Backward);
}

void Graph::addBiDirectedEdge(const Node* const from, const Node* const to, const double cost) {
    this->nodes[from->getId()].addEdge(this->nodes[to->getId()], cost, Graph::EdgeType::BiDirect);
    this->nodes[to->getId()].addEdge(this->nodes[from->getId()], cost, Graph::EdgeType::BiDirect);
}

const Graph::Node* const Graph::operator[](const uint32_t number) const {
    return &nodes[number];
}


Graph::Node::Node(const uint32_t id): id(id){}

const uint32_t Graph::Node::getId() const {
    return id;
}

void Graph::Node::addEdge(Graph::Node &dest, const double cost, Graph::EdgeType type) {
    edges.push_back(Graph::Edge (*this, dest, cost, type));
}

Graph::Edge ::Edge(Graph::Node& from, Graph::Node& dest,
                        const double cost, Graph::EdgeType type): cost(cost), from(&from),
                                                                  dest(&dest), type(type){}

const Graph::Edge *const Graph::Node::operator[](const uint32_t number) const {
    return &edges[number];
}

const double Graph::Edge ::getCost() const {
    return cost;
}

const Graph::Node* const Graph::Edge ::getFrom() const {
    return from;
}

const Graph::Node* const Graph::Edge ::getDest() const {
    return dest;
}

const Graph::EdgeType Graph::Edge ::getType() const {
    return type;
}

const vector<Graph::Edge>* const Graph::Node::getEdges() const {
    return &edges;
}

const Graph::Node* const Graph::getInfiniteNode() const {
    return infiniteNode;
}
