//
// Created by jon on 10/29/23.
//

#include "HttpsRequest.hpp"
#include "InputDirectoryConfig.hpp"
#include "Utilities.ipp"

namespace
{
    std::string GetCookie()
    {
        const auto sessionFile = config::GetInputFilePath() + "/.adventofcode.session";
        if(const auto sessions = util::Parse(sessionFile); !sessions.empty())
        {
            return "session=" + sessions.front();
        }

        return {};
    }
}

HttpsRequest::HttpsRequest()
{
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // TODO: Could probably make sure we don't already have that file...
    mCurl = curl_easy_init();

    // Disable progress bar
    curl_easy_setopt(mCurl, CURLOPT_NOPROGRESS, 1L);

    // Don't do any custom data parsing
    // TODO: Perhaps I could push content into a vector instead of writing to a file and then
    // reading.
    curl_easy_setopt(mCurl, CURLOPT_WRITEFUNCTION, nullptr);
}

HttpsRequest::~HttpsRequest()
{
    if(mCurl)
    {
        curl_easy_cleanup(mCurl);
    }

    curl_global_cleanup();
}

void HttpsRequest::setUrl(const std::string& url)
{
    setUrl(url.c_str());
}

void HttpsRequest::setUrl(const char* url)
{
    curl_easy_setopt(mCurl, CURLOPT_URL, url);
}

void HttpsRequest::setContentType(const std::string& type)
{
    setContentType(type.c_str());
}

void HttpsRequest::setContentType(const char* type)
{
    curl_slist* list = nullptr;
    const std::string content = std::string("Content-Type: ") + type;
    list = curl_slist_append(list, content.c_str());
    curl_easy_setopt(mCurl, CURLOPT_HTTPHEADER, list);
}

std::vector<std::string> HttpsRequest::operator()() const
{
    if(!mCurl)
    {
        return {};
    }

    const auto cookie = GetCookie();
    if(cookie.empty())
    {
        std::cerr << "Could not load session file\n";
    }

    curl_easy_setopt(mCurl, CURLOPT_COOKIE, cookie.c_str());

    // TODO: Compiler complains about usage of std::tmpnam. Use std::tmpfile instead.
    std::string temporaryFile = std::tmpnam(nullptr);
    if(auto file = fopen(temporaryFile.c_str(), "w"))
    {
        curl_easy_setopt(mCurl, CURLOPT_WRITEDATA, file);

        if(curl_easy_perform(mCurl) != CURLE_OK)
        {
            std::cerr << "Could not perform HTTPS request\n";
        }

        fclose(file);

        return util::Parse(temporaryFile);
    }

    return {};
}
