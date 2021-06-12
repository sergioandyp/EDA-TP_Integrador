#pragma once

#include <allegro5/allegro.h>

#include "BlockChain.h"
#include <string>

#define MAXIMUM_PATH_LENGTH 100
#define MAXIMUM_KEY_LENGTH 20

#define IM_FMTARGS(FMT)

enum DisplayMode {
	STOP_RUNNING = 0, WAITING, MERKLETREE, NODE
};
enum DisplayState {
	FILESELECT, MENU, CALCULATEMERKLE, DRAWTREE, CREATE, LINK, SEND
};

class Gui {
public:

	//Methods
	Gui();
	~Gui();
	void setup();
	DisplayMode functions();
	void setstate (DisplayState state);
	DisplayState getstate();
	std::string getpath();


private:
	void drawTreeToBMP(double dispWidth, double dispHeight);
	void IPinput(int* octets, std::string ip);
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_BITMAP* background;
	ALLEGRO_BITMAP* treeBMP;
	DisplayState state;
	DisplayMode mode;
	
	char bufPath[MAXIMUM_PATH_LENGTH + 1];
	char bufKey[MAXIMUM_KEY_LENGTH + 1];
	int port1;
	int port2;
	std::string path;
	std::string pathtext;
	int valueToTransfer;
	std::string publicKey;

	int octets1[4];
	int octets2[4];

	Block block;
	BlockChain chain;
	FullCompleteTree<std::string> merkleTree;
	bool validRoot;
};

