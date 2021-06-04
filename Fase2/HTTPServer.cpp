#include "HTTPServer.h"

#include <boost/bind/bind.hpp>
#include <boost/asio/serial_port.hpp>

#include <iostream>

#define DEBUG

using boost::asio::ip::tcp;
using namespace std;

HTTPServer::HTTPServer(unsigned short port) :
				io_context(),
				acceptor(io_context, tcp::endpoint(tcp::v4(), port)),
				socket(io_context),				// Inicializa socket sin abrirlo
				buff(),
				request()
{
}

bool HTTPServer::start() {

	if (socket.is_open()) {
#ifdef DEBUG
		cout << "Socket is already open, cannot accept more connections" << endl;
#endif
		return false;
	}
	
#ifdef DEBUG
	cout << "Server started" << endl;
#endif

	return startWaitingConnection();
}

void HTTPServer::run() {
	io_context.run_one();
}

void HTTPServer::shutdown() {
	if (socket.is_open()) {
		socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
		socket.close();
#ifdef DEBUG
		cout << "Connection closed" << endl;
#endif
	}
}

bool HTTPServer::isRequest() {
	return !request.empty();
}

string HTTPServer::getRequest() {
	string temp = request;
	request.empty();
	return temp;
}

void HTTPServer::sendResponse(std::string response) {

#ifdef DEBUG
	cout << "Sending response" << endl;
	cout << "Response:" << endl << response << endl << endl;
#endif

	boost::asio::async_write(socket, boost::asio::buffer(response),
		boost::bind(&HTTPServer::messageSentCb, this,
			boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

}


bool HTTPServer::startWaitingConnection() {

	if (socket.is_open()) {
#ifdef DEBUG
		cout << "Socket is already open, cannot accept more connections" << endl;
#endif
		return false;
	}
#ifdef DEBUG
	cout << "Waiting for connection..." << endl;
#endif

	acceptor.async_accept(socket,
		boost::bind(&HTTPServer::connectionReceivedCb, this, boost::asio::placeholders::error));

	return true;
}

void HTTPServer::connectionReceivedCb(const boost::system::error_code& error) {

	if (!error) {
#ifdef DEBUG
		cout << "Connection received" << endl;
#endif
		boost::asio::async_read_until(socket, buff, "\r\n\r\n",			// Leemos hasta el terminador HTTP
			boost::bind(&HTTPServer::messageReceivedCb, this,
				boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

	}
	else {
#ifdef DEBUG
		cout << "Error creating connection: " << error.message() << endl;
#endif
		shutdown();					// Server restart
		startWaitingConnection();

	}

}

void HTTPServer::messageReceivedCb(const boost::system::error_code& error, std::size_t size) {

	if (!error) {

		std::istream is(&buff);				// Guarda toda la data recibida del buffer
		std::getline(is, request, {});		// como string
#ifdef DEBUG
		cout << size << " bytes received" << endl;
		cout << "Received: " << endl << request << endl << endl;
#endif

	}
	else {
#ifdef DEBUG
		cout << "Error receiving message: " << error.message() << endl;
#endif
		shutdown();					// Server restart
		startWaitingConnection();

	}

}

void HTTPServer::messageSentCb(const boost::system::error_code& error, std::size_t size) {

#ifdef DEBUG
	if (!error) {
		cout << "Response sent" << endl;
		cout << size << " bytes were sent" << endl;
	}
	else {
		cout << "Response failed: " << error.message() << endl;
	}
#endif

	shutdown();		// Close actual connection

	startWaitingConnection();	// Wait for the next connection
}


//
//string HTTPServer::getHTTPResponse(std::string data) {
//
//	string method = data.substr(0, data.find(" "));
//	string path = data.substr(data.find(" /")+2);
//	path = path.substr(0, path.find(" "));
//	
//	string host = data.substr(data.find("Host: ")+6);
//	host.replace(host.find("\r"), 1, " ");
//	host = host.substr(0, host.find(" "));
//
//	string file_content;
//
//	time_t now = time(0);
//	tm* nowTm = gmtime(&now);
//	char timeNow[256];
//	strftime(timeNow, 256, "%a, %d %b %Y %T GMT", nowTm);    //Ej: Tue, 04 Sep 2018 18:21:00 GMT
//
//	time_t exp = now + 30;
//	tm* expTm = gmtime(&exp);
//	char timeExp[256];
//	strftime(timeExp, 256, "%a, %d %b %Y %T GMT", expTm);
//	
//	string response;
//
//	if (method != "GET" || host != "127.0.0.1") {
//
//		response = string(	"HTTP/1.1 404 Not Found \r\n") +
//							"Date: " + timeNow + "\r\n" +
//							"Cache-Control: public, max-age=30 \r\n" +
//							"Expires: " + timeExp + "\r\n" +
//							"Content-Length: 0 \r\n" +
//							"Content-Type: text/html; charset=iso-8859-1 \r\n\r\n";;
//	}
//	else {
//
//		response = string(	"HTTP/1.1 200 OK \r\n") +
//							"Date: " + timeNow + "\r\n" +
//							"Location: 127.0.0.1/" + path + " \r\n" +
//							"Cache-Control: max-age=30 \r\n" +
//							"Expires: " + timeExp + "\r\n" +
//							"Content-Length: " + to_string(file_content.length()) + " \r\n" +
//							"Content-Type: text/html; charset=iso-8859-1 \r\n\r\n" +
//							file_content;
//	}
//
//	return response;
//}