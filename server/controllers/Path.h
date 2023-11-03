#pragma once

#include "../utils/BWriter.h"
#include <drogon/HttpController.h>

using drogon::HttpController;
using drogon::HttpMethod;
using drogon::HttpRequestPtr, drogon::HttpResponsePtr;
using namespace utils;

namespace api::v1
{
	class Path : public HttpController<Path>
	{
	private:
		const BWriter writer = BWriter("paths");

	public:
		METHOD_LIST_BEGIN
		METHOD_ADD(Path::getAll, "", HttpMethod::Get, HttpMethod::Options);
		METHOD_ADD(Path::select, "/select", HttpMethod::Get, HttpMethod::Options);
		METHOD_ADD(Path::include, "", HttpMethod::Post, HttpMethod::Options);
		METHOD_ADD(Path::deletePath, "", HttpMethod::Delete, HttpMethod::Options);
		METHOD_LIST_END

		void getAll(const HttpRequestPtr& req,
			std::function<void(const HttpResponsePtr&)>&& callback);

		void select(const HttpRequestPtr& req,
			std::function<void(const HttpResponsePtr&)>&& callback);

		void include(const HttpRequestPtr& req,
			std::function<void(const HttpResponsePtr&)>&& callback);

		void deletePath(const HttpRequestPtr& req,
			std::function<void(const HttpResponsePtr&)>&& callback);
	};
}
