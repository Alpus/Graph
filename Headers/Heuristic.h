//
// Created by alpus on 22.05.16.
//

#ifndef PATHFINDER_HEURISTIC_H
#define PATHFINDER_HEURISTIC_H

#include<math.h>
#include"GridGraph.h"


class Heuristic {
public:
    static const double manhattanDistance(const GridGraph::Cell *const from,
                                   const GridGraph::Cell *const to);

    static const double euclidDistance(const GridGraph::Cell *const from,
                                                           const GridGraph::Cell *const to);

    static const double chebyshevDistance(const GridGraph::Cell *const from,
                                                              const GridGraph::Cell *const to);
};


#endif //PATHFINDER_HEURISTIC_H
