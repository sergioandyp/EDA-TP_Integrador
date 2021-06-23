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
	int getOutputId();

private:
	std::string blockId;
	std::string txId;
	std::string signature;
	int outputId;		
};

class TransactionOut {
public:
	TransactionOut(const std::string& jsonString);
	std::string getPublicId();
	double getAmount();

private:
	std::string publicId;
	double amount;			 
};

class Transaction {
public:
	Transaction(const std::string& jsonString);
	std::string getID();
	std::vector<TransactionEntry> getEntries();
	std::vector<TransactionOut> getOutputs();
	int getNTxin();
	int getNTxout();

private:
	std::string id;							// Id de la transacción
	std::vector<TransactionEntry> entries;	// Vector de transacciones de entradas
	std::vector<TransactionOut> outputs;	// Vector de transacciones de salidas
};
#endif // TRANS