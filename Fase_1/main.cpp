#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include "BlockChain.h"
#include "FullCompleteTree.h"
#include "mygui.h"

#define DEBUG

using namespace std;

void printTree(FullCompleteTree<string> tree);


#include "Allegro.h"
int main() {

	Gui gui;

	gui.setup();

	////Cargamos el path
	//string path = "blockchain_sample_0.json";

	////Creamos la blockchain con el json de base.
	//BlockChain chain;

	//chain.buildFromPath(path);

	//ALLEGRO_BITMAP* display = al_create_bitmap(DISPLAY_SIZE_X, DISPLAY_SIZE_Y);
	////ALLEGRO_DISPLAY* display = al_create_display(DISPLAY_SIZE_X, DISPLAY_SIZE_Y);

	////al_set_target_backbuffer(display);
	//al_set_target_bitmap(display);

	//drawTree(chain.getChain()[0].getMerkleTree(), DISPLAY_SIZE_X, DISPLAY_SIZE_Y);


	//ALLEGRO_DISPLAY* disp = al_create_display(1080, 720);

	//al_get_backbuffer(disp);

	//al_draw_bitmap(display, 0, 0, 0);

	//al_flip_display();


	//cin >> path;

	//al_destroy_bitmap(display);
	//al_destroy_display(disp);


	while (gui.functions()) {

	}


	//for (Block& block : chain.getChain()) {
	//	cout << "Bloque " << block.getBlockId() << ":" << endl;
	//	printTree(block.getMerkleTree());
	//	cout << endl << endl;
	//}

#ifdef DEBUG
	//Guardamos el chain en un archivo.
	//chain.saveChain();
#endif

	return 0;
}

void printTree(FullCompleteTree<string> tree) {
	
	for (unsigned int i = 0; i <= tree.getHeight(); i++) {
		for (unsigned int j = 0; j < tree[i].size(); j++) {
			cout << tree[i][j] << '\t';
		}
		cout << endl;
	}

}

//void testHex() {
//
//	while (true) {
//		unsigned int n; cin >> n;
//		cout << Block::hexCode(n) << endl;
//	}
//
//}