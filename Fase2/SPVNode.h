#pragma once

#include "Node.h"
#include "HTTPServer.h"
#include "Block.h"
#include <vector>
#include <nlohmann/json.hpp>

class SPVNode : public Node {
public:

	SPVNode(unsigned int serverPort);

	bool start();

	virtual void update();
	
	// Accion a realizar a traves del ID, parametros opcionales
	virtual bool doAction(ACTION_ID actionID, std::map<std::string, std::string> params = std::map<std::string, std::string>());

	virtual std::vector<ACTION_ID> getSendActions();

	virtual std::vector<ACTION_ID> getReceiveActions();

private:
	
	std::vector<BlockHeader> blocks;
	HTTPServer server;

	void handleRequest(std::string request);
	void sendResponse(bool status, nlohmann::json result);

};