#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <vector>
#include <string>
#include "FullCompleteTree.h"
#include "Transaction.h"

class Block {
public:

	Block();
	Block(const std::string& jsonString);

	//std::vector<std::string> getMerklePath(std::string txid);
	FullCompleteTree<std::string> getMerkleTree();

	
	std::string getBlockId();
	int getBlockHeight();
	std::string getPrevBlockId();
	std::string getMerkleRoot();
	std::vector<Transaction> getBlockTxs();
	unsigned int getBlockNonce();
	int getBlockNTx();

private:

	std::vector<Transaction> txs;
	double height;
	unsigned int nonce;
	std::string blockId;
	std::string prevBlockId;
	std::string merkleRoot;

	std::string hexCode(const unsigned int id);
	unsigned int generateID(const unsigned char* str);
};

// Todavia no se usa
// 
// class Node {
//
//private:
//	std::vector<Block> blocks;
//};


#endif //_BLOCK_H_





