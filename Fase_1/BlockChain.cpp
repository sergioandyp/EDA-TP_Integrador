#include "BlockChain.h"
#include <iostream>
#include "nlohmann/json.hpp"

using namespace nlohmann;

BlockChain::BlockChain(const nlohmann::json& j) {
	for (int i = 0; i < j.size(); i++) {
		#ifdef DEBUG
		std::cout << "Bloque" << i << ':' << std::endl;
		#endif
		chain.push_back(Block(j[i]));
	}
}

