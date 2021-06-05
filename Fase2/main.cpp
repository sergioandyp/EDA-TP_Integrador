#include "mygui.h"
#include "HTTPServer.h"
#include <iostream>

using namespace std;

void testServer();

int main() {

	Gui gui;

	gui.setup();		// Necesario para inicializar la GUI

	while (gui.functions()) { // Esperamos hasta que se cierre la GUI
		//EDACoinNetwork.updateNodes();
	}

	testServer();

	return 0;
}

void testServer() {
	HTTPServer server(8530);
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