#include "Transaction.h"
#include <iostream>
#include <nlohmann/json.hpp>

using namespace std;
using namespace nlohmann;

TransactionEntry::TransactionEntry(const std::string& jsonString) {
	nlohmann::json fromJSON = nlohmann::json::parse(jsonString);
	blockId = fromJSON["blockid"];
	txId = fromJSON["txid"];
	signature = fromJSON["signature"]; 
	outputId = fromJSON["outputIndex"];
}

TransactionOut::TransactionOut(const std::string& jsonString) {
	nlohmann::json fromJSON = nlohmann::json::parse(jsonString);
	publicId = fromJSON["publicid"]; 
	amount = fromJSON["amount"]; 
}

Transaction::Transaction(const std::string& jsonString) {
	json fromJSON = nlohmann::json::parse(jsonString);

	id = fromJSON["txid"];
	// Creamos y appendeamos las entries
	for (int i = 0; i < fromJSON["vin"].size(); i++) {
		entries.push_back(TransactionEntry(fromJSON["vin"][i].dump()));
	}

	// Creamos y appendeamos las outputs
	for (int i = 0; i < fromJSON["vout"].size(); i++) {
		outputs.push_back(TransactionOut(fromJSON["vout"][i].dump()));
	}
}

string Transaction::getID(){
	return	id;
}

int Transaction::getNTxin() {
	return (int) entries.size();
}
int Transaction::getNTxout() {
	return (int) outputs.size();
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
