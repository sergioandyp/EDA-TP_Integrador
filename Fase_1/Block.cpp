#include "Block.h"
#include "Transaction.h"
#include <iostream>
#define DEBUG

using namespace std;
Block::Block(const nlohmann::json& fromJSON) {

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