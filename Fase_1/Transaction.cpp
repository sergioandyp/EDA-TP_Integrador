#include "Transaction.h"
#define DEBUG
using namespace std;

TransactionEntry::TransactionEntry(const nlohmann::json& fromJSON) {
	blockId = fromJSON["blockid"];
	txId = fromJSON["txid"];
	signature = fromJSON["signature"]; 
	outputId = fromJSON["outputIndex"];
	#ifdef DEBUG
	cout << "\t\t Entries:"
	cout << "\t\t\tblockid:" << blockid << endl;
	cout << "\t\t\ttxid:" << blockid << endl;
	cout << "\t\t\tsignature:" << signature << endl;
	cout << "\t\t\toutputIndex:" << outputId << endl;
	#endif
}

TransactionOut::TransactionOut(const nlohmann::json& fromJSON) {
	publicId = fromJSON["publicid"]; 
	amount = fromJSON["amount"]; 
	#ifdef DEBUG
	cout << "\t\t Outs:"
	cout << "\t\t\tpublicid:" << publicid << endl;
	cout << "\t\t\tamount:" << amount << endl;
	#endif
}

Transaction::Transaction(const nlohmann::json& fromJSON) {
	#ifdef DEBUG
	cout << "\tTransacciones:" << endl;
	#endif	
	id = fromJSON["txid"];
	for (int i = 0; i < fromJSON["vin"].size(); i++) {
		entries.push_back(fromJSON["vin"][i]);
	}

	for (int i = 0; i < fromJSON["vout"].size(); i++) {
		outputs.push_back(fromJSON["vout"][i]);
	}
}

string Transaction::getID(){
	return	id;
}