#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <curl/curl.h>

class HTTPClient{

public:

HTTPClient();
int clientSetUp(std::string url);
int perform();
void cleanUp();

private:
	CURL* curl;
	CURLM* multiHandle;
	std::string response;
	bool requesting;
};

