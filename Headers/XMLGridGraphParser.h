//
// Created by alpus on 21.05.16.
//

#ifndef PATHFINDER_XMLGRIDGRAPHPARSER_H
#define PATHFINDER_XMLGRIDGRAPHPARSER_H

#include "GridGraph.h"

class XMLGridGraphParser {
public:
    XMLGridGraphParser(const string path);
    const vector<vector<double>>* getGrid() const;
    const int32_t getWidth() const;
    const int32_t getHeight() const;
    const int32_t getStartX() const;
    const int32_t getStartY() const;
    const int32_t getEndX() const;
    const int32_t getEndY() const;
private:
    vector<vector<double>> grid;
    int32_t width;
    int32_t height;
    int32_t startX;
    int32_t startY;
    int32_t endX;
    int32_t endY;
};


#endif //PATHFINDER_XMLGRIDGRAPHPARSER_H
