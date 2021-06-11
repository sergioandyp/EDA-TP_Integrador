#include "mygui.h"
#include "EDACoinNetwork.h"
#include "HTTPServer.h"
#include <iostream>

using namespace std;

void testServer();
void testClient();

int main() {

	EDACoinNetwork network;

	Gui gui(network);

	gui.setup();		// Necesario para inicializar la GUI

	while (gui.functions()) { // Esperamos hasta que se cierre la GUI
		network.updateNodes();
	}

	//testServer();
	//testClient();

	return 0;
}

void testServer() {
	HTTPServer server(8531);
	if (!server.start()) {
		cout << "No se pudo iniciar el server" << endl;
	}

	while (true) {
		while (!server.isRequest()) {
			server.run();
		}

		cout << "Respuesta recibida: " << server.getRequest() << endl;

		server.sendResponse("Hola, gracias por conectarte\r\n\r\n");

	}

}


#include "HTTPClient.h"
void testClient() {
	HTTPClient clientecito(32123);
	clientecito.getRequest("localhost", 80);
	while (clientecito.isBusy())
	{
		clientecito.clientRun();
		cout << clientecito.isBusy() << endl;
	}
	std::string s;
	std::cin >> s;
	cout << "RTA: " << clientecito.getContent()<<endl;

}