#pragma once

#include <allegro5/allegro.h>

#include "BlockChain.h"
#include <string>

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
	void drawTreeToBMP(double dispWidth, double dispHeight);

	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_BITMAP* background;
	ALLEGRO_BITMAP* treeBMP;
	DisplayState state;
	
	char bufPath[MAXIMUM_PATH_LENGTH + 1];
	std::string path;
	Block block;
	std::string pathtext;
	BlockChain chain;
	FullCompleteTree<std::string> merkleTree;
	bool validRoot;
};