#include "Action.h"

using namespace std;

Action::Action(ACTION_ID action) : id(action), desc(), params(){
	map<string, string> parameter;
	switch (action) {
	case SEND_TRANS:

		desc = "Send transaction";

		parameter["name"] = "public key";
		parameter["type"] = "string";
		params.push_back(parameter);

		parameter["name"] = "mount";
		parameter["type"] = "int";
		params.push_back(parameter);
		
		break;

	default:
		break;
	}
}