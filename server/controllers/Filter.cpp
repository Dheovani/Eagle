#include "Filter.h"

using api::v1::Filter;
using drogon::ContentType;
using drogon::HttpResponse;
using drogon::HttpStatusCode;

void Filter::getAll(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
	const std::vector<Record> filters = writer.readAll();
	Json::Value ret;
	ret["results"] = Json::arrayValue;

	for (const Record& filter : filters) {
		Json::Value value;
		value["id"] = filter.id;
		value["filter"] = filter.data;

		ret["results"].append(value);
	}

	auto resp = HttpResponse::newHttpJsonResponse(ret);
	resp->setStatusCode(HttpStatusCode::k200OK);
	resp->setContentTypeCode(ContentType::CT_APPLICATION_JSON);
	callback(resp);
}

void Filter::include(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
	Json::Value json = *req->getJsonObject();

	std::string data = json["filter"].asString();
	char buffer[MAX_PATH];
	strncpy_s(buffer, data.c_str(), sizeof(buffer));
	buffer[sizeof(buffer) - 1] = '\0';

	Record filter{ json["id"].asUInt() | writer.nextId() };
	strcpy_s(filter.data, buffer);
	writer.write(filter);

	auto resp = HttpResponse::newHttpResponse();
	resp->setStatusCode(HttpStatusCode::k200OK);
	resp->setContentTypeCode(ContentType::CT_APPLICATION_JSON);
	callback(resp);
}

void Filter::deleteFilter(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
	Json::Value json = *req->getJsonObject();
	const size_t id = json["id"].asUInt();
	writer.deleteRecord(id);

	auto resp = HttpResponse::newHttpResponse();
	resp->setStatusCode(HttpStatusCode::k200OK);
	resp->setContentTypeCode(ContentType::CT_APPLICATION_JSON);
	callback(resp);
}
