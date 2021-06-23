#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <vector>
#include <string>
#include "FullCompleteTree.h"
#include "Transaction.h"

class MinerNode;

class BlockHeader {
public:
	double height;
	unsigned int nonce;
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
	void setNonce(unsigned int nonce);
	std::string getHash();
	void setId(std::string ID);
	void printHeader();

private:
	BlockHeader header;
	std::string blockId;
	std::vector<Transaction> txs;	// Vector de transacciones.

	std::string hexCode(const unsigned int id);
	std::string generateID(const unsigned char* str);
};

#endif //_BLOCK_H_





