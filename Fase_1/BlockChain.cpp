#include "BlockChain.h"
#include <iostream>
#include <fstream>      
#include "nlohmann/json.hpp"
//#define DEBUG
using namespace nlohmann;
using namespace std

BlockChain::BlockChain(const std::string& path) {
	// Cargamos el .json y lo formateamos a json
	ifstream inputFile = ifstream(path);
	nlohmann::json j;
	inputFile >> j;
	inputFile.close();

	for (int i = 0; i < j.size(); i++) {
		#ifdef DEBUG
		std::cout << "Bloque" << i << ':' << std::endl;
		#endif
		//Creamos y appendeamos bloque por bloque.
		chain.push_back(Block(j[i]));
	}
}

void BlockChain::saveChain() {
	ofstream file("chain.txt", std::ofstream::out);
	
	for (int bloquesito; bloquesito < chain.size; bloquesito++) {
		file << "blockId: " << chain[bloquesito].blockId << endl;
		file << "nonce: " << chain[bloquesito].nonce << endl;
		file << "prevBlockId: " << chain[bloquesito].prevBlockId << endl;
		file << "merkleRoot: " << chain[bloquesito].merkleRoot << endl;
		for (int trans; trans < (chain[bloquesito]).txs.size(); trans++) {
			file << "Transacción " << trans << endl;
			for (int entry; entry < (chain[bloquesito]).txs.entries.size(); entry++) {
				file << "\tEntrie " << entry << endl;
				file << "\t\tblockid:" << (chain[bloquesito].txs.entries)[entry].blockId << endl;
				file << "\t\ttxid:" << (chain[bloquesito].txs.entries)[entry].txId << endl;
				file << "\t\tsignature:" << (chain[bloquesito].txs.entries)[entry].signature << endl;
				file << "\t\toutputIndex:" << (chain[bloquesito].txs.entries)[entry].outputId << endl;
			}

			for (int outro; outro < (chain[bloquesito]).txs.outputs.size(); outro++) {
				file << "\tOut " << outro << endl;
				file << "\t\tpublicId:" << (chain[bloquesito].txs.outputs)[outro].publicId << endl;
				file << "\t\tamount:" << (chain[bloquesito].txs.outputs)[outro].amount << endl;
			}
		}
	}
	file.close();
}

