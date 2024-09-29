#pragma once

#include <optional>
#include <string>

#include <curl/curl.h>

class HttpsRequest
{
  public:
    HttpsRequest();
    HttpsRequest(const HttpsRequest&) = delete;
    HttpsRequest(HttpsRequest&& other) noexcept;

    ~HttpsRequest();

    HttpsRequest& operator=(const HttpsRequest&) = delete;
    HttpsRequest& operator=(HttpsRequest&& other) noexcept;

    void setUrl(const std::string& url) const;
    void setUrl(const char* url) const;

    void setContentType(const std::string& type) const;
    void setContentType(const char* type) const;

    std::optional<std::string> operator()() const;

  private:
    CURL* mCurl = nullptr;
    std::string mReadBuffer;
};
