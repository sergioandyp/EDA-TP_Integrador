#ifndef TRANS
#define TRANS

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

class TransactionEntry {
public:
	TransactionEntry(const nlohmann::json& fromJSON);
	std::string getBlockId();
	std::string getTxId();
	std::string getSignature();
	double getOutputId();

private:
	std::string blockId;
	std::string txId;
	std::string signature;
	double outputId;		//Revisar tipo de dato numerico.
};

class TransactionOut {
public:
	TransactionOut(const nlohmann::json& fromJSON);
	std::string getPublicId();
	double getAmount();

private:
	std::string publicId;
	double amount;			//Revisar tipo de dato numerico. 
};

class Transaction {
public:
	Transaction(const nlohmann::json& json);
	std::string getID();
	std::vector<TransactionEntry> getEntries();
	std::vector<TransactionOut> getOutputs();

private:
	std::string id;
	std::vector<TransactionEntry> entries;
	std::vector<TransactionOut> outputs;

};
#endif // TRANS