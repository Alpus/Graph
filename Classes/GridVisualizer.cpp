//
// Created by alpus on 22.05.16.
//

#include "../Headers/GridVisualizer.h"

GridVisualizer::GridVisualizer(GridGraph *graph): graph(graph),
                                                  img(graph->getWidth(), graph->getHeight(),
                                                      CV_8UC3, Vec3b(255, 255, 255)) {
    uint8_t color;
    for (int height = 0; height < graph->getHeight(); ++height) {
        for (int width = 0; width < graph->getWidth(); ++width) {
            if (graph->getCellByCoords(height, width)->getCost() == numeric_limits<double>::infinity()) {
                color = 0;
            } else {
                color = 255;
            }
            img.at<Vec3b>(height, width) = Vec3b(color, color, color);
        }
    }
}

void GridVisualizer::addPath(const vector<const Graph::Node *>* const path) {
    GridGraph::Cell *cell;
    for(auto node : *path) {
        cell = static_cast<GridGraph::Cell*>(const_cast<Graph::Node*>(node));
        img.at<Vec3b>(cell->getCoord().height, cell->getCoord().width) = Vec3b(0, 0, 255);
    }
}

void GridVisualizer::drawImage() const {
    namedWindow("Map", WINDOW_AUTOSIZE);
    imshow("Map", img);
    waitKey(0);
}





