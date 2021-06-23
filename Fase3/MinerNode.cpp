#include "MinerNode.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <cmath>

#define DEBUG

using namespace std;
using namespace nlohmann;

MinerNode::MinerNode(unsigned int serverPort) : FullNode(serverPort){
    isMining = 0;
    srand(time(NULL));
    createBlock();
}

void MinerNode::update() {
    this->FullNode::update();
    mine();
}

bool MinerNode::mine() {
    static unsigned int nonce;
    nonce += (unsigned int)(rand() - RAND_MAX / 2);
    actualBlock.setNonce(nonce);
    string newHash = actualBlock.getHash();

    if (newHash.substr(0, CHALLENGE) == (string(CHALLENGE, '0'))) {
        actualBlock.setId(newHash);
#ifdef DEBUG
        cout << "Encontramos nuevo HASH: \t" << newHash << endl;
        actualBlock.printHeader();
        cout << endl;
#endif
        FullNode::blocks.push_back(actualBlock);    // Agrega el bloque a la blockchain
        createBlock();      // Creamos nuevo bloque para minar
        return true;
    }

    return false;
}

int MinerNode::createBlock() {
    try {
        json blockJson;
        blockJson["height"] = FullNode::blocks.size();
        if (FullNode::blocks.size() > 0) {
            blockJson["previousblockid"] = FullNode::blocks[FullNode::blocks.size() - 1].getBlockId();
        }
        else {
            blockJson["previousblockid"] = to_string(0);
        }

        int txLarge = incomingTransactions.size();
        blockJson["nTx"] = txLarge;
        for (int i = 0; i < txLarge; i++)
        {
            Transaction& trans = incomingTransactions[i];
            blockJson["tx"][i]["txid"] = trans.getID();

            blockJson["tx"][i]["nTxin"] = trans.getNTxin();
            for (int j = 0; j < trans.getNTxin(); j++) {
                blockJson["tx"][i]["vin"][j]["blockid"] = trans.getEntries()[j].getBlockId();
                blockJson["tx"][i]["vin"][j]["txid"] = trans.getEntries()[j].getTxId();
                blockJson["tx"][i]["vin"][j]["signature"] = trans.getEntries()[j].getSignature();
                blockJson["tx"][i]["vin"][j]["outputIndex"] = trans.getEntries()[j].getOutputId();
            }

            blockJson["tx"][i]["nTxout"] = trans.getNTxout();
            for (int j = 0; j < trans.getNTxout(); j++) {
                blockJson["tx"][i]["vout"][j]["publicid"] = trans.getOutputs()[j].getPublicId();
                blockJson["tx"][i]["vout"][j]["amount"] = trans.getOutputs()[j].getAmount();
            }
        }

        blockJson["tx"][txLarge]["nTxin"] = 0;
        blockJson["tx"][txLarge]["nTxout"] = 1;
        blockJson["tx"][txLarge]["txid"] = FullNode::getPublicKey();    // Aca va el hash de la tx
        blockJson["tx"][txLarge]["vout"][0]["publicid"] = FullNode::getPublicKey();   // Sumo la recompensa por minar
        blockJson["tx"][txLarge]["vout"][0]["amount"] = 50;

        incomingTransactions.erase(incomingTransactions.begin(), incomingTransactions.begin() + txLarge);   // Borramos de la cola de transacciones
        blockJson["nonce"] = 0;

        blockJson["merkleroot"] = "";
        blockJson["blockid"] = "";
        actualBlock = Block(blockJson.dump());

        string root = actualBlock.getMerkleTree()[0][0];
        blockJson["merkleroot"] = root;
        actualBlock = Block(blockJson.dump());

        return true;
    }
    catch (const exception& e) {
#ifdef DEBUG
        cout << "Error creating Block: " << e.what() << endl;
#endif
        return false;
    }
}

void MinerNode::saveTransaction(Transaction tx) {
    incomingTransactions.push_back(tx);
}