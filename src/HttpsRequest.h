//
// Created by jon on 10/29/23.
//

#ifndef AOC_2022_HTTPSREQUEST_H
#define AOC_2022_HTTPSREQUEST_H

#include <curl/curl.h>
#include <string>

class HttpsRequest
{
  public:
    HttpsRequest();
    ~HttpsRequest();

    void setUrl(const std::string& url);
    void setUrl(const char* url);

    void setContentType(const std::string& type);
    void setContentType(const char* type);

    void setFile(const std::string& file);
    void setFile(const char* file);

    bool operator()() const;

  private:
    CURL* mCurl = nullptr;
};

#endif // AOC_2022_HTTPSREQUEST_H
