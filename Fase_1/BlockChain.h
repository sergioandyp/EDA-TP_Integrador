#ifndef CHAIN
#define CHAIN

#include <vector>
#include <string>
#include "Block.h"
#include <nlohmann/json.hpp>

class BlockChain {
public:
	BlockChain(const nlohmann::json& path);
	void saveChain();	//Guarda la Chain en "chain.txt"

private:
	std::vector<Block>	chain;
};

#endif // CHAIN