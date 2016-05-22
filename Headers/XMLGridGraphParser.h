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
    const int32_t getStartWidth() const;
    const int32_t getStartHeight() const;
    const int32_t getEndWidth() const;
    const int32_t getEndHeight() const;
private:
    vector<vector<double>> grid;
    int32_t width;
    int32_t height;
    int32_t startHeight;
    int32_t startWidth;
    int32_t endHeight;
    int32_t endWidth;
};


#endif //PATHFINDER_XMLGRIDGRAPHPARSER_H
