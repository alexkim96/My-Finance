#include "iostream"
#include "string"

#define CURL_STATICLIB
#include "curl/curl.h"

#ifdef _DEBUG
#pragma comment (lib, "curl/libcurl_a_debug.lib")
#pragma comment (lib, "curl/libcurl_a.lib")
#endif

static int writer(char *data, size_t size, size_t nmemb,
	std::string *writerData)
{
	if (writerData == NULL)
		return 0;

	writerData->append(data, size*nmemb);

	return size * nmemb;
}

int wmain(int argc, wchar_t *argv[]) {
	std::string content;
	
	curl_global_init(CURL_GLOBAL_ALL);
	CURL *curl = nullptr;
	curl = curl_easy_init();

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "http://free.currencyconverterapi.com/api/v5/convert?q=EUR_USD&compact=y");
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
		CURLcode code = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	std::cout << content;
	std::cin.get();
	return 0;
}
