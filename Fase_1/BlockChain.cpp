#include "BlockChain.h"
#include "nlohmann/json.hpp"

using namespace nlohmann;

BlockChain::BlockChain(const std::string& path) {
	auto j = json::parse(path);
	for (auto& el : j.items()) {
		//chain.push_back(Block(el));
	}
}

