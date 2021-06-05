#include "SPVNode.h"

using namespace std;
using namespace nlohmann;

SPVNode::SPVNode(unsigned int serverPort) : server(serverPort) 
{
}

bool SPVNode::start() {
	return server.start();
}


void SPVNode::update() {
	server.run();

	if (server.isRequest()) {
		handleRequest(server.getRequest());
	}

}

vector<ACTION_ID> SPVNode::getSendActions() {
	
	vector<ACTION_ID> actions;

	actions.push_back(TRANSACTION);
	actions.push_back(FILTER);
	actions.push_back(GET_BLOCK_HEADER);
	
	return actions;
}

vector<ACTION_ID> SPVNode::getReceiveActions() {

	vector<ACTION_ID> actions;

	actions.push_back(MERKLE_BLOCK);

	return actions;
}

bool SPVNode::doAction(ACTION_ID actionID, map<string, string> params) {
	switch (actionID)
	{
	case TRANSACTION:
		return false;
		break;
	default:
		break;
	}
	return true;
}


void SPVNode::handleRequest(string request) {

	string url = request.substr(0, request.find('\n'));		// Me quedo solo con la primera linea
	string path = url.substr(request.find("eda_coin/"));	// me quedo con el path
	string body = request.substr(request.find('\n'));		// y el body

	string params = path.substr(path.find('?'));		// Separo parametros
	path = path.substr(0, path.find('?'));				// del path

	if (path.find("send_merkle_block") != path.npos) {

		/*
			INTERPRETAR REQUEST
		*/

		json result = NULL;
		sendResponse(true, result);
	}

}

void SPVNode::sendResponse(bool status, json result) {

	json response;

	response["status"] = status;

	response["result"] = result;

	server.sendResponse(response.dump());

}