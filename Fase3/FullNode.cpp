#include "FullNode.h"
#include <iostream>
#include <iomanip>

#include <cryptopp/asn.h>
#include <cryptopp/oids.h>	// ASN1
#include <cryptopp/cryptlib.h>
#include <cryptopp/secblock.h>
#include <cryptopp/filters.h>
#include <cryptopp/integer.h>
#include <cryptopp/osrng.h>
#include <cryptopp/files.h>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>

#define DEBUG

using namespace std;
using namespace nlohmann;
using namespace CryptoPP;


FullNode::FullNode(unsigned int serverPort) : server(serverPort), client(serverPort+1) , IP("127.0.0.1"), prng()
{
	privateKey.Initialize( prng, ASN1::secp256k1() );
	//privateKey.Validate( prng, 3 );
	privateKey.MakePublicKey(publicKey);
    publicKey.AccessGroupParameters().SetPointCompression(true);      // Clave comprimida


#ifdef DEBUG
    cout << "Creado nodo Full en " << IP << ":" << serverPort << " con publicKey: " << getPublicKey() << endl;
#endif

}

bool FullNode::start() {
	return server.start();
}

void FullNode::update() {
	server.run(); 

    if(client.isBusy())
		client.clientRun();

	if (server.isRequest()) {
		handleRequest(server.getRequest());
	}

}

vector<ACTION_ID> FullNode::getSendActions() {
	
	vector<ACTION_ID> actions;

	actions.push_back(BLOCK);
	actions.push_back(TRANSACTION);
	actions.push_back(MERKLE_BLOCK);
	actions.push_back(GET_BLOCKS);
	
	return actions;
}


vector<ACTION_ID> FullNode::getReceiveActions() {

	vector<ACTION_ID> actions;

	actions.push_back(BLOCK);
	actions.push_back(TRANSACTION);
	actions.push_back(FILTER);
	actions.push_back(GET_BLOCK_HEADER);
	actions.push_back(GET_BLOCKS);

	return actions;
}

