#include "Block.h"
#include "Transaction.h"
#include <iostream>
#include <string>
#include <cmath>
#include <nlohmann/json.hpp>
#include <cryptopp/eccrypto.h>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>

//#define DEBUG

using namespace std;
using namespace nlohmann;
using namespace CryptoPP;

string Block::getHash() {
	json headerJSON;
	headerJSON["height"] = header.height;
	headerJSON["nonce"] = header.nonce;
	headerJSON["previousblockid"] = header.prevBlockId;
	headerJSON["merkleroot"] = header.merkleRoot;

	CryptoPP::SHA256 hash;
	string msg = headerJSON.dump();
	string digest;

	hash.Update((const CryptoPP::byte*)msg.data(), msg.size());
	digest.resize(hash.DigestSize());
	hash.Final((CryptoPP::byte*)&digest[0]);

	CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));

	string output;
	encoder.Attach(new CryptoPP::StringSink(output));
	encoder.Put((CryptoPP::byte*)&digest[0], sizeof(digest));
	encoder.MessageEnd();

#ifdef DEBUG
	cout << endl << endl << "Header: " << msg << endl;
	cout << "Hash: " << output << endl << endl;
#endif


	return output;

}

Block::Block()
{
}

Block::Block(const std::string& jsonString) {
	json fromJSON =  nlohmann::json::parse(jsonString);

	//Para cada transacción, creamos la estructura con la 
	// información cargada y la appendeamos.
	for (int i = 0; i < fromJSON["tx"].size(); i++) {
		txs.push_back(Transaction((fromJSON["tx"][i]).dump()));
	}

	// Cargamos la información del JSON
	header.nonce = fromJSON["nonce"];
	blockId = fromJSON["blockid"];
	header.prevBlockId = fromJSON["previousblockid"];
	header.merkleRoot = fromJSON["merkleroot"];
	header.height = fromJSON["height"];
}

void Block::setNonce(unsigned int nonce_){
	header.nonce = nonce_;
}

void Block::setId(std::string ID){
	blockId = ID;
}

FullCompleteTree<string> Block::getMerkleTree() {

	FullCompleteTree<string> merkleTree(2);	// Siempre por lo menos hay dos hojas

	// Creo arbol con cantidad de hojas igual a la potencia de dos mas proxima a txs.size (redondeado para arriba)
	if (txs.size() > 1) {
		merkleTree = FullCompleteTree<string>(exp2(ceil(log2(txs.size()))));
	}

	vector<string> txHashes;
	for (Transaction& tx : txs) {	// Por cada transacción
		string id;
		for (TransactionEntry& entry : tx.getEntries()) {	// Por cada entry en la transacción
			id += entry.getTxId();								// Concateno los txid
		}
		txHashes.push_back(generateID((const unsigned char*)id.c_str()));		// Genero ID en HexCodeASCII
	}

	unsigned int lastRow = merkleTree.getHeight();
	for (int j = 0; j < merkleTree[lastRow].size(); j++) {		// Agrego los nidstr como hojas
		if (j < txHashes.size()) {
			merkleTree[lastRow][j] = txHashes[j];
		}
		else {		// Si no hay mas transacciones, repito la ultima
			merkleTree[lastRow][j] = txHashes[txHashes.size() - 1];
		}
	}

	for (int i = lastRow - 1; i >= 0; i--) {		// Por cada profundidad
		for (int j = 0; j < merkleTree[i].size(); j++) {		// Por cada nodo en esa profundidad
			
			string concat = merkleTree[i + 1][2 * j] + merkleTree[i + 1][2 * j + 1];
			
			merkleTree[i][j] = generateID((const unsigned char*)concat.c_str());
		}
	}

	return merkleTree;
}

// Generador de IDs
string Block::generateID(const unsigned char* str) {
	CryptoPP::SHA256 hash;
	string msg((char*)str);
	string digest;

	hash.Update((const CryptoPP::byte*)msg.data(), msg.size());
	digest.resize(hash.DigestSize());
	hash.Final((CryptoPP::byte*)&digest[0]);

	string output;
	StringSource ss(digest, true, new HexEncoder(new StringSink(output)));

	return output;
}

// Conversión de decimal a hexadecimal tipo string.
string Block::hexCode(const unsigned int id) {
	string output;
	const char convTable[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	for (int i = 2*sizeof(id)-1; i >= 0; i--) {
		int temp = (id & (0xF << (4 * i))) >> (4 * i);
		output += convTable[temp];
	}
	return output;
}

string Block::getBlockId(){
	return blockId;
}
string Block::getPrevBlockId(){
	return header.prevBlockId;
}
string Block::getMerkleRoot(){
	return header.merkleRoot;
}
unsigned int Block::getBlockNonce(){
	return header.nonce;
}

int Block::getBlockNTx(){
	return (int)txs.size();
}

int Block::getBlockHeight(){
	return header.height;
}

vector<Transaction> Block::getBlockTxs(){
	return txs;
}

void Block::printHeader() {
	cout << "blockID: " << blockId << endl;
	cout << "height: " << header.height << endl;
	cout << "merkleRoot: " << header.merkleRoot << endl;
	cout << "nonce: " << header.nonce << endl;
	cout << "prevBlockID: " << header.prevBlockId << endl;
	cout << "nTx: " << txs.size() << endl;
}