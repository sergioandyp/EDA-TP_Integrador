#pragma once

#include "BlockChain.h"
#include "Action.h"
#include <vector>

class Node {
public:

	virtual std::vector<Action> getActions() = 0;

};