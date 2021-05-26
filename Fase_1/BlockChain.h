#ifndef CHAIN
#define CHAIN

#include "Block.h"
#include <vector>
#include <string>

class BlockChain {
public:
	BlockChain();

	//Constructor de la Chain en base al path del .json
	int buildFromPath(const std::string& path); 

	void saveChain();	//Guarda la Chain en "chain.txt"
	std::vector<Block> getChain();

private:
	std::vector<Block> chain;
};

#endif // CHAIN