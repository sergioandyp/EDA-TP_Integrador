#ifndef _HTTP_S_H_
#define _HTTP_S_H_

#include <boost/asio.hpp>

class HTTPServer {

public:

	HTTPServer(unsigned short port);

	bool start();

	// Se debe llamar continuamente para que el server pueda funcionar
	void run();

	bool isRequest();

	std::string getRequest();
	
	// Envia la respuesta, luego cierra la conexion
	void sendResponse(std::string response);

	void shutdown();

	unsigned int getPort();

private:

	void connectionReceivedCb(const boost::system::error_code& error);

	bool startWaitingConnection();

	void messageReceivedCb(const boost::system::error_code& error, std::size_t size);

	void messageSentCb(const boost::system::error_code& error, std::size_t size);

	//std::string getHTTPResponse(std::string data);

	boost::asio::io_context io_context;
	boost::asio::ip::tcp::acceptor acceptor;
	boost::asio::ip::tcp::socket socket;

	boost::asio::streambuf buff;

	std::string request;
	std::string response;

};

#endif	// _HTTP_S_H_