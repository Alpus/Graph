cmake_minimum_required(VERSION 3.3)
project(Pathfinder)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Classes/Graph.cpp Headers/Graph.h
        Classes/PathFinder.cpp Headers/PathFinder.h
        Classes/GridGraph.cpp Headers/GridGraph.h
        Classes/XMLGridGraphParser.cpp Headers/XMLGridGraphParser.h
        Libraries/pugixml-1.7/src/pugixml.hpp Libraries/pugixml-1.7/src/pugixml.cpp
        Classes/Heuristic.cpp Headers/Heuristic.h
        Classes/GridVisualizer.cpp Headers/GridVisualizer.h)

add_executable(Pathfinder ${SOURCE_FILES})

find_package( OpenCV REQUIRED )
target_link_libraries( Pathfinder ${OpenCV_LIBS} )
