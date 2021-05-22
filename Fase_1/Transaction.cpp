#include "Transaction.h"
#include <iostream>
//#define DEBUG
using namespace std;

TransactionEntry::TransactionEntry(const nlohmann::json& fromJSON) {
	blockId = fromJSON["blockid"];
	txId = fromJSON["txid"];
	signature = fromJSON["signature"]; 
	outputId = fromJSON["outputIndex"];
	#ifdef DEBUG
	cout << "\t\t Entries:" << endl;
	cout << "\t\t\tblockid:" << blockId << endl;
	cout << "\t\t\ttxid:" << txId << endl;
	cout << "\t\t\tsignature:" << signature << endl;
	cout << "\t\t\toutputIndex:" << outputId << endl;
	#endif
}

TransactionOut::TransactionOut(const nlohmann::json& fromJSON) {
	publicId = fromJSON["publicid"]; 
	amount = fromJSON["amount"]; 
	#ifdef DEBUG
	cout << "\t\t Outs:" << endl;
	cout << "\t\t\tpublicid:" << publicId << endl;
	cout << "\t\t\tamount:" << amount << endl;
	#endif
}

Transaction::Transaction(const nlohmann::json& fromJSON) {
	#ifdef DEBUG
	cout << "\tTransacciones:" << endl;
	#endif	
	id = fromJSON["txid"];
	// Creamos y appendeamos las entries
	for (int i = 0; i < fromJSON["vin"].size(); i++) {
		entries.push_back(fromJSON["vin"][i]);
	}

	// Creamos y appendeamos las outputs
	for (int i = 0; i < fromJSON["vout"].size(); i++) {
		outputs.push_back(fromJSON["vout"][i]);
	}
}

string Transaction::getID(){
	return	id;
}

vector<TransactionEntry> Transaction::getEntries() {
	return entries;
}

vector<TransactionOut> Transaction::getOutputs(){
	return outputs;
}

string TransactionEntry ::getBlockId(){
	return blockId;
}
string TransactionEntry::getTxId(){
	return txId;
}
string TransactionEntry::getSignature(){
	return signature;
}
double TransactionEntry::getOutputId(){
	return outputId;
}

string TransactionOut::getPublicId(){
	return publicId;
}
double TransactionOut::getAmount(){
	return amount;
}
