#include "Search.h"
#include <sstream>

using api::v1::Search;
using drogon::ContentType;
using drogon::HttpResponse;
using drogon::HttpStatusCode;

std::vector<std::string> extractValues(const Json::Value &value, const std::string &key)
{
	std::string keyValue = value[key].asString();
	if (keyValue.find(';') == std::string::npos && !keyValue.empty())
		return std::vector<std::string>{ keyValue };

	std::vector<std::string> tokens;
	std::istringstream iss(keyValue);

	std::string token;
	while (std::getline(iss, token, ';')) {
		token.erase(std::remove_if(token.begin(), token.end(), ::isspace), token.end());
		tokens.push_back(token);
	}

	return tokens;
}

void Search::search(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
	Json::Value json = *req->getJsonObject();
	bool ignoreCase = json["ignoreCase"].asBool();
	bool subFolders = json["subFolders"].asBool();

	auto paths = extractValues(json["path"], "path");
	auto filters = extractValues(json["filter"], "filter");
	auto keywords = extractValues(json["keyword"], "keyword");

	utils::Tracker tracker;
	tracker.setPaths(paths);
	tracker.setFilters(filters);

	Json::Value results, files = tracker.search(keywords);

	for (const auto& key : files.getMemberNames())
		results["results"].append(files[key]);

	auto resp = HttpResponse::newHttpJsonResponse(results);
	resp->setStatusCode(HttpStatusCode::k200OK);
	resp->setContentTypeCode(ContentType::CT_APPLICATION_JSON);
	callback(resp);
}
