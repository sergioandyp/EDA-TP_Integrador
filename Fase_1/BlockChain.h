#ifndef CHAIN
#define CHAIN

#include "Block.h"
#include <vector>
#include <string>

class BlockChain {
public:
	BlockChain();
	// BlockChain(const std::string& path);
	int buildFromPath(const std::string& path);
	void saveChain();	//Guarda la Chain en "chain.txt"
	std::vector<Block> getChain();

private:
	std::vector<Block> chain;
};

#endif // CHAIN