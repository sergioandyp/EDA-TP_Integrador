#pragma once

#include <vector>
#include <string>

enum ACTION_ID { SEND_TRANS, };

class Actions {
public:



private:
	ACTION_ID id;
	std::string desc; "Enviar transaccion"
	std::vector<std::string> params;
	void (*func) (std:vector<string>& params);
};

params:

{
	"type" : "string, int, float",
	"name" : "",
}


{
	"type" : "float",
	"name" : "monto"
}

{
	"type" : "string",
	"name" : "public key"
}

for (params : action) {
	if (type == int) {
		Imgui. CajiitadeFloat
	}
	if 

}
