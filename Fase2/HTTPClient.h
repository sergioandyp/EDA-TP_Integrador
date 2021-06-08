#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <curl/curl.h>

class HTTPClient {

public:

    HTTPClient(unsigned int port);
    int clientRun();
    std::string getContent();
    int postRequest(std::string url, std::string msg, unsigned int port);
    int getRequest(std::string url, unsigned int port);
    int isBusy();
    unsigned int getPort();


private:
    CURL* handle;
    CURLM* multiHandle;
    std::string content;
    std::string header;
    std::string request;
    int busy; // Tiene que ser int para poder usarla en curl.
    unsigned int port;
    
    
    void clientCleanUp();
};