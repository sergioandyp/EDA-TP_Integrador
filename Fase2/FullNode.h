#pragma once

#include "Node.h"
#include "Block.h"
#include "HTTPServer.h"
#include <map>



class FullNode : public Node {
public:

    // Crea el nodo con servidor en serverPort y cliente en serverPort+1
    FullNode(unsigned int serverPort);

    bool start();

    virtual void update();
    
    // Accion a realizar a traves del ID, parametros opcionales
    virtual bool doAction(ACTION_ID actionID, std::map<std::string, std::string> params = std::map<std::string, std::string>());

    virtual std::vector<ACTION_ID> getSendActions();

    virtual std::vector<ACTION_ID> getReceiveActions();



private:
    std::vector<Block> blocks;
    HTTPServer server;


};