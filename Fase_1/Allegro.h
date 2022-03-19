#pragma once

#include "FullCompleteTree.h"
#include <cmath>
#include <string>


//
//class NodeGUI {
//public:
//	double x_center;
//	double y_center;
//	double width;
//	double height;
//
//	double getSupLeftVertexX();
//	double getSupLeftVertexY();
//	double getInfRightVertexX();
//	double getInfRightVertexY();
//};

void drawTree(FullCompleteTree<std::string> tree, double dispWidth, double dispHeight);