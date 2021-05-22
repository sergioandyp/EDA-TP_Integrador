#include "Block.h"
#include "Transaction.h"
#include <iostream>
//#define DEBUG

using namespace std;
Block::Block(const nlohmann::json& fromJSON) {

	//Para cada transacción, creamos la estructura y la appendeamos.
	for (int i = 0; i < fromJSON["nTx"].size(); i++) {
		txs.push_back(Transaction(fromJSON["tx"][i]));
	}

	nonce = fromJSON["nonce"];
	blockId = fromJSON["blockid"];
	prevBlockId = fromJSON["previousblockid"];
	merkleRoot = fromJSON["merkleroot"];
	
	#ifdef DEBUG
	cout << "\t nonce: " << nonce << endl;
	cout << "\t blockid: " << blockId << endl;
	cout << "\t previousblockid: " << prevBlockId << endl;
	cout << "\t merkleroot: " << merkleRoot << endl;
	#endif
}

unsigned int Block::generateID(unsigned char* str)
{
	unsigned int ID = 0;
	int c;
	while (c = *str++) {
		ID = c + (ID << 6) + (ID << 16) - ID;
	}
	return ID;
}

string Block::hexCode(unsigned int id) {
	string output;
	const char convTable[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	for (int i = 2*sizeof(id); i < 0; i -= 4) {
		int temp = (id & (0xF << (4 * i))) >> (4 * i);
		output += convTable[temp];
	}
	return output; //string
}