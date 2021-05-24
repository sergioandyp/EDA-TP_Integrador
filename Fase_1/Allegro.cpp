#include "Allegro.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>

#define BLOCK_DIST_X(h)		(BLOCK_WIDTH(y,h)*0.1)	//No se usa
#define BLOCK_DIST_Y(y,h)	(BLOCK_HEIGHT(h)*0.1)	//No se usa
#define X_CENTER_POS(x,y)	((double)TREE_OFFSET_X + (x)*BLOCK_WIDTH(y) + (x+1)*BLOCK_DIST_X(h))
#define Y_CENTER_POS(x,y)	((double)TREE_OFFSET_Y + (double)(x)*(double)DISPLAY_AVALIABLE_Y/(double)(exp2(y)+1.0))
#define VERT_1_X(x,y,h)		((double)X_CENTER_POS((x),(y)) - (double)BLOCK_WIDTH(y)/2.0)
#define VERT_1_Y(x,y,h)		((double)Y_CENTER_POS((x),(y)) - (double)BLOCK_HEIGHT(h)/2.0)
#define VERT_2_X(x,y,h)		((double)X_CENTER_POS((x),(y)) + (double)BLOCK_WIDTH(y)/2.0)
#define VERT_2_Y(x,y,h)		((double)Y_CENTER_POS((x),(y)) + (double)BLOCK_HEIGHT(h)/2.0)

#define HEIGHT_DIV_PERC	0.1
#define WIDTH_DIV_PERC	0.2

using namespace std;

void drawTree(FullCompleteTree<string> tree, double dispWidth, double dispHeight) {

	unsigned int h = tree.getHeight() + 1;

	ALLEGRO_FONT* font = al_create_builtin_font();

	for (unsigned int i = 0; i < h; i++) {

			double bros = exp2(i);
			double dividerX = dispWidth * WIDTH_DIV_PERC / (double)(bros + 1.0);
			double dividerY = dispHeight * HEIGHT_DIV_PERC / (double)(h + 1.0);

		for (unsigned int j = 0; j < tree[i].size(); j++) {


			double height = (dispHeight - dividerY * (h + 1.0)) / h;
			double width = (dispWidth - dividerX * (bros + 1.0)) / bros;
			double xVert1 = j * (width + dividerX) + dividerX;
			double yVert1 = i * (height + dividerY) + dividerY;
			double rx = 0;
			dobule ry = 0;

			al_draw_filled_rounded_rectangle(xVert1, yVert1, xVert1 + width, yVert1 + height, rx, ry, al_map_rgb(BACKGD_COLOR_R, BACKGD_COLOR_G, BACKGD_COLOR_B));
			
			double centerX = xVert1 + width / 2.0;
			double centerY = yVert1 + height / 2.0;
			
			al_draw_text(font, al_color_name(FONT_COLOR), centerX, centerY, ALLEGRO_ALIGN_CENTRE, tree[i][j].c_str());

		}
	}

	al_flip_display();

}

//double NodeGUI::NodeGUI(double centerX, double centerY, double, double) : x_center(), y_center() {
//}
//
//double NodeGUI::getSupLeftVertexX() {
//	return x_center-width/2.0;
//}
//
//double NodeGUI::getSupLeftVertexY() {
//	return y_center-height/2.0;
//}
//
//double NodeGUI::getInfRightVertexX() {
//	return x_center+width/2.0;
//}
//
//double NodeGUI::getInfRightVertexY() {
//	return y_center+height/2.0;
//}
//
//
