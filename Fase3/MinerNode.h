#pragma once
#include "FullNode.h"
#include "Transaction.h"

class MinerNode :
    public FullNode
{
public: 
    MinerNode();
    int mining(int ZerosCount);
    int saveTransaction(Transaction tx);
    int stopMining();
    
private:
    std::vector<Transaction> transactions;
    int mining;
};

