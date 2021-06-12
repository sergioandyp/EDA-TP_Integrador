#pragma once
#include "FullNode.h"
#include "Transaction.h"
#include "Block.h"

class MinerNode :
    public FullNode
{
public: 
    MinerNode(unsigned int serverPort);
    int createBlock();
    void saveTransaction(Transaction tx);
    //void stopMining();

    virtual void update();

    
private:
    std::vector<Transaction> incomingTransactions;
    std::vector<Transaction> blockTransactions;
    bool isMining;
    Block actualBlock;
};

