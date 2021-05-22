#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include "BlockChain.h"
#define DEBUG
using namespace std;

void testTree();

int main() {

	//Cargamos el path
	std::string path = "blockchain_sample_0.json";

	//Creamos la blockchain con el json de base.
	BlockChain chain(path);

#ifdef DEBUG
	//Guardamos el chain en un archivo.
	chain.saveChain();
#endif

	return 0;
}

#include "FullCompleteTree.h"
void testTree() {

	unsigned int n;
	cin >> n;

	vector<string> str = {"Raiz", "Hijo 1", "Hijo 2", "Hijo de hijo", "Un hash", "Otro hash", "Mas hashes", "Hoja"};

	FullCompleteTree<string> tree(n, "BASURA");

	unsigned int count = 0;

	for (unsigned int i = 0; i < tree.getRows(); i++) {
		for (unsigned int j = 0; j < tree[i].size(); j++) {
			tree[i][j] = str[count++];
		}
	}

	for (unsigned int i = 0; i < tree.getRows(); i++) {
		for (unsigned int j = 0; j < tree[i].size(); j++) {
			cout << tree[i][j] << '\t';
		}
		cout << endl;
	}

}