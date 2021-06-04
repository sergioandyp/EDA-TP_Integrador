#pragma once

#include "Node.h"
#include "HTTPServer.h"

class SPVNode : public Node {
public:

	virtual std::vector<Action> getActions();

private:
	HTTPServer server;

};