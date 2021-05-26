#include "BlockChain.h"
#include <iostream>
#include <fstream>      
#include "nlohmann/json.hpp"

using namespace nlohmann;
using namespace std;

BlockChain::BlockChain()
{
}

int BlockChain::buildFromPath(const std::string& path){

	chain.clear();

	// Cargamos el .json y lo formateamos a json
	try {
		ifstream inputFile = ifstream(path);
		json j;
		inputFile >> j;
		inputFile.close();

		for (int i = 0; i < j.size(); i++) {
			//Creamos y appendeamos bloque por bloque.
			chain.push_back(Block(j[i].dump()));
		}

		return 0;
	}
	catch (const exception& e){
		return 1;	// Si tira excepcion, devuelvo error
	}


}

/************************************************************************************
	saveChain: Creamos y guardamos en un archivo, el contenido de la chain
	una vez parseada por el Json. Util para verificar el correcto funcionamiento
	del parser.
************************************************************************************/
void BlockChain::saveChain() {
	ofstream file("chain.txt", std::ofstream::out);
	
	for (int bloquesito = 0 ; bloquesito < chain.size(); bloquesito++) {
		file << "Bloque " << bloquesito << endl;
		file << "\tblockId: " << chain[bloquesito].getBlockId() << endl;
		file << "\tnonce: " << chain[bloquesito].getBlockNonce() << endl;
		file << "\tprevBlockId: " << chain[bloquesito].getPrevBlockId() << endl;
		file << "\tmerkleRoot: " << chain[bloquesito].getMerkleRoot() << endl;

		for (int trans= 0; trans < ((chain[bloquesito]).getBlockTxs()).size(); trans++) {
			Transaction transBlock = ((chain[bloquesito]).getBlockTxs())[trans];
			
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

