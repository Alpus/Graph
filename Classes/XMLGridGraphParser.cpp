//
// Created by alpus on 21.05.16.
//

#include "../Headers/XMLGridGraphParser.h"
#include "../Libraries/pugixml-1.7/src/pugixml.hpp"
#include <sstream>

using std::stringstream;
using std::vector;

XMLGridGraphParser::XMLGridGraphParser(const string path) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(path.c_str());
    pugi::xml_node map = doc.child("root").child("map");
    width = strtoul(map.child_value("width"), NULL, 10);
    height = strtoul(map.child_value("height"), NULL, 10);
    startX = strtoul(map.child_value("startx"), NULL, 10);
    startY = strtoul(map.child_value("starty"), NULL, 10);
    endX = strtoul(map.child_value("finishx"), NULL, 10);
    endY = strtoul(map.child_value("finishy"), NULL, 10);
    pugi::xml_node rows = map.child("grid");

    grid.assign(height, vector<double>());
    string number;

    int row_number = 0;

    for (pugi::xml_node row = rows.first_child(); row_number < height; row = rows.next_sibling()) {
        stringstream ssin(row.child_value());

        int i = 0;
        while (ssin.good() && i < width) {
            ssin >> number;
            if (number == "0") {
                grid[row_number].push_back(0);
            } else {
                grid[row_number].push_back(numeric_limits<double>::infinity());
            }
            ++i;
        }
        ++row_number;
    }
}

const vector<vector<double>> XMLGridGraphParser::getGrid() const {
    return grid;
}

const uint32_t XMLGridGraphParser::getWidth() const {
    return width;
}

const uint32_t XMLGridGraphParser::getHeight() const {
    return height;
}

const uint32_t XMLGridGraphParser::getStartX() const {
    return startX;
}

const uint32_t XMLGridGraphParser::getStartY() const {
    return startY;
}

const uint32_t XMLGridGraphParser::getEndX() const {
    return endX;
}

const uint32_t XMLGridGraphParser::getEndY() const {
    return endY;
}















