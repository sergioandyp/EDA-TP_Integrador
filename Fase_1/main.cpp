#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include "BlockChain.h"
#include "FullCompleteTree.h"
#define DEBUG
using namespace std;

void printTree(FullCompleteTree<string> tree);


int main() {

	//Cargamos el path
	std::string path = "blockchain_sample_1.json";

	//Creamos la blockchain con el json de base.
	BlockChain chain(path);

	for (Block& block : chain.getChain()) {
		cout << "Bloque " << block.getBlockId() << ":" << endl;
		printTree(block.getMerkleTree());
		cout << endl << endl;
	}

#ifdef DEBUG
	//Guardamos el chain en un archivo.
	chain.saveChain();
#endif

	return 0;
}

void printTree(FullCompleteTree<string> tree) {
	
	for (unsigned int i = 0; i < tree.getRows(); i++) {
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