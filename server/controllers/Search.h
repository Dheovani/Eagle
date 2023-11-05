#pragma once

#include <drogon/HttpController.h>
#include "../utils/Tracker.h";

using drogon::HttpController;
using drogon::HttpMethod;
using drogon::HttpRequestPtr, drogon::HttpResponsePtr;

namespace api::v1
{
	class Search : public HttpController<Search>
	{
	public:
		METHOD_LIST_BEGIN
		METHOD_ADD(Search::search, "/find", HttpMethod::Get, HttpMethod::Post, HttpMethod::Options);
		METHOD_LIST_END

		void search(const HttpRequestPtr& req,
			std::function<void(const HttpResponsePtr&)>&& callback);
	};
}
