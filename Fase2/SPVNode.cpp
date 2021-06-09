#include "SPVNode.h"

using namespace std;
using namespace nlohmann;

SPVNode::SPVNode(unsigned int serverPort) : server(serverPort), client(serverPort+1), IP("127.0.0.1")
{
}

bool SPVNode::start() {
	return server.start();
}


void SPVNode::update() {
	server.run();

	if(client.isBusy())
		client.clientRun();

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
	std::string host = params["IP"];
	switch (actionID){
	case TRANSACTION:
	{
		auto Tx = R"(
			    {
				    "nTxin": 1,
				    "nTxout" : 4,
				    "txid" : "712331CE",
				    "vin" : [
					    {
					    "blockid": "0000084D",
						    "outputIndex" : 2,
						    "signature" : "00000077",
						    "txid" : "0000007E"
					    }
					    ],
				    "vout": [
						    {
							    "amount": 0,
							    "publicid" : "2"
						    }						  
						    ]
			    } 
		    )";

		json txJson = json::parse(Tx);
		txJson["vout"][0]["amount"] = stod(params["amount"]);
		txJson["vout"][0]["publicid"] = params["pubkey"];
		client.postRequest(host + "/eda_coin/send_tx/", txJson.dump(), (unsigned int)stoi(params["portDest"]));
		return false;
		break;
	}
	case FILTER: 
	{	
		auto filter = R"({"Key": "pubkey1"})";
		json filterJson = json::parse(filter);

		client.postRequest(host+"/eda_coin/send_filter/", filterJson.dump(), (unsigned int) stoi(params["portDest"]));
		return true;
		break;
	}

	case GET_BLOCK_HEADER:
	{
		int block_id = 0;  // modificar por stoi(params["block_id"])
        int count = 0;     // modificar por stoi(params["count"])
		string url = host + "/eda_coin/get_blocks?block_id=" + to_string(block_id) + "&count=" + to_string(count);
		client.getRequest(url, (unsigned int) stoi(params["portDest"]));
		return true;
		break;
	}
	default:
		break;
	}
	return false;
}

std::vector<Node*> SPVNode::getNeighbors(){
	return this->neighbors;
}

void SPVNode::handleRequest(string request) {

	string url = request.substr(0, request.find('\n'));		// Me quedo solo con la primera linea
	
	string path;
	if (request.find("eda_coin/") != request.npos) {
		path = url.substr(request.find("eda_coin/"));	// me quedo con el path
	}
	
	string body = request.substr(request.find('\n'));		// y el body

	string params;
	if (path.find('?') != path.npos) {
		params = path.substr(path.find('?'));		// Separo parametros
		path = path.substr(0, path.find('?'));				// del path
	}

	if (path.find("send_merkle_block") != path.npos) {

		/*
			INTERPRETAR REQUEST
		*/

		json result = NULL;
		sendResponse(true, result);
	}

}

bool SPVNode::addConnection(Node* node) {
	if (dynamic_cast<SPVNode*>(node))	// Si node puedo castearlo a SPVNode*,
		return false;					// estoy intentando conectar nodos SPV

	neighbors.push_back(node);
    return true;
}

void SPVNode::sendResponse(bool status, json result) {

	json response;

	response["status"] = status;

	response["result"] = result;

	server.sendResponse(response.dump());

}

string SPVNode::getIP(){
	return IP;
}
	
unsigned int SPVNode::getClientPort(){
	return client.getPort();
}

unsigned int SPVNode::getServerPort(){
	return server.getPort();
}