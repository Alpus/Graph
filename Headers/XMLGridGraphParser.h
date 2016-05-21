//
// Created by alpus on 21.05.16.
//

#ifndef PATHFINDER_XMLGRIDGRAPHPARSER_H
#define PATHFINDER_XMLGRIDGRAPHPARSER_H

#include "GridGraph.h"

class XMLGridGraphParser {
public:
    XMLGridGraphParser(const string path);
    const vector<vector<double>> getGrid() const;
    const uint32_t getWidth() const;
    const uint32_t getHeight() const;
    const uint32_t getStartX() const;
    const uint32_t getStartY() const;
    const uint32_t getEndX() const;
    const uint32_t getEndY() const;
private:
    vector<vector<double>> grid;
    uint32_t width;
    uint32_t height;
    uint32_t startX;
    uint32_t startY;
    uint32_t endX;
    uint32_t endY;
};


#endif //PATHFINDER_XMLGRIDGRAPHPARSER_H
