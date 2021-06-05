#include "FullNode.h"
#include <nlohmann/json.hpp>

using namespace std;
using namespace nlohmann;

FullNode::FullNode(unsigned int serverPort) : server(serverPort) {

}

bool FullNode::start() {
	return server.start();
}

void FullNode::update() {
	server.run();

	if (server.isRequest()) {
		handleRequest(server.getRequest());
	}

}

vector<ACTION_ID> FullNode::getSendActions() {
	
	vector<ACTION_ID> actions;

	actions.push_back(BLOCK);
	actions.push_back(TRANSACTION);
	actions.push_back(MERKLE_BLOCK);
	actions.push_back(GET_BLOCKS);
	
	return actions;
}


vector<ACTION_ID> FullNode::getReceiveActions() {

	vector<ACTION_ID> actions;

	actions.push_back(BLOCK);
	actions.push_back(TRANSACTION);
	actions.push_back(FILTER);
	actions.push_back(GET_BLOCK_HEADER);
	actions.push_back(GET_BLOCKS);

	return actions;
}

bool FullNode::doAction(ACTION_ID actionID, map<string, string> params) {
	switch (actionID)
	{
	case BLOCK:
		break;
	case TRANSACTION:
		break;
	case MERKLE_BLOCK:
		break;
	case GET_BLOCKS:
		break;
	default:
		return false;
		break;
	}
	return true;
}

void FullNode::handleRequest(string request) {

	string url = request.substr(0, request.find('\n'));		// Me quedo solo con la primera linea
	string path = url.substr(request.find("eda_coin/"));	// me quedo con el path

	string params = path.substr(path.find('?'));		// Separo parametros
	path = path.substr(0, path.find('?'));				// del path

	if (path.find("send_block") != path.npos) {

		/*
			INTERPRETAR REQUEST
		*/
		sendResponse(true);
	}
	else if (path.find("send_tx") != path.npos) {
		/*
			INTERPRETAR REQUEST
		*/
		sendResponse(true);
	}
	else if (path.find("send_filter") != path.npos) {
		/*
			INTERPRETAR REQUEST
		*/
		sendResponse(true);
	}
	else if (path.find("get_blocks") != path.npos) {
		/*
			INTERPRETAR REQUEST
		*/
		sendResponse(true);
	}
	else if (path.find("get_block_header") != path.npos) {
		/*
			INTERPRETAR REQUEST
		*/
		sendResponse(true);
	}

}

void FullNode::sendResponse(bool status) {

	json response;

	response["status"] = status;

	response["result"] = NULL;

	server.sendResponse(response.dump());

}