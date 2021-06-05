#include "SPVNode.h"

using namespace std;

SPVNode::SPVNode(unsigned int serverPort) : server(serverPort) {


}

bool SPVNode::start() {
	return server.start();
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
