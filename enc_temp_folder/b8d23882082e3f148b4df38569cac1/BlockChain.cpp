#include "BlockChain.h"
#include "Block.h"
#include "Transaction.h"
#include <iostream>
#include <fstream>      
#include "nlohmann/json.hpp"

using namespace nlohmann;
using namespace std;

BlockChain::BlockChain(const std::string& path) {
	// Cargamos el .json y lo formateamos a json
	ifstream inputFile = ifstream(path);
	nlohmann::json j;
	inputFile >> j;
	inputFile.close();

	for (int i = 0; i < j.size(); i++) {
		//Creamos y appendeamos bloque por bloque.
		chain.push_back( Block( (j[i]).dump() ) );
	}
}

void BlockChain::saveChain() {
	ofstream file("chain.txt", std::ofstream::out);
	
	for (int bloquesito = 0 ; bloquesito < chain.size(); bloquesito++) {
		file << "Bloque " << bloquesito << endl;
		file << "\tblockId: " << chain[bloquesito].getBlockId() << endl;
		file << "\tnonce: " << chain[bloquesito].getNonce() << endl;
		file << "\tprevBlockId: " << chain[bloquesito].getPrevBlockId() << endl;
		file << "\tmerkleRoot: " << chain[bloquesito].getMerkleRoot() << endl;

		for (int trans= 0; trans < ((chain[bloquesito]).getTxs()).size(); trans++) {
			Transaction transBlock = ((chain[bloquesito]).getTxs())[trans];
			
			file << "\tTransacción " << trans << endl;
			
			vector<TransactionEntry> entries = transBlock.getEntries();
			vector<TransactionOut> outros = transBlock.getOutputs();

			for (int entry = 0; entry < entries.size(); entry++) {
				file << "\t\tEntrie " << entry << endl;
				file << "\t\t\tblockid:" << (entries[entry]).getBlockId() << endl;
				file << "\t\t\ttxid:" << (entries[entry]).getTxId() << endl;
				file << "\t\t\tsignature:" << (entries[entry]).getSignature() << endl;
				file << "\t\t\toutputIndex:" << (entries[entry]).getOutputId() << endl;
			}

			for (int outro = 0; outro < outros.size(); outro++) {
				file << "\t\tOut " << outro << endl;
				file << "\t\t\tpublicId:" << outros[outro].getPublicId() << endl;
				file << "\t\t\tamount:" << outros[outro].getAmount() << endl;
			}
		}
	}
	file.close();
}

vector<Block> BlockChain::getChain() {
	return chain;
}