bool FullNode::doAction(ACTION_ID actionID, map<string, string> params) {
    std::string host = params["IP"];
    switch (actionID)
    {
        case TRANSACTION:
        {
            auto Tx = R"(
			    {
				    "nTxin": 1,
				    "nTxout" : 4,
				    "txid" : "712331CE",
				    "vin" : [
					    {
					    "blockid": "0000084D",
						    "outputIndex" : 2,
						    "signature" : "00000077",
						    "txid" : "0000007E"
					    }
					    ],
				    "vout": [
						    {
							    "amount": 0,
							    "publicid" : "2"
						    }						  
						    ]
			    } 
		    )";

            json txJson = json::parse(Tx);
            txJson["vout"][0]["amount"] = stod(params["amount"]);
            txJson["vout"][0]["publicid"] = params["pubkey"];
            client.postRequest(host+"/eda_coin/send_tx/", txJson.dump(), (unsigned int) stoi(params["portDest"]));
            return true;
            break;
        }
        case BLOCK:
        {
            auto block = R"(
		    {
                "blockid": "13878957",
                "height": 0,
                "merkleroot": "80EEF9F8",
                "nTx": 4,
                "nonce": 4733,
                "previousblockid": "00000000",
                "tx": [
                    {
                        "nTxin": 1,
                        "nTxout": 4,
                        "txid": "712331CE",
                        "vin": [
                            {
                                "blockid": "0000084D",
                                "outputIndex": 2,
                                "signature": "00000077",
                                "txid": "0000007E"
                            }
                        ],
                        "vout": [
                            {
                                "amount": 0,
                                "publicid": "91218912199121891218"
                            },
                            {
                                "amount": 1,
                                "publicid": "91218912199121891218"
                            },
                            {
                                "amount": 2,
                                "publicid": "91218912199121891218"
                            },
                            {
                                "amount": 1,
                                "publicid": "91218912199121891218"
                            }
                        ]
                    },
                    {
                        "nTxin": 3,
                        "nTxout": 2,
                        "txid": "215E228D",
                        "vin": [
                            {
                                "blockid": "00000709",
                                "outputIndex": 4,
                                "signature": "00000A7B",
                                "txid": "000009EB"
                            },
                            {
                                "blockid": "00000F84",
                                "outputIndex": 3,
                                "signature": "00000D35",
                                "txid": "000004E5"
                            },
                            {
                                "blockid": "000005D4",
                                "outputIndex": 1,
                                "signature": "00000F92",
                                "txid": "0000042A"
                            }
                        ],
                        "vout": [
                            {
                                "amount": 2,
                                "publicid": "91218912199121891218"
                            },
                            {
                                "amount": 2,
                                "publicid": "91218912199121891218"
                            }
                        ]
                    },
                    {
                        "nTxin": 2,
                        "nTxout": 5,
                        "txid": "6A808C27",
                        "vin": [
                            {
                                "blockid": "00000BA8",
                                "outputIndex": 0,
                                "signature": "00001265",
                                "txid": "00000B2F"
                            },
                            {
                                "blockid": "0000031F",
                                "outputIndex": 3,
                                "signature": "0000079E",
                                "txid": "00001112"
                            }
                        ],
                        "vout": [
                            {
                                "amount": 0,
                                "publicid": "91218912199121891218"
                            },
                            {
                                "amount": 1,
                                "publicid": "91218912199121891218"
                            },
                            {
                                "amount": 0,
                                "publicid": "91218912199121891218"
                            },
                            {
                                "amount": 1,
                                "publicid": "91218912199121891218"
                            },
                            {
                                "amount": 1,
                                "publicid": "91218912199121891218"
                            }
                        ]
                    },
                    {
                        "nTxin": 4,
                        "nTxout": 1,
                        "txid": "391C912C",
                        "vin": [
                            {
                                "blockid": "00000EAE",
                                "outputIndex": 3,
                                "signature": "00000679",
                                "txid": "00000A4B"
                            },
                            {
                                "blockid": "00000FB5",
                                "outputIndex": 0,
                                "signature": "00000902",
                                "txid": "00000D86"
                            },
                            {
                                "blockid": "00001060",
                                "outputIndex": 1,
                                "signature": "000011E1",
                                "txid": "000004AF"
                            },
                            {
                                "blockid": "00000375",
                                "outputIndex": 0,
                                "signature": "00000A9B",
                                "txid": "000006E1"
                            }
                        ],
                        "vout": [
                            {
                                "amount": 1,
                                "publicid": "91218912199121891218"
                            }
                        ]
                    }
                ]
            })";

            json blockJson = json::parse(block);
            client.postRequest(host+"/eda_coin/send_block/", blockJson.dump(), (unsigned int) stoi(params["portDest"]));
            return true;
            break;
        }
	    case MERKLE_BLOCK:
        {    
            //Revisar que lo sgte no explote.
            //auto merkleBlock = R"({"Nombre": "El Pepe"})";
            auto merkleBlock = R"(
            {
                "blockid": "ABCD123",
                "tx": [
			    {
				    "nTxin": 1,
				    "nTxout": 4,
				    "txid": "712331CE",
				    "vin": [
					    {
					        "blockid": "0000084D",
						    "outputIndex": 2,
						    "signature": "00000077",
						    "txid": "0000007E"
					    }
					    ],
				    "vout": [
						    {
							    "amount": 0,
							    "publicid": "91218912199121891218"
						    }
						    ]
			    }
                ],
                "txPos": 123,
                "merklePath": [
                    {
                        "Id": "1234"
                    }
                ]
            })";




		    json merkleBlockJson = json::parse(merkleBlock);  
            //std::cout << std::setw(4) << merkleBlockJson << "\n\n";
		    client.postRequest(host+"/eda_coin/send_merkle_block/", merkleBlockJson.dump(), (unsigned int) stoi(params["portDest"]));	
		    return true;
            break;
        }

	    case GET_BLOCKS:
        {   
            int block_id = 0;  // modificar por stoi(params["block_id"])
            int count = 0;     // modificar por stoi(params["count"])

            string url = host + "/eda_coin/get_blocks?block_id=" + to_string(block_id) + "&count=" + to_string(count);
            client.getRequest(url, (unsigned int) stoi(params["portDest"]));
            return true;
            break;
       }
	    default:
		    return false;
		    break;
	    }
	    return false;
}

std::vector<Node*> FullNode::getNeighbors(){
	return this->neighbors;
}

bool FullNode::addConnection(Node* node) {
    neighbors.push_back(node);
    return true;
}

