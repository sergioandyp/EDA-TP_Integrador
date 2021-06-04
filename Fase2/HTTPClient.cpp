#include "HTTPClient.h"

static size_t writeCb(void* contents, size_t size, size_t nmemb, void* userp);
static size_t readCb(char* ptr, size_t size, size_t nmemb, void* userdata);


HTTPClient::HTTPClient() : curl(), multiHandle(), requesting(0), request(0)
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
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_READDATA, &request);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCb);
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
    response = "";
    curl_multi_add_handle(multiHandle, curl);
}


int HTTPClient::perform() {
    requesting = true;
    if (curl_multi_perform(multiHandle, &requesting) != CURLM_OK) {
        return 0;

    this->cleanUp();
    return 1;
}

void HTTPClient::cleanUp() {
    curl_multi_remove_handle(multiHandle, curl);
    curl_easy_cleanup(curl);
    curl_multi_cleanup(multiHandle);
    requesting = false;
}


//Concatena lo recibido en content a s
static size_t writeCb(void* contents, size_t size, size_t nmemb, void* userp)
{
    size_t realsize = size * nmemb;
    char* data = (char*)contents;
    string* s = (string*)userp;
    s->append(data, realsize);
    return realsize;                        //recordar siempre devolver realsize
}

static size_t readCb(char* ptr, size_t size, size_t nmemb, void* userdata)
{
    FILE* readhere = (FILE*)userdata;
    curl_off_t nread;

    size_t retcode = fread(ptr, size, nmemb, readhere);

    nread = (curl_off_t)retcode;

    return retcode;
}