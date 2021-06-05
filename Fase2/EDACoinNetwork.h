#pragma once

#include "SPVNode.h"
#include <vector>


class EDACoinNetwork {
public:

	void updateNodes();

	bool createFull(unsigned int serverPort);
	bool createSPV(unsigned int serverPort);

private:
	std::vector<Node*> nodes;
};