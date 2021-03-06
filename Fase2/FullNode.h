#pragma once

#include "Node.h"
#include "Block.h"
#include "HTTPServer.h"
#include "HTTPClient.h"
#include <string>
#include <map>
#include <nlohmann/json.hpp>


class FullNode : public Node {
public:

    // Crea el nodo con servidor en serverPort y cliente en serverPort+1
    FullNode(unsigned int serverPort);

    bool start();

    // Accion a realizar a traves del ID, parametros opcionales
    virtual bool doAction(ACTION_ID actionID, std::map<std::string, std::string> params = std::map<std::string, std::string>());
    
    virtual void update();

    virtual std::string getIP();

    virtual unsigned int getServerPort();

    virtual unsigned int getClientPort();

    virtual std::vector<ACTION_ID> getSendActions();

    virtual std::vector<ACTION_ID> getReceiveActions();

    virtual bool addConnection(Node* node);

    virtual std::vector<Node*> getNeighbors();


private:
    std::vector<Block> blocks;
    std::vector<Node*> neighbors;
    HTTPServer server;
    HTTPClient client;
    std::string IP;

    void handleRequest(std::string request);
    void sendResponse(bool status, nlohmann::json result);

};