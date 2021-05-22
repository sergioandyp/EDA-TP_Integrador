#ifndef CHAIN
#define CHAIN

#include <vector>
#include <string>
#include "Block.h"
#include <nlohmann/json.hpp>

class BlockChain {
public:
	BlockChain(const std::string& path);
	void saveChain();	//Guarda la Chain en "chain.txt"
	std::vector<Block> getChain();

private:
	std::vector<Block> chain;
};

#endif // CHAIN