#ifndef CHAIN
#define CHAIN

#include <vector>
#include <string>
#include "Block.h"

class BlockChain {
public:
	BlockChain(const std::string& path);
	void saveChain();	//Guarda la Chain en "chain.txt"
	std::vector<Block> getChain();

private:
	std::vector<Block> chain;
};

#endif // CHAIN