# Graph Library
###### Alexander Pushin
### Implemented features:
 * Class "Graph"
 * Dijkstra algorithm

---
### Decription:
This library is realization of class Graph. The main part of this lib is PathFinder class that implements different algorithms.

### Graph API
#### Graph creation
To create graph you should use constructor. It receives 3 arguments.
 1. Number of nodes.
  * Description: Number of nodes in graph.
   * Type: `std::uint32_t`.
 2. List of edges:
  * Default: empty.
   * Description: List of edges that should be added in graph.
   * Type: `std::tuple<uint32_t, uint32_t, double>` (begin, end, cost).
   * Notes: 
        * Node numbering starts with 0.
        * If there is no cost, default cost equals to 0.
 3. Is directed:
  * Default: false.
  * Description: If that field is true, constructor will add all required edges as directed.
  * Type: `bool`.
    
Example:
```cpp
// Creation of directed graph with:
// 3 nodes, 2 directed edges (0 - 1 with cost 1, 0 - 2 with cost 2)
// by constructor

vector<tuple<uint32_t, uint32_t, double>> edges;
edges.push_back(make_tuple(uint32_t(0), uint32_t(1), double(1)));
edges.push_back(make_tuple(uint32_t(0), uint32_t(2), double(2)));
    
Graph graph(3, edges, true);
```
You can add edges one-by-one using methods:
 1. `Graph.addDirectedEdge()`
 2. `Graph.addBiDirectedEdge()`

They receive 3 aruments:
 1. Start node.
  * Type: `Graph::Node* const`.
 2. End node.
  * Type: `Graph::Node* const`.
 3. Edge cost.
  * Default: 0
  * Type: `double`.

Example:
```cpp
// Creation of directed graph with:
// 3 nodes, 2 directed edges (0 - 1 with cost 1, 0 - 2 with cost 2)
// by methods

Graph graph(3);
graph.addDirectedEdge(graph[0], graph[1], 1);
graph.addDirectedEdge(graph[0], graph[2], 2);
```
#### Graph information
You can get graph size by method `Graph.getSize()`. It will return `const std::uint32_t` value with number of nodes in graph.

Example:
```cpp
// Get graph size
Graph graph(3);
uint32_t size = graph.getSize();  // size == 3
```

You can get node with required number by `Graph[std::uint32_t]`. It will return `const Graph::Node* const` with node object.

Example:
```cpp
// Get node by id
const Graph::Node* node = graph[0];  // node now contains graph node with id 0
```

You can get abstract infinite node by `Graph.getInfiniteNode()`. It will return `const Graph::Node*` with node object. This node is unreacheable from any others nodes and has `id == std::numeric_limits<uint32_t>::infinity()`.

Example:
```cpp
// Get infinite node
const Graph::Node* node = graph.getInfiniteNode();  // node id equals to numeric_limits<uint32_t>::infinity()
```

#### Node
You can get id of node using `Node.getId()`. That will return `const std::uint32_t` value with node id.

Example:
```cpp
// Get node id
uint32_t id = graph[0]->getId(); // id == 0
```

If you need to get edges that connected with node, use `Node.getEdges()` It will return `const std::vector<Graph::Edge>*` with node edges.

```cpp
// Get node edges
const std::vector<Graph::Edge>* edges = graph[0]->getEdges(); // edges contain list of edges connected with node 0 (backward 0 - 1 with cost 1, backward 0 - 2 with cost 2).
```

If you need only one edge, you can use `Edge[std::uint32_t]`. Then you get `const Graph::Edge*` with needed edge.

```cpp
// Get node edges
const Graph::Edge* edge = (*graph[0])[0]; // edges contain list of edges connected with node 0 (backward 0 - 1 with cost 1, backward 0 - 2 with cost 2).
```

#### Edge
You can get edge cost by method `Edge.getCost()`. It will return `const double` value with edge cost.

```cpp
// Get edge cost
double cost = edge->getCost(); // cost == 1
```

You can get edge two ends of edge by method `Edge.getFrom()` and `Edge.getDest()`. It will return `const Graph::Node*` nodes.

```cpp
// Get ends of edge
const Graph::Node* nodeFrom  = edge->getFrom(); // nodeFrom is Node with id 0
const Graph::Node* nodeDest  = edge->getDest(); // nodeDest is Node with id 1
```

You can get type of edge by method `Edge.getType()`. It will return `const Graph::EdgeType` type. `EdgeType` is enum class that may contain `{Backward, BiDirected, Forward}`.

```cpp
// Get type of edge
const Graph::EdgeType type  = edge->getType(); // type == Graph::EdgeType::Backward
```

#### PathFinder
To use some path finder you need to call constructor of needed class with graph object as argument. For example `DijkstraSearch(Graph&)`.

Allowed classes:
 * DijkstraSearch 
  * **No negative loops**
  * Min cost path.
  * From one to all.
  * O(E log(N))

Then you need to call `pathFinder.findPath()` that received 2 arguments:
 1. Begin node
    * Type: `const Graph::Node& `
 2. Goal node
  * Type: `const Graph::Node& `
  * Note: You are available to send `Graph.getInfiniteNode()` if you want to find path to all nodes and algorithm support it.
    
```cpp
// Find path
DijkstraSearch pathFinder(graph);
pathFinder.findPath(*graph[0], *graph.getInfiniteNode()); // path from node 0 to all other nodes is founded
```

After that you can get cost of path to node with some id by method `pathFinder.getPathCost(std::uint32_t)`. It will return `double` cost of path that algorithm founded (and `std::numeric_limits<double>::infinity()` if algorithm did not achieve this node).

```cpp
// Get path cost
double cost = pathFinder.getPathCost(1); // cost == 1
```

And you can get order of nodes that algorithm found by method `pathFinder.getFullPath()`. It will return `const vector<Graph::Node*>` list with reached nodes in path order.

```cpp
// Get path order
const vector<const Graph::Node*> path = pathFinder.getFullPath(1); // path contain nodes with id (0, 1).
```
