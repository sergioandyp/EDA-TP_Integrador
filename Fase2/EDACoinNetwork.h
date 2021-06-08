#pragma once

#include "Node.h"
#include "Action.h"
#include <vector>


class EDACoinNetwork {
public:

	void updateNodes();

	// Crea un nodo. Si no se pudo inicializar correctamente se destruye.
	bool createFull(unsigned int serverPort);
	bool createSPV(unsigned int serverPort);

	std::vector<Node*>& getNodes();

	std::vector<ACTION_ID> getActionsBetween(Node* senderNode, Node* ReceiverNode);

	bool makeConnection(unsigned int port1, unsigned int port2);

private:
	std::vector<Node*> nodes;
};