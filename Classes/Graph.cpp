#include "../Headers/Graph.h"
#include "../Headers/PathFinder.h"

Graph::Graph(const uint32_t nodesNumber,
             const vector<tuple<uint32_t, uint32_t>> &rawEdges,
             const bool isDirected) {
    vector<tuple<uint32_t, uint32_t, double>> newRawEdges(nodesNumber);
    for (auto rawEdge: rawEdges) {
        newRawEdges.push_back(make_tuple(get<0>(rawEdge), get<1>(rawEdge), 1));
    }
    Graph(nodesNumber, newRawEdges, isDirected);
}

Graph::Graph(const uint32_t nodesNumber,
             const vector<tuple<uint32_t, uint32_t, double>> &rawEdges,
             const bool isDirected) {
    nodes.reserve(nodesNumber);
    for (uint32_t i = 0; i < nodesNumber; ++i) {
        nodes.push_back(Node(i));
    }
    for (auto rawEdge: rawEdges) {
        if (isDirected) {
            addDirectedEdge(get<0>(rawEdge), get<1>(rawEdge), get<2>(rawEdge));
        } else {
            addBiDirectedEdge(get<0>(rawEdge), get<1>(rawEdge), get<2>(rawEdge));
        }
    }
}

Graph::~Graph() {
    delete pathFinder;
}

const uint32_t Graph::getDimension() const {
    return uint32_t(nodes.size());
}

void Graph::addDirectedEdge(const uint32_t from, const uint32_t to, const double cost) {
    (*this)[from]->addEdge(*(*this)[to], cost, Graph::EdgeType::Forward);
    (*this)[to]->addEdge(*(*this)[from], cost, Graph::EdgeType::Backward);
}

void Graph::addBiDirectedEdge(const uint32_t from, const uint32_t to, const double cost) {
    (*this)[from]->addEdge(*(*this)[to], cost, Graph::EdgeType::BiDirect);
    (*this)[to]->addEdge(*(*this)[from], cost, Graph::EdgeType::BiDirect);
}

Graph::Node* const Graph::operator[](const uint32_t number) {
    return &nodes[number];
}

void Graph::setPathFinder(const string &pathFinderName) {
    if (pathFinderName == "DijkstraSearch") {
        pathFinder = (PathFinder *) new DijkstraSearch(*this);
    } else {
        throw Exeptions::NoSuchPathFinderName(pathFinderName);
    }
}

void Graph::findPath(const uint32_t begin, const string& pathFinderName, const uint32_t goal) {
    if (!pathFinderName.empty()) {
        setPathFinder(pathFinderName);
    }
    if (pathFinder == NULL) {
        throw Exeptions::NoPathfinderSet();
    }
    Node* goalNode;
    if (goal == numeric_limits<uint32_t >::infinity()) {
        goalNode = new Node(goal);
    } else {
        goalNode = (*this)[goal];
    }
    pathFinder->findPath(*(*this)[begin], *goalNode);
}

const double Graph::getPathCost(const uint32_t goal) {
    if (pathFinder == NULL) {
        throw Exeptions::NoPathfinderSet();
    }
    return pathFinder->getPathCost(*(*this)[goal]);
}

const vector<Graph::Node *> Graph::getFullPath(const uint32_t goal) {
    if (pathFinder == NULL) {
        throw Exeptions::NoPathfinderSet();
    }
    return pathFinder->getFullPath(*(*this)[goal]);
}


Graph::Node::Node(const uint32_t id): id(id){}

const uint32_t Graph::Node::getId() const {
    return id;
}

void Graph::Node::addEdge(Graph::Node &dest, const double cost, Graph::EdgeType type) {
    edges.push_back(Graph::Node::Edge(*this, dest, cost, type));
}

Graph::Node::Edge::Edge(Graph::Node& from, Graph::Node& dest,
                        const double cost, Graph::EdgeType type): cost(cost), from(&from),
                                                                  dest(&dest), type(type){}


const double Graph::Node::Edge::getCost() const {
    return cost;
}

Graph::Node* const Graph::Node::Edge::getFrom() const {
    return from;
}

Graph::Node* const Graph::Node::Edge::getDest() const {
    return dest;
}

const Graph::EdgeType Graph::Node::Edge::getType() const {
    return type;
}

const vector<Graph::Node::Edge>* const Graph::Node::getEdges() const {
    return &edges;
}

