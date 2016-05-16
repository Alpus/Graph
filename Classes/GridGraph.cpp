#include "../Headers/GridGraph.h"

GridGraph::Cell::Cell(const uint32_t x, const uint32_t y): Graph::Node(uint64_t(x) + uint64_t(y) * (2 << 32)),
                                                           coord(Coord(x, y)) {}

const GridGraph::Cell::Coord GridGraph::Cell::getCoord() const {
    return coord;
}

void GridGraph::Cell::addAllNeighs(const GridGraph *graph, const double nodeCost) {
    const vector<const Cell* const> neighs = graph->getAllValidNeighs(this);
    for (auto neig : neighs) {
        addEdge(neig, nodeCost, EdgeType::BiDirect);
    }
}

bool GridGraph::Cell::Coord::isValid(const GridGraph * const graph) {
    return (x >= 0 && y >= 0 && x < graph->getWidth() && y < graph->getHeight());
}

Coord GridGraph::Cell::Coord::operator+(const Coord s) const {
    return Coord(x + s.x, y + s.y);
}

GridGraph::Cell *const GridGraph::operator[](const GridGraph::Cell::Coord *const coord) const {
    this->grid[coord->x][coord->y];
}

const vector<const GridGraph::Cell* const> GridGraph::getAllValidNeighs(const GridGraph::Cell* const mainCell) const {
    vector<const Cell* const> ans(8);
    GridGraph::Cell::Coord mainCoord = mainCell->getCoord();
    GridGraph::Cell::Coord resCoord = GridGraph::Cell::Coord(0, 0);
    for (auto diff : neighCoordDiff) {
        resCoord = mainCoord + diff;
        if (resCoord.isValid(this)) {
            ans.push_back(this->operator[](&resCoord));
        }
    }
}

GridGraph::GridGraph(uint32_t width, uint32_t height, vector<vector<double>> nodeCosts): Graph(), width(width), height(height) {
    grid.assign(height, vector<Cell>(width));
    for (uint32_t i = 0; i < height; ++i) {
        for (uint32_t j = 0; j < width; ++j) {
            grid[i].push_back(Cell(i, j));
        }
    }

    for (uint32_t i = 0; i < height; ++i) {
        for (uint32_t j = 0; j < width; ++j) {
            grid[i][j].addAllNeighs(this, nodeCosts[i][j]);
        }
    }
}

uint32_t GridGraph::getWidth() const {
    return width;
}

uint32_t GridGraph::getHeight() const {
    return height;
}


