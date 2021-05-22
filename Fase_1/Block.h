#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <vector>
#include <string>
#include "FullCompleteTree.h"
#include "Transaction.h"
#include <nlohmann/json.hpp>

class Block {
public:

	Block();
	BlockChain(const std::string& path);

	std::vector<std::string> getMerklePath(std::string txid);
	FullCompleteTree<std::string> getMerkleTree();

private:

	std::vector<Transaction> txs;
	unsigned int nonce;
	std::string blockId;
	std::string prevBlockId;
	std::string merkleRoot;

	unsigned int generateID(unsigned char* str);
	std::string hexCode(unsigned int id);
};

class Node {

private:
	std::vector<Block> blocks;
};

/*" If you want to build a tree of fixed size whose keys will not change, it is more efficient to use a std::vector, sorting the elements with
either std::sort or std::stable_sort, and searching it using std::lower_bound. If you need to support duplicate keys, you would also use std::upper_bound. 
If you just need to see whether or not a particular key is in the tree, you can use std::binary_search"*/

/*Class Nodo	-> vecctor<Block>
		-> Extraer Bloques
lee el file, interpreta en jason, extraer los bloques, y armar los bloques con la info
		->createBlockchainFromFile()
		
Class Block	-> estructura de json
		     vector<tx> tsx;
		-> Block (string jsonBlock)
		     Block (json block)
		-> getMerklePath(txid)
		-> getMerkleTree()*/

/*
int i=255;	//0x 00 00 00 FF
cout << i << endl; //255
cout << hex << i << endl; //FF

fstream fs;
fs.open("output.txt", fstream::in | fstream::out........)
fs<<i	//El notepad lo va a interpretar en ascii  x

string f= hexCodedAscii(i); //int->4bytes, hexa->8 bytes
fs<<f;


string hexcodedAscii (int)
{
	string output;
	const char convTable[16]= {'0', '1', ... 'F'}
	for (int i=sizeof(d)*2; i<0; i-=4){
		int temp = (d&(0xF0000000)<<(4*i))>>(4*i)
		output+=convTable[temp]
	}
	return output; //string
}	// Independiente de si es big o little endian*/





#endif //_BLOCK_H_





