#include "Filter.h"

using api::v1::Filter;
using drogon::ContentType;
using drogon::HttpResponse;
using drogon::HttpStatusCode;

void Filter::getAll(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
	const std::vector<Dao> filters = writer.readAll();
	Json::Value ret;

	for (const Dao& filter : filters) {
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
	Dao filter{ json["id"].asUInt() | writer.nextId(), json["filter"].asString() };
	writer.write(filter);

	auto resp = HttpResponse::newHttpResponse();
	resp->setStatusCode(HttpStatusCode::k200OK);
	resp->setContentTypeCode(ContentType::CT_APPLICATION_JSON);
	callback(resp);
}

void Filter::deleteFilter(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
	Json::Value json = *req->getJsonObject();
	const UINT id = json["id"].asUInt();
	writer.deleteRecord(id);

	auto resp = HttpResponse::newHttpResponse();
	resp->setStatusCode(HttpStatusCode::k200OK);
	resp->setContentTypeCode(ContentType::CT_APPLICATION_JSON);
	callback(resp);
}
