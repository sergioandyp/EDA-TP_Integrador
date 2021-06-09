#include "EDACoinNetwork.h"

#include "FullNode.h"
#include "SPVNode.h"

using namespace std;

// Crea un nodo full. Si no se pudo inicializar correctamente se destruye.
bool EDACoinNetwork::createFull(unsigned int port) {

	unsigned int serverPort = port % 2 == 0 ? port : port - 1;	// Si es par, eligo ese para server
																// si es impar, elijo el anterior para sever

	FullNode* node = new FullNode(serverPort);

	if (!node->start()) {
		delete node;
		return false;
	}

	nodes.push_back(node);

	return true;
}

// Crea un nodo SPV. Si no se pudo inicializar correctamente se destruye.
bool EDACoinNetwork::createSPV(unsigned int serverPort) {

	SPVNode* node = new SPVNode(serverPort);

	if (!node->start()) {
		delete node;
		return false;
	}

	nodes.push_back(node);

	return true;
}

void EDACoinNetwork::updateNodes() {
	for (Node*& node : nodes) {
		node->update();
	}
}

vector<ACTION_ID> EDACoinNetwork::getActionsBetween(Node* senderNode, Node* receiverNode) {

	vector<ACTION_ID> actions;

	for (ACTION_ID sendAction : senderNode->getSendActions()) {
		for (ACTION_ID receiveAction : receiverNode->getReceiveActions()) {
			if (sendAction == receiveAction) {
				actions.push_back(sendAction);
			}
		}
	}

	return actions;
}

std::vector<Node*>& EDACoinNetwork::getNodes() {
	return nodes;
}

bool EDACoinNetwork::makeConnection(unsigned int port1, unsigned int port2) {

	unsigned int clientPort;
	unsigned int serverPort;

	Node* node1 = nullptr;
	Node* node2 = nullptr;

	for (Node* node : nodes) {
		serverPort = node->getServerPort();
		clientPort = node->getClientPort();

		if (serverPort == port1 || clientPort == port1) {
			node1 = node;
		}
		else if (serverPort == port2 || clientPort == port2) {
			node2 = node;
		}
	}

	if (node1 != nullptr && node2 != nullptr) {		// Se encontraron ambos puertos
		if (node1->addConnection(node2)) {
			if (node2->addConnection(node1)) {
				return true;
			}
		}
	}

	return false;

}