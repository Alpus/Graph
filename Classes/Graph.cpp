#include "../Headers/Graph.h"
#include<iostream>

Graph::Graph(const uint64_t nodesNumber,
             const vector<tuple<uint64_t, uint64_t, double>> &rawEdges,
             const bool isDirected) {
    infiniteNode = new Graph::Node(numeric_limits<uint64_t>::infinity());
    nodes.reserve(nodesNumber);
    for (uint64_t i = 0; i < nodesNumber; ++i) {
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

Graph::Graph() {
    infiniteNode = new Graph::Node(numeric_limits<uint64_t>::infinity());
}


Graph::~Graph() {
    delete infiniteNode;
}

const uint64_t Graph::getSize() const {
    return uint64_t(nodes.size());
}

void Graph::addDirectedEdge(const Node* const from, const Node* const to, const double cost) {
    this->nodes[from->getId()].addEdge(&(this->nodes[to->getId()]), cost, Graph::EdgeType::Forward);
    this->nodes[to->getId()].addEdge(&(this->nodes[from->getId()]), cost, Graph::EdgeType::Backward);
}

void Graph::addBiDirectedEdge(const Node* const from, const Node* const to, const double cost) {
    this->nodes[from->getId()].addEdge(&(this->nodes[to->getId()]), cost, Graph::EdgeType::BiDirect);
    this->nodes[to->getId()].addEdge(&(this->nodes[from->getId()]), cost, Graph::EdgeType::BiDirect);
}

const Graph::Node* Graph::operator[](const uint64_t number) const {
    return &nodes[number];
}

Graph::Node::Node(const uint64_t id): id(id){}

const uint64_t Graph::Node::getId() const {
    return id;
}

void Graph::Node::addEdge(Graph::Node* const dest, const double cost, Graph::EdgeType type) {
    edges.push_back(Graph::Edge (this, dest, cost, type));
}

Graph::Edge::Edge(Graph::Node* const from, Graph::Node* const dest,
                        const double cost, Graph::EdgeType type): cost(cost), from(from),
                                                                  dest(dest), type(type){
}

const Graph::Edge *const Graph::Node::operator[](const uint64_t number) const {
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

const Graph::Node* Graph::getNodeById(const uint64_t number) {
    this->operator[](number);
}



