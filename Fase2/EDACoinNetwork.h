#pragma once

#include "SPVNode.h"
#include <vector>


class EDACoinNetwork {
public:

	void updateNodes();

	// Crea un nodo. Si no se pudo inicializar correctamente se destruye.
	bool createFull(unsigned int serverPort);
	bool createSPV(unsigned int serverPort);

private:
	std::vector<Node*> nodes;
};