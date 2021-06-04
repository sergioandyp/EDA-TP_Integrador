#include "HTTPClient.h"



HTTPClient::HTTPClient() : curl(), multiHandle(), requesting(0)
{
}

int HTTPClient::clientSetUp(std::string url) {
	curl = curl_easy_init();
	multiHandle = curl_multi_init();

	if ((curl == NULL) || (multiHandle == NULL))
		return 0;

	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTP | CURLPROTO_HTTPS);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, myCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
	response = "";
	curl_multi_add_handle(multiHandle, curl);
}


int HTTPClient::perform() {
	requesting = true;
	if (curl_multi_perform(multiHandle, &requesting) != CURLM_OK) {
		return 0;

	this.cleanUp();
	return 1;
}

void TwitterAPI::cleanUp() {
	curl_multi_remove_handle(multiHandle, curl);
	curl_easy_cleanup(curl);
	curl_multi_cleanup(multiHandle);
	requesting = false;
}


//Concatena lo recibido en content a s
static size_t myCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	size_t realsize = size * nmemb;
	char* data = (char*)contents;
	string* s = (string*)userp;
	s->append(data, realsize);
	return realsize;						//recordar siempre devolver realsize
}

void TwitterAPI::cleanUp() {}