void FullNode::handleRequest(string request) {

	string url = request.substr(0, request.find('\n'));		// Me quedo solo con la primera linea
	string path = url.substr(url.find("eda_coin/"));	// me quedo con el path

    string params;
    if (path.find('?') != path.npos) {
        params = path.substr(path.find('?'));		// Separo parametros
        path = path.substr(0, path.find('?'));				// del path
    }

    string body = request.substr(request.find("\r\n\r\n")+4);

#ifdef DEBUG
    cout << "Message received: " << request << endl;
    cout << "\tURL: " << url << endl;
    cout << "\tparams: " << params << endl;
    cout << "\tcontent: " << body << endl;
#endif

	if (path.find("send_block") != path.npos) {

        Block newBlock(body);

		json result = NULL;
        bool status = true;
        if (newBlock.getHash() != newBlock.getBlockId()                             // Bloque invalido
            || newBlock.getBlockId().substr(0, CHALLENGE) != string(CHALLENGE, '0')) {      // No cumple el challenge
            status = false;
            result = 2;
        }

		sendResponse(status, result);
	}
	else if (path.find("send_tx") != path.npos) {

        Transaction tx(body);

        json result = NULL;
        bool status = true;
        if (!verifyTransaction(tx)) {
            status = false;
            result = 2;
        }

		sendResponse(status, result);
	}
	else if (path.find("send_filter") != path.npos) {
		/*
			INTERPRETAR REQUEST
		*/
		json result = NULL;
		sendResponse(true, result);
	}
	else if (path.find("get_blocks") != path.npos) {
		/*
			INTERPRETAR REQUEST
		*/
		json result = NULL;
		sendResponse(true, result);
	}
	else if (path.find("get_block_header") != path.npos) {
		/*
			INTERPRETAR REQUEST
		*/
		json result = NULL;
		sendResponse(true, result);
	}
	else {
		json result = 1;
		sendResponse(false, result);
	}

}

void FullNode::sendResponse(bool status, json result) {

	json response;

	response["status"] = status;

	response["result"] = result;

	server.sendResponse(response.dump());

}

string FullNode::getIP(){
	return IP;
}

unsigned int FullNode::getClientPort(){
	return client.getPort();
}

unsigned int FullNode::getServerPort(){
	return server.getPort();
}

string FullNode::getPublicKey() {
    string key;
    publicKey.Save(HexEncoder(new StringSink(key)).Ref());  // Para almacenarlo en ASCII
    return key;
}

string FullNode::signMessage(string msg) {

    ECDSA<ECP, SHA256>::Signer signer(privateKey);

    // Determine maximum size, allocate a string with the maximum size
    size_t siglen = signer.MaxSignatureLength();
    string signature(siglen, 0x00);

    signer.SignMessage(prng, (byte*)msg.data(), msg.size(), (byte*)signature.data());
    signature.resize(siglen);

    string signStr;
    StringSource ss(signature, true, new HexEncoder(new StringSink(signStr)));  // de Hex a ASCII

    return signStr;
}

bool FullNode::verifyMessage(string msg, string sign, string pubKey) {

    StringSource pubKeyHex(pubKey, true, new HexDecoder);  // HexDecoder pasa de ASCII a hex

    ECDSA<ECP, SHA256>::PublicKey pub;      // Para guardar la clave publicKey recibida
    pub.AccessGroupParameters().SetPointCompression(true);  // Clave comprimida

    pub.Load(pubKeyHex);

    ECDSA<ECP, SHA256>::Verifier verifier(pub);

    string signHex;
    StringSource ss(sign, true, new HexDecoder(new StringSink(signHex)));
    
    return verifier.VerifyMessage((byte*)msg.data(), msg.size(), (byte*)signHex.data(), signHex.size());
}

bool FullNode::verifyTransaction(Transaction& trans) {

    for (TransactionEntry& entry : trans.getEntries()) {
        string msg;
        
        TransactionOut* transOut = searchOutput(entry);
        if (transOut == nullptr) {
            return false;           // No se puede verificar, ya que la transaccion no esta en la blockchain
        }
        
        msg += entry.getBlockId();		// Concatenamos los campos para hashear
        msg += entry.getTxId();
        msg += entry.getOutputId();

        for (TransactionOut& out : trans.getOutputs()) {
            msg += out.getAmount();
            msg += out.getPublicId();
        }

        if (!verifyMessage(msg, entry.getSignature(), transOut->getPublicId())) {
            return false;   // Transaccion fraudulenta, la firma no corresponde
        }

    }

    return true;        // Todo OK, transaccion verificada
}

Block* FullNode::searchBlock(string blockId) {
    for (Block& block : blocks) {
        if (block.getBlockId() == blockId)
            return &block;
    }

    return nullptr;
}

Transaction* FullNode::searchTransaction(Block& block, string transId) {
    for (Transaction& trans : block.getBlockTxs()) {
        if (trans.getID() == transId)
            return &trans;
    }

    return nullptr;
}

TransactionOut* FullNode::searchOutput(TransactionEntry& entry) {

    Block* block = searchBlock(entry.getBlockId());

    if (block != nullptr) {

        Transaction* trans = searchTransaction(*block, entry.getTxId());

        if (trans != nullptr) {
            if (trans->getNTxout() > entry.getOutputId()) {
                return &(trans->getOutputs()[entry.getOutputId()]);
            }
        }

    }

    return nullptr;
}