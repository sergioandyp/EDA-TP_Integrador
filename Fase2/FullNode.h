#pragma once

#include "Node.h"
#include "HTTPServer.h"

class FullNode : public Node {
public:

    virtual std::vector<Action> getActions();

private:
    std::vector<std::string> actions;
    HTTPServer server;
};