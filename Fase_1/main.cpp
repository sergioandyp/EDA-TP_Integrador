#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include "BlockChain.h"

using namespace std;

void testTree();

int main() {

	//INCLUIR RUTA DEL JSON
	std::string path = "blockchain_sample_0.json";
	ifstream inputFile = ifstream(path);
	nlohmann::json data;
	inputFile >> data;
	inputFile.close();
	BlockChain chain(data);
	//https://github.com/EDA-ITBA/class-json/blob/main/samples/json/json/main.cpp


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