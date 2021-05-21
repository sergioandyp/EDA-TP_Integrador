#ifndef TRANS
#define TRANS

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

class TransactionEntry {

	TransactionEntry(const nlohmann::json& json);

private:
	std::string blockId;
	std::string txId;
	std::string signature;
	double outputId;		//Revisar tipo de dato numerico.
};

class TransactionOut {

	TransactionOut(const nlohmann::json& fromJSON);

private:
	std::string publicId;
	double amount;			//Revisar tipo de dato numerico. 
};

class Transaction {
public:
	Transaction();
	Transaction(const nlohmann::json& json);
	std::string getID();

private:
	std::string id;
	std::vector<TransactionEntry> entries;
	std::vector<TransactionOut> outputs;

};
#endif // TRANS