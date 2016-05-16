//
// Created by alpus on 15.05.16.
//

#ifndef PATHFINDER_GRIDGRAPH_H
#define PATHFINDER_GRIDGRAPH_H

#include "Graph.h"

class GridGraph : public Graph {
public:
    class Cell : public GridGraph::Node {
    public:
        struct Coord {
            Coord(uint32_t x, uint32_t y): x(x), y(y) {}
            uint32_t x;
            uint32_t y;
            bool isValid(const GridGraph* const graph);
            GridGraph::Cell::Coord operator+(const GridGraph::Cell::Coord) const;
        };
        Cell(const uint32_t x, const uint32_t y);
        const Coord getCoord() const;
        void addAllNeighs(const GridGraph *graph, const double nodeCost);
    private:
        Coord coord;
    };
    GridGraph(uint32_t width, uint32_t height, vector<vector<double>> nodeCosts);
    uint32_t getWidth() const;
    uint32_t getHeight() const;
    Cell* const operator[](const Cell::Coord* const) const;
private:
    const vector<const Cell::Coord> neighCoordDiff = {Cell::Coord(uint32_t(-1), uint32_t(-1)),
                                                      Cell::Coord(uint32_t(0), uint32_t(-1)),
                                                      Cell::Coord(uint32_t(1), uint32_t(-1)),
                                                      Cell::Coord(uint32_t(1), uint32_t(0)),
                                                      Cell::Coord(uint32_t(1), uint32_t(1)),
                                                      Cell::Coord(uint32_t(0), uint32_t(1)),
                                                      Cell::Coord(uint32_t(-1), uint32_t(1)),
                                                      Cell::Coord(uint32_t(-1), uint32_t(0))};
    vector<vector<GridGraph::Cell>> grid;
    const vector <const GridGraph::Cell* const> getAllValidNeighs(const GridGraph::Cell* const) const;
    uint32_t width;
    uint32_t height;
};


#endif //PATHFINDER_GRIDGRAPH_H
