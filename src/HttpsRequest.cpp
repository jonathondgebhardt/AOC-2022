//
// Created by jon on 10/29/23.
//

#include "HttpsRequest.h"

HttpsRequest::HttpsRequest()
{
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // TODO: Could probably make sure we don't already have that file...
    mCurl = curl_easy_init();

    // Disable progress bar
    curl_easy_setopt(mCurl, CURLOPT_NOPROGRESS, 1L);

    // Don't do any custom data parsing
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
    list = curl_slist_append(list, "Content-Type: " + type);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
}

void HttpsRequest::setFile(const std::string& file)
{
    setFile(file.c_str());
}

void HttpsRequest::setFile(const char* file)
{
    curl_easy_setopt(mCurl, CURLOPT_WRITEDATA, file);
}

bool HttpsRequest::operator()() const
{
    const auto inputPath = config::GetInputFilePath();
    // TODO: Read this from the filesystem, don't hard-code
    const auto sessionFile = inputPath + "/.adventofcode.session";
    const auto session = util::Parse(sessionFile).front();
    //            const auto cookie = "session=" + session;
    //            curl_easy_setopt(mCurl, CURLOPT_COOKIE, cookie.c_str());

    return curl_easy_perform(mCurl) == CURLE_OK;
}


