#include "../Headers/GridGraph.h"
#include <cmath>
#include <iostream>

GridGraph::Cell::Cell(const int32_t height, const int32_t width, GridGraph* graph):
        Graph::Node(uint64_t(height) * graph->getWidth() + uint64_t(width)),
        coord(Coord(height, width)) {
}

const GridGraph::Cell::Coord GridGraph::Cell::getCoord() const {
    return coord;
}

void GridGraph::Cell::addAllNeighs(const GridGraph *graph, const double nodeCost) {
    const vector<GridGraph::Cell*> neighs = graph->getAllValidNeighs(this);
    for (auto neig : neighs) {
        neig->addEdge(this, nodeCost, EdgeType::BiDirect);
    }
}

bool GridGraph::Cell::Coord::isValid(const GridGraph * const graph) {
    return (width >= 0 && height >= 0 && width < graph->getWidth() && height < graph->getHeight());
}

GridGraph::Cell::Coord GridGraph::Cell::Coord::operator+(const Coord s) const {
    return Coord(height + s.height, width + s.width);
}

const vector<GridGraph::Cell*> GridGraph::getAllValidNeighs(GridGraph::Cell* const mainCell) const {
    vector<Cell*> ans;
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

GridGraph::GridGraph(int32_t width, int32_t height, const vector<vector<double>>* const nodeCosts): Graph(), width(width), height(height) {
    nodes.reserve(height * width + 1);
    grid.assign(height, vector<Cell*>());
    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            nodes.push_back(Cell(i, j, this));
            grid[i].push_back(&nodes[i * width + j]);
        }
    }

    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            grid[i][j]->addAllNeighs(this, (*nodeCosts)[i][j]);
        }
    }
}

int32_t GridGraph::getWidth() const {
    return width;
}

int32_t GridGraph::getHeight() const {
    return height;
}

const GridGraph::Cell *GridGraph::getCellByCoords(const int32_t x, const int32_t y) const {
    GridGraph::Cell::Coord coord(x, y);
    return this->getCellByCoords(&coord);
}

GridGraph::Cell *const GridGraph::getCellByCoords(const Cell::Coord *const coord) const {
    std::cerr << grid[coord->height][coord->width]->getId() << std::endl;
    return this->grid[coord->height][coord->width];
}

const uint64_t GridGraph::getSize() const {
    return nodes.size();
}

const GridGraph::Cell *GridGraph::operator[](const uint64_t number) const {
    return &nodes[number];
}












