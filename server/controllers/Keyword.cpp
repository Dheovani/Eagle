#include "Keyword.h"

using api::v1::Keyword;
using drogon::ContentType;
using drogon::HttpResponse;
using drogon::HttpStatusCode;

void Keyword::getAll(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
	const std::vector<Dao> keywords = writer.readAll();
	Json::Value ret;

	for (const Dao& keyword : keywords) {
		Json::Value value;
		value["id"] = keyword.id;
		value["path"] = keyword.data;

		ret["results"].append(value);
	}

	auto resp = HttpResponse::newHttpJsonResponse(ret);
	resp->setStatusCode(HttpStatusCode::k200OK);
	resp->setContentTypeCode(ContentType::CT_APPLICATION_JSON);
	callback(resp);
}

void Keyword::include(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
	Json::Value json = *req->getJsonObject();
	Dao keyword{ json["id"].asUInt() | writer.nextId(), json["keyword"].asString() };
	writer.write(keyword);

	auto resp = HttpResponse::newHttpResponse();
	resp->setStatusCode(HttpStatusCode::k200OK);
	resp->setContentTypeCode(ContentType::CT_APPLICATION_JSON);
	callback(resp);
}

void Keyword::deleteKeyword(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
	Json::Value json = *req->getJsonObject();
	const UINT id = json["id"].asUInt();
	writer.deleteRecord(id);

	auto resp = HttpResponse::newHttpResponse();
	resp->setStatusCode(HttpStatusCode::k200OK);
	resp->setContentTypeCode(ContentType::CT_APPLICATION_JSON);
	callback(resp);
}
