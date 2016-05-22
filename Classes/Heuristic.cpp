//
// Created by alpus on 22.05.16.
//

#include "../Headers/Heuristic.h"

const double Heuristic::manhattanDistance(const GridGraph::Cell *const from, const GridGraph::Cell *const to) {
    return abs(from->getCoord().height - to->getCoord().height) +
           abs(from->getCoord().width - to->getCoord().width);;
}

const double Heuristic::euclidDistance(const GridGraph::Cell *const from, const GridGraph::Cell *const to) {
    return sqrt(pow((from->getCoord().height - to->getCoord().height), 2) +
                pow(from->getCoord().width - to->getCoord().width, 2));
}

const double Heuristic::chebyshevDistance(const GridGraph::Cell *const from,
                                                          const GridGraph::Cell *const to) {
    return std::min(abs(from->getCoord().height - to->getCoord().height),
                    abs(from->getCoord().width - to->getCoord().width));
}