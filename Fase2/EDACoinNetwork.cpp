#include "EDACoinNetwork.h"

#include "FullNode.h"
#include "SPVNode.h"

using namespace std;

// Crea un nodo full. Si no se pudo inicializar correctamente se destruye.
bool EDACoinNetwork::createFull(unsigned int serverPort) {

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

vector<ACTION_ID> EDACoinNetwork::getActionsBetween(Node* node1, Node* node2) {

	vector<ACTION_ID> actions;

	for (ACTION_ID sendAction : node1->getSendActions()) {
		for (ACTION_ID receiveAction : node1->getSendActions()) {
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

	unsigned int port;

	Node* node1 = nullptr;
	Node* node2 = nullptr;

	for (Node* node : nodes) {
		port = node->getServerPort();
		if (port == port1) {
			node1 = node;
		}
		else if (port == port2) {
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