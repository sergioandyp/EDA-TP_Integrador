#pragma once

#include "BlockChain.h"
#include <vector>

enum ACTION_ID { BLOCK, TRANSACTION, MERKLE_BLOCK, FILTER, GET_BLOCK_HEADER, GET_BLOCKS };

class Node {
public:

	virtual std::vector<ACTION_ID> getSendActions() = 0;
	virtual std::vector<ACTION_ID> getReceiveActions() = 0;

	// Accion a realizar a traves del ID, parametros opcionales
	virtual bool doAction(ACTION_ID actionID, std::map<std::string, std::string> params = std::map<std::string, std::string>()) = 0;

	virtual void update() = 0;

	virtual ~Node() = 0;

};