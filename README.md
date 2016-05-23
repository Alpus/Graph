# Graph Library
###### Alexander Pushin
### Implemented features:
 * Class "Graph"
 * Class "GridGraph"
 * Class "GridVisualizer"
 * Dijkstra algorithm
 * AStar
 * Heuristics
   * Manhattan distance
   * Euclid distance
   * Chebyshev distance
 * XMLGridGraphParser (only for examples in "Inputs" folder)

---
### Decription:
This library is realization of class Graph. The main part of this lib is PathFinder class that implements different algorithms.

### Graph API
#### Graph creation
To create graph you should use constructor. It receives 3 arguments.
 1. Number of nodes.
  * Description: Number of nodes in graph.
   * Type: `std::uint64_t`.
 2. List of edges:
  * Default: empty.
   * Description: List of edges that should be added in graph.
   * Type: `std::tuple<uint64_t, uint64_t, double>` (begin, end, cost).
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

vector<tuple<uint64_t, uint64_t, double>> edges;
edges.push_back(make_tuple(uint64_t(0), uint64_t(1), double(1)));
edges.push_back(make_tuple(uint64_t(0), uint64_t(2), double(2)));

Graph graph(3, edges, true); // there is graph with 3 nodes and 2 edges (0 - 1, 0 - 2) with directed edges
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
graph.addDirectedEdge(graph[0], graph[1], 1); // edge 0 - 1 added
graph.addDirectedEdge(graph[0], graph[2], 2); // edge 0 - 2 added
```
#### Graph information
You can get graph size by method `Graph.getSize()`. It will return `const std::uint64_t` value with number of nodes in graph.

Example:
```cpp
// Get graph size
Graph graph(3);
uint32_t size = graph.getSize();  // size == 3
```

You can get node with required number by `Graph[std::uint64_t]`. It will return `const Graph::Node* const` with node object.

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
uint64_t id = graph[0]->getId(); // id == 0
```

If you need to get edges that connected with node, use `Node.getEdges()` It will return `const std::vector<Graph::Edge>*` with node edges.

```cpp
// Get node edges
const std::vector<Graph::Edge>* edges = graph[0]->getEdges(); // edges contain list of edges connected with node 0 (backward 0 - 1 with cost 1, backward 0 - 2 with cost 2).
```

If you need only one edge, you can use `Edge[std::uint64_t]`. Then you get `const Graph::Edge*` with needed edge.

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

### GridGraph
That class implement grid graph and has the same API as `Graph` with some differences.
#### Creation
Constructor of GridGraph takes 3 arguments.
 1. Width.
  * Description: grid width.
  * Type: `std::uint32_t`.
 2. Height:
  * Description: grid height.
  * Type: `std::uint32_t`.
 3. Grid:
  * Description: two-dimensional grid with costs of nodes.
  * Type: `const vector<vector<double>>* const`.
    
Example:
```cpp
XMLGridGraphParser data("/home/alpus/Work/Course_work/Implementation/Inputs/DragonAge-Starcraft-somemaps/Starcraft_movingai.com_/Cauldron/3796273.xml");
GridGraph graph(data.getWidth(), data.getHeight(), data.getGrid()); // There is grid graph with values from file
```

In that example you noticed class `XMLGridGraphParser`. It is help class that can parse xml files from folder "Inputs". It just takes path to file and can return data by getters discribed below:
```cpp
const vector<vector<double>>* getGrid() const;
const int32_t getWidth() const;
const int32_t getHeight() const;
const int32_t getStartWidth() const;
const int32_t getStartHeight() const;
const int32_t getEndWidth() const;
const int32_t getEndHeight() const;
```

#### GridGraph information
All methods the same with methods from Graph.

#### Cell
Cell is replacement of Node from graph. It has one additional method `const Coord getCoord() const` that returns `Coord` of that cell. Coord is just struct with `height` and `width` fields, method `bool isValid(const GridGraph* const graph)` that returns `true` value if cell in placed in grid, and `GridGraph::Cell::Coord operator+(const GridGraph::Cell::Coord) const` that makes sum of the same coordinates.

### Heuristic
That class contains static functions with implementations of different heuristic functions:
```cpp
static const double manhattanDistance(const GridGraph::Cell *const from, const GridGraph::Cell *const to); // Манхеттенское расстояние

static const double euclidDistance(const GridGraph::Cell *const from, const GridGraph::Cell *const to); // Евклидово расстояние

static const double chebyshevDistance(const GridGraph::Cell *const from, const GridGraph::Cell *const to); // Расстояние Чебышева
```

### PathFinder
To use some path finder you need to call constructor of needed class.

Allowed classes:

DijkstraSearch:
  * Constructor: `DijkstraSearch(Graph*)`.
  * **No negative loops**
  * Min cost path.
  * From one to all.
  * O(E log(N))

AStar:
  * Constructor: `AStar(Gridraph*, heuristic_function)`. As a second argument you can use on of the function from Heuristic class. For example `Heuristic::manhattanDistance`;
  * **No negative loops**
  * Min cost path.
  * From one to all.
  * O(E log(N))
  * **Only for graphs with heuristics**

Then you need to call `pathFinder.findPath()` that received 2 arguments:
 1. Begin node
    * Type: `const Graph::Node* `
 2. Goal node
  * Type: `const Graph::Node* `
  * Note: You are available to send `Graph.getInfiniteNode()` if you want to find path to all nodes and algorithm support it.
    
```cpp
// Find path
DijkstraSearch pathFinder(&graph);
pathFinder.findPath(graph[0], graph.getInfiniteNode()); // path from node 0 to all other nodes is founded
```

After that you can get cost of path to node with some id by method `pathFinder.getPathCost(std::uint64_t)`. It will return `const double* const` cost of path that algorithm founded (and `std::numeric_limits<double>::infinity()*` if algorithm did not achieve this node).

```cpp
// Get path cost
const double* cost = pathFinder.getPathCost(graph[1]); // cost == 1
```

And you can get order of nodes that algorithm found by method `pathFinder.getFullPath()`. It will return `const vector<Graph::Node*>` list with reached nodes in path order.

```cpp
// Get path order
const vector<const Graph::Node*> path = pathFinder.getFullPath(graph[1]); // path contain nodes with id (0, 1).
```

### GridVisualizer
That class can draw GridGraph and pathes on it using OpenCV library.

Constructor takes only 1 argument `GridGraph *graph`.
 1. Graph.
  * Description: grid graph object.
  * Type: `GridGraph *graph`.
    
Example:
```cpp
GridVisualizer map(&graph); // There is object of visualizer
```

If you want to draw path that find some pathFinder, then use method 'addPath(path)'. It takes 1 argument.
Constructor takes only 1 argument `GridGraph *graph`.
 1. Path.
  * Description: path as pathfinder returns it.
  * Type: `const vector<const Graph::Node*>* const path`.
  
Example:
```cpp
const vector<const Graph::Node*> path = pathFinder.getFullPath(endCell);
map.addPath(&path); // Now visualizer contain path
```
 
The main method is `drawImage()`. It shows image with graph and added paths.
  
Example:
```cpp
map.drawImage(); // You will see img on your screen
```
