#include "MinerNode.h"
   
MinerNode:: MinerNode(): FullNode(){
    mining = 0;
}

// Armar mining
int MinerNode::mining(int ZerosCount) {
    // https://www.cryptopp.com/wiki/SHA2
    // https://www.cryptopp.com/wiki/Hash_Functions
}

int MinerNode::saveTransaction(Transaction tx) {
    transactions.push_back(tx);
}

int MinerNode::stopMining(){
    mining = 0;
}