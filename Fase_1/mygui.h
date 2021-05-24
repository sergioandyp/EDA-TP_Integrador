#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_allegro5.h"
#include "BlockChain.h"
#include <string>
#include <vector>

#define MAXIMUM_PATH_LENGTH 100

enum DisplayState {
	STOP_RUNNING = 0, WAITING, FILESELECT, MENU, CALCULATEMERKLE, DRAWTREE
};

class Gui {
public:

	//Methods
	Gui();
	~Gui();
	void setup();
	DisplayState functions();
	void setstate (DisplayState state);
	DisplayState getstate();
	std::string getpath();


private:

	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_BITMAP* background = NULL;
	DisplayState state;
	
	char bufPath[MAXIMUM_PATH_LENGTH + 1] = { 0 };
	std::string path;
	Block block;
	std::string pathtext;
	BlockChain chain;
	FullCompleteTree<std::string> merkleTree;
	bool validRoot;
};