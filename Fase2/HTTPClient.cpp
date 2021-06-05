#include "HTTPClient.h"
#include <iostream>

static size_t getData(char* contents, size_t size, size_t nmemb, void* userp);
static size_t getHeader(char* buff, size_t itemsize, size_t nitems, void* header);

HTTPClient::HTTPClient(unsigned int port) : handle(), multiHandle()
{
    content = "";
    request = "";
    header = "";
    busy = 0;
    this->port = port;
}

int HTTPClient::postRequest(std::string url, std::string msg, unsigned int port) {
    request = msg;
    handle = curl_easy_init();
    multiHandle = curl_multi_init();

    if ((handle == NULL) || (multiHandle == NULL))
        return 0;

    curl_easy_setopt(handle, CURLOPT_LOCALPORT, this->port);
    curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(handle, CURLOPT_PORT, (long)port);
    curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L); //Follow HTTP redirects
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, getData);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &content);
    curl_easy_setopt(handle, CURLOPT_PROTOCOLS, CURLPROTO_HTTP | CURLPROTO_HTTPS);
    curl_easy_setopt(handle, CURLOPT_POSTFIELDS, msg.c_str());
    curl_easy_setopt(handle, CURLOPT_POSTFIELDSIZE, (long)(msg.length()));
    curl_multi_add_handle(multiHandle, handle);
    curl_multi_perform(multiHandle, &busy);
    return 1;
}

int HTTPClient::getRequest(std::string url, unsigned int port) {
    content = "";
    header = "";
    handle = curl_easy_init();
    multiHandle = curl_multi_init();

    if ((handle == NULL) || (multiHandle == NULL))
        return 0;

    curl_easy_setopt(handle, CURLOPT_LOCALPORT, this->port);
    curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(handle, CURLOPT_PORT, (long) port);
    curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(handle, CURLOPT_PROTOCOLS, CURLPROTO_HTTP | CURLPROTO_HTTPS);
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, getData);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &content);
    curl_easy_setopt(handle, CURLOPT_HEADERFUNCTION, getHeader);
    curl_easy_setopt(handle, CURLOPT_HEADERDATA, &header);
    curl_multi_add_handle(multiHandle, handle);
    curl_multi_perform(multiHandle, &busy);
    return 1;
}

// Devuelve 0 si no se termino la comunicación
// Devuelve 1 si se termino la comunicación
int HTTPClient::clientRun() {
    curl_multi_perform(multiHandle, &busy);

    if (!busy)
    {
        this->clientCleanUp();
        return 1;
    }
    return 0;
}

void HTTPClient::clientCleanUp(){
    curl_multi_remove_handle(multiHandle, handle);
    curl_multi_cleanup(multiHandle);
    busy = 0;
}

std::string HTTPClient::getContent() {
    return content;
}

int HTTPClient::isBusy() {
    return busy;
}

static size_t getData(char* contents, size_t size, size_t nmemb, void* userp)
{
    size_t dataSize = size * nmemb;
    // Agregamos al dato miembro Data, el content recibido.
    ((std::string*)userp)->append(contents, dataSize);
    return dataSize;
}

static size_t getHeader(char* buff, size_t itemsize, size_t nitems, void* header)
{
    size_t headerSize = itemsize * nitems;
    // Agregamos al dato miembro Header, el header recibido.
    ((std::string*)header)->append(buff, headerSize);
    return headerSize;
}