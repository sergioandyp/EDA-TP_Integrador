#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <vector>
#include <string>
#include "FullCompleteTree.h"
#include "Transaction.h"

class BlockHeader {
public:
	double height;
	unsigned int nonce;
	std::string blockId;
	std::string prevBlockId;
	std::string merkleRoot;
};


class Block {
public:

	Block();
	Block(const std::string& jsonString);

	// Genera el Merkle tree del bloque seleccionado
	FullCompleteTree<std::string> getMerkleTree();

	// Getters con info de los bloques
	std::string getBlockId();
	int getBlockHeight();
	std::string getPrevBlockId();
	std::string getMerkleRoot();
	std::vector<Transaction> getBlockTxs();
	unsigned int getBlockNonce();
	int getBlockNTx();

private:

	BlockHeader header;

	std::vector<Transaction> txs;	// Vector de transacciones.

	std::string hexCode(const unsigned int id);
	unsigned int generateID(const unsigned char* str);
};

#endif //_BLOCK_H_





