#pragma once

#include <curl/curl.h>
#include <string>
#include <vector>

class HttpsRequest
{
  public:
    HttpsRequest();
    ~HttpsRequest();

    HttpsRequest(const HttpsRequest&) = delete;
    HttpsRequest& operator=(const HttpsRequest&) = delete;

    void setUrl(const std::string& url);
    void setUrl(const char* url);

    void setContentType(const std::string& type);
    void setContentType(const char* type);

    std::vector<std::string> operator()() const;

  private:
    CURL* mCurl = nullptr;
};
