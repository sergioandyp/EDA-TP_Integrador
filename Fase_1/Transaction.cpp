#include "Transaction.h"
using namespace std;

TransactionEntry::TransactionEntry(const nlohmann::json& fromJSON) {
	blockId = fromJSON["blockid"];
	txId = fromJSON["txid"];
	signature = fromJSON["signature"]; 
	outputId = fromJSON["outputIndex"];
}

TransactionOut::TransactionOut(const nlohmann::json& fromJSON) {
	publicId = fromJSON["publicid"]; 
	amount = fromJSON["amount"]; 
}

Transaction::Transaction(const nlohmann::json& fromJSON) {
	id = fromJSON["txid"];
	for (auto& el : fromJSON["vin"].items()) {
		//entries.push_back(TransactionEntry(el));
	}

	for (auto& el : fromJSON["vout"].items()) {
		//outputs.push_back(TransactionOut(el));
	}
}

string Transaction::getID(){
	return	id;
}