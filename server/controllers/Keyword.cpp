#include "Keyword.h"

using api::v1::Keyword;
using drogon::ContentType;
using drogon::HttpResponse;
using drogon::HttpStatusCode;

void Keyword::getAll(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
	const std::vector<Record> keywords = writer.readAll();
	Json::Value ret;

	for (const Record& keyword : keywords) {
		Json::Value value;
		value["id"] = keyword.id;
		value["keyword"] = keyword.data;

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

	std::string data = json["keyword"].asString();
	char buffer[MAX_PATH];
	strncpy_s(buffer, data.c_str(), sizeof(buffer));
	buffer[sizeof(buffer) - 1] = '\0';

	Record keyword{ json["id"].asUInt() | writer.nextId() };
	strcpy_s(keyword.data, buffer);
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
