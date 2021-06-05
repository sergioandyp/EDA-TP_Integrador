#include "FullNode.h"

using namespace std;

FullNode::FullNode(unsigned int serverPort) : server(serverPort) {


}

bool FullNode::start() {
	return server.start();
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
	case TRANSACTION:
		return false;
		break;
	default:
		break;
	}
	return true;
}