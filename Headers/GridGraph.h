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
            Coord(int32_t height, int32_t width): width(width), height(height) {}
            int32_t height;
            int32_t width;
            bool isValid(const GridGraph* const graph);
            GridGraph::Cell::Coord operator+(const GridGraph::Cell::Coord) const;
        };
        Cell(const int32_t x, const int32_t y, GridGraph* graph);
        const Coord getCoord() const;
        void addAllNeighs(const GridGraph *graph, const double nodeCost);
    protected:
        Coord coord;
    };
    GridGraph(int32_t width, int32_t height, const vector<vector<double>>* const nodeCosts);
    int32_t getWidth() const;
    int32_t getHeight() const;
    const Cell* getCellByCoords(const int32_t height, const int32_t width) const;
    const uint64_t getSize() const;
    const Cell* operator[](const uint64_t number) const;
    virtual const Cell* const getInfiniteNode() const;

private:
    const vector<Cell::Coord> neighCoordDiff = {Cell::Coord(int32_t(-1), int32_t(-1)),
                                                Cell::Coord(int32_t(0), int32_t(-1)),
                                                Cell::Coord(int32_t(1), int32_t(-1)),
                                                Cell::Coord(int32_t(1), int32_t(0)),
                                                Cell::Coord(int32_t(1), int32_t(1)),
                                                Cell::Coord(int32_t(0), int32_t(1)),
                                                Cell::Coord(int32_t(-1), int32_t(1)),
                                                Cell::Coord(int32_t(-1), int32_t(0))};
    vector<vector<GridGraph::Cell*>> grid;
    const vector <GridGraph::Cell*> getAllValidNeighs(GridGraph::Cell* const) const;
    int32_t width;
    int32_t height;
    GridGraph::Cell *const getCellByCoords(const Cell::Coord* const) const;
    vector<Cell> nodes;
    Cell* infiniteNode;
};


#endif //PATHFINDER_GRIDGRAPH_H
