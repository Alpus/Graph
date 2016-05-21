#include "../Headers/GridGraph.h"
#include <cmath>

GridGraph::Cell::Cell(const uint32_t x, const uint32_t y): Graph::Node(uint64_t(x) +
                                                           uint64_t(y) * uint32_t((pow(uint32_t(2), uint32_t(32))))),
                                                           coord(Coord(x, y)) {}

const GridGraph::Cell::Coord GridGraph::Cell::getCoord() const {
    return coord;
}

void GridGraph::Cell::addAllNeighs(const GridGraph *graph, const double nodeCost) {
    const vector<GridGraph::Cell*> neighs = graph->getAllValidNeighs(this);
    for (auto neig : neighs) {
        addEdge(neig, nodeCost, EdgeType::BiDirect);
    }
}

bool GridGraph::Cell::Coord::isValid(const GridGraph * const graph) {
    return (x >= 0 && y >= 0 && x < graph->getWidth() && y < graph->getHeight());
}

GridGraph::Cell::Coord GridGraph::Cell::Coord::operator+(const Coord s) const {
    return Coord(x + s.x, y + s.y);
}

const vector<GridGraph::Cell*> GridGraph::getAllValidNeighs(GridGraph::Cell* const mainCell) const {
    vector<Cell*> ans(8);
    GridGraph::Cell::Coord mainCoord = mainCell->getCoord();
    GridGraph::Cell::Coord resCoord = GridGraph::Cell::Coord(0, 0);
    for (auto diff : neighCoordDiff) {
        resCoord = mainCoord + diff;
        if (resCoord.isValid(this)) {
            ans.push_back(this->getCellByCoords(&resCoord));
        }
    }
    return ans;
}

GridGraph::GridGraph(uint32_t width, uint32_t height, vector<vector<double>> nodeCosts): Graph(), width(width), height(height) {
    nodes.assign(height * width, 0);
    grid.assign(height, vector<Cell*>());
    for (uint32_t i = 0; i < height; ++i) {
        for (uint32_t j = 0; j < width; ++j) {
            Cell newCell(i, j);
            nodes[newCell.getId()] = newCell;
            grid[i].push_back(&newCell);
        }
    }

    for (uint32_t i = 0; i < height; ++i) {
        for (uint32_t j = 0; j < width; ++j) {
            grid[i][j]->addAllNeighs(this, nodeCosts[i][j]);
        }
    }
}

uint32_t GridGraph::getWidth() const {
    return width;
}

uint32_t GridGraph::getHeight() const {
    return height;
}

const GridGraph::Cell *GridGraph::getCellByCoords(const uint32_t x, const uint32_t y) const {
    GridGraph::Cell::Coord coord(x, y);
    return this->getCellByCoords(&coord);
}

GridGraph::Cell *const GridGraph::getCellByCoords(const Cell::Coord *const coord) const {
    return this->grid[coord->x][coord->y];;
}








