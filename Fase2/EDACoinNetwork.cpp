#include "EDACoinNetwork.h"

#include "FullNode.h"
#include "SPVNode.h"

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
bool EDACoinNetwork::createFull(unsigned int serverPort) {

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