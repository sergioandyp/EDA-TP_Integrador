#pragma once

#include "Node.h"
#include "Block.h"
#include "HTTPServer.h"
#include "HTTPClient.h"
#include <string>
#include <map>
#include <nlohmann/json.hpp>
#include <cryptopp/eccrypto.h>
#include <cryptopp/osrng.h>


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


protected:
    std::vector<Block> blocks;
    std::vector<Node*> neighbors;
    HTTPServer server;
    HTTPClient client;
    std::string IP;
    
    CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey privateKey;
    CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey publicKey;
    CryptoPP::AutoSeededRandomPool prng;

    void handleRequest(std::string request);
    void sendResponse(bool status, nlohmann::json result);
    
    // Devuelve la Public Key del nodo
    std::string getPublicKey();
    
    // Firma un mensaje, devuelve la firma
    std::string signMessage(std::string msg);
    bool verifyMessage(std::string msg, std::string sign, std::string pubKey);

};