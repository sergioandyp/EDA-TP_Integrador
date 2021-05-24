#ifndef TRANS
#define TRANS

#include <string>
#include <vector>

class TransactionEntry {
public:
	TransactionEntry(const std::string& jsonString);
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
	TransactionOut(const std::string& jsonString);
	std::string getPublicId();
	double getAmount();

private:
	std::string publicId;
	double amount;			//Revisar tipo de dato numerico. 
};

class Transaction {
public:
	Transaction(const std::string& jsonString);
	std::string getID();
	std::vector<TransactionEntry> getEntries();
	std::vector<TransactionOut> getOutputs();

private:
	std::string id;
	std::vector<TransactionEntry> entries;
	std::vector<TransactionOut> outputs;

};
#endif // TRANS