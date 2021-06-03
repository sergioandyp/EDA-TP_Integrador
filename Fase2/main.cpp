#include "mygui.h"

using namespace std;

int main() {

	Gui gui;

	gui.setup();		// Necesario para inicializar la GUI

	while (gui.functions()) { // Esperamos hasta que se cierre la GUI
		//EDACoinNetwork.updateNodes();
	}
	return 0;
}