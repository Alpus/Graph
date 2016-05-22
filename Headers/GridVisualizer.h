//
// Created by alpus on 22.05.16.
//

#ifndef PATHFINDER_GRIDVISUALIZER_H
#define PATHFINDER_GRIDVISUALIZER_H

#include"GridGraph.h"
#include<opencv2/opencv.hpp>
using namespace cv;

class GridVisualizer {
public:
    GridVisualizer(GridGraph *graph);
    void addPath(const vector<const Graph::Node*>* const path);
    void drawImage() const;
private:
    Mat img;
    GridGraph* graph;
};


#endif //PATHFINDER_GRIDVISUALIZER_H
