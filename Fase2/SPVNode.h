#pragma once

#include "Node.h"
#include "HTTPServer.h"
#include "HTTPClient.h"
#include "Block.h"
#include <vector>
#include <string>
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

	virtual bool addConnection(Node* node);

	virtual std::vector<Node*> getNeighbors();

	virtual std::string getIP();
	
	virtual unsigned int getServerPort();

	virtual unsigned int getClientPort();


private:
	
	std::vector<BlockHeader> blocks;
	std::vector<Node*> neighbors;
	HTTPServer server;
	HTTPClient client;
	std::string IP;

	void handleRequest(std::string request);
	void sendResponse(bool status, nlohmann::json result);

};