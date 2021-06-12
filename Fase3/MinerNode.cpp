#include "MinerNode.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <cmath>

using namespace std;
using namespace nlohmann;

#define N   4

MinerNode::MinerNode(unsigned int serverPort) : FullNode(serverPort){
    isMining = 0;
    srand(time(NULL));
}

void MinerNode::update() {
    this->FullNode::update();
    static unsigned int nonce;
    nonce += (unsigned int) (rand() - RAND_MAX / 2);
    actualBlock.setNonce(nonce);
    string newHash = actualBlock.getHash();
    //cout << "NEW HASH: " << newHash << endl;

    if (newHash.substr(0, N) == (string(N, '0'))) {
        actualBlock.setId(newHash);
        cout << "Encontramos nuevo HASH: \t" << newHash << endl;
    }

}


// Armar mining
int MinerNode::createBlock() {
    // https://www.cryptopp.com/wiki/SHA2
    // https://www.cryptopp.com/wiki/Hash_Functions 
    try {
        json blockJson;
        blockJson["height"] = FullNode::blocks.size();
        blockJson["previousblockid"] = FullNode::blocks[FullNode::blocks.size() - 1].getBlockId();

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
        incomingTransactions.erase(incomingTransactions.begin(), incomingTransactions.begin() + txLarge);
        blockJson["nonce"] = string("00000000") + string("00000000");

        actualBlock = Block(blockJson.dump());
        return true;
    }
    catch (const exception& e) {
        return false;
    }
}

void MinerNode::saveTransaction(Transaction tx) {
    incomingTransactions.push_back(tx);
}

//void MinerNode::stopMining() {
//    isMining = 0;
//}