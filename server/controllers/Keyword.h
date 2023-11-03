#pragma once

#include "../utils/BWriter.h"
#include <drogon/HttpController.h>

using drogon::HttpController;
using drogon::HttpMethod;
using drogon::HttpRequestPtr, drogon::HttpResponsePtr;
using namespace utils;

namespace api::v1
{
    class Keyword : public drogon::HttpController<Keyword>
    {
    private:
        const BWriter writer = BWriter("keywords");

    public:
        METHOD_LIST_BEGIN
        METHOD_ADD(Keyword::getAll, "", HttpMethod::Get, HttpMethod::Options);
        METHOD_ADD(Keyword::include, "", HttpMethod::Post, HttpMethod::Options);
        METHOD_ADD(Keyword::deleteKeyword, "", HttpMethod::Delete, HttpMethod::Options);
        METHOD_LIST_END

        void getAll(const HttpRequestPtr& req,
            std::function<void(const HttpResponsePtr&)>&& callback);

        void include(const HttpRequestPtr& req,
            std::function<void(const HttpResponsePtr&)>&& callback);

        void deleteKeyword(const HttpRequestPtr& req,
            std::function<void(const HttpResponsePtr&)>&& callback);
    };
}
