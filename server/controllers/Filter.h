#pragma once

#include "../utils/BWriter.h"
#include <drogon/HttpController.h>

using drogon::HttpController;
using drogon::HttpMethod;
using drogon::HttpRequestPtr, drogon::HttpResponsePtr;
using namespace utils;

namespace api::v1
{
    class Filter : public drogon::HttpController<Filter>
    {
    private:
        const BWriter writer = BWriter("filters");

    public:
		METHOD_LIST_BEGIN
		METHOD_ADD(Filter::getAll, "", HttpMethod::Get, HttpMethod::Options);
		METHOD_ADD(Filter::include, "", HttpMethod::Post, HttpMethod::Options);
		METHOD_ADD(Filter::deleteFilter, "", HttpMethod::Delete, HttpMethod::Options);
		METHOD_LIST_END

		void getAll(const HttpRequestPtr& req,
			std::function<void(const HttpResponsePtr&)>&& callback);

		void include(const HttpRequestPtr& req,
			std::function<void(const HttpResponsePtr&)>&& callback);

		void deleteFilter(const HttpRequestPtr& req,
			std::function<void(const HttpResponsePtr&)>&& callback);
    };
}
