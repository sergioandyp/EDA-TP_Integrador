#ifndef CHAIN
#define CHAIN

#include <vector>
#include <string>
#include "Block.h"

class BlockChain {
public:
	BlockChain(const std::string& path);

private:
	std::vector<Block>	chain;
};

#endif // CHAIN