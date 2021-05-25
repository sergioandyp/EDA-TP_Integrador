#include "Allegro.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>


#define DISPLAY_SIZE_Y	720
#define DISPLAY_SIZE_X	1080

#define BACKGD_COLOR_R	7
#define BACKGD_COLOR_G	210
#define BACKGD_COLOR_B	170
#define FONT_COLOR		"black"

#define HEIGHT_DIV_PERC	0.1
#define WIDTH_DIV_PERC	0.2

using namespace std;

void drawTree(FullCompleteTree<string> tree, double dispWidth, double dispHeight) {

	unsigned int h = tree.getHeight() + 1;

	for (unsigned int i = 0; i < h; i++) {

			double bros = exp2(i);
			double dividerX = dispWidth * WIDTH_DIV_PERC / (double)(bros + 1.0);
			double dividerY = dispHeight * HEIGHT_DIV_PERC / (double)(h + 1.0);
			ALLEGRO_FONT* font = al_load_font("Sans.ttf", 50-10*i, 0);

		for (unsigned int j = 0; j < tree[i].size(); j++) {


			double height = (dispHeight - dividerY * (h + 1.0)) / h;
			double width = (dispWidth - dividerX * (bros + 1.0)) / bros;
			double xVert1 = j * (width + dividerX) + dividerX;
			double yVert1 = i * (height + dividerY) + dividerY;
			double rx = width/10;
			double ry = height/10;

			al_draw_filled_rounded_rectangle(xVert1, yVert1, xVert1 + width, yVert1 + height, rx, ry, al_map_rgb(BACKGD_COLOR_R, BACKGD_COLOR_G, BACKGD_COLOR_B));
			
			double centerX = xVert1 + width / 2.0;
			double centerY = yVert1 + height / 2.0;
			
			al_draw_text(font, al_color_name(FONT_COLOR), centerX, centerY, ALLEGRO_ALIGN_CENTRE, tree[i][j].c_str());

		}
		al_destroy_font(font);
	}
}
