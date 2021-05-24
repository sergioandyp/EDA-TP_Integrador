#pragma once

#include "FullCompleteTree.h"
#include <cmath>
#include <string>

#define DISPLAY_SIZE_Y	720
#define DISPLAY_SIZE_X	1080
#define BACKGD_COLOR_R	7
#define BACKGD_COLOR_G	210
#define BACKGD_COLOR_B	170
#define FONT_COLOR		"black"

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