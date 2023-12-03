#include "Path.h"
#include <Windows.h>
#include <ShObjIdl.h>

using drogon::ContentType;
using drogon::HttpResponse;
using drogon::HttpStatusCode;
using namespace api::v1;

// Opens Window's dir selection dialog and return selected dir
inline std::wstring GetSelectedDirectory()
{
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr)) {
        IFileDialog* pFileDialog = NULL;
        std::wstring selectedDirectory;

        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFileDialog));

        if (SUCCEEDED(hr)) {
            DWORD dwOptions;
            pFileDialog->GetOptions(&dwOptions);
            pFileDialog->SetOptions(dwOptions | FOS_PICKFOLDERS | FOS_FORCEFILESYSTEM);

            hr = pFileDialog->Show(NULL);

            if (SUCCEEDED(hr)) {
                IShellItem* pItem;
                hr = pFileDialog->GetResult(&pItem);

                if (SUCCEEDED(hr)) {
                    PWSTR pszDir;
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszDir);

                    if (SUCCEEDED(hr)) {
                        selectedDirectory = pszDir;
                        CoTaskMemFree(pszDir);
                    }

                    pItem->Release();
                }
            }

            pFileDialog->Release();
        }

        CoUninitialize();

        return selectedDirectory;
    }

    return L"";
}

void Path::getAll(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
	const std::vector<Record> paths = writer.readAll();
	Json::Value ret;
    ret["results"] = Json::arrayValue;

	for (const Record& path : paths) {
		Json::Value value;
		value["id"] = path.id;
		value["path"] = path.data;

		ret["results"].append(value);
	}

	auto resp = HttpResponse::newHttpJsonResponse(ret);
	resp->setStatusCode(HttpStatusCode::k200OK);
	resp->setContentTypeCode(ContentType::CT_APPLICATION_JSON);
	callback(resp);
}

void Path::select(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
    std::wstring selectedPath = GetSelectedDirectory();

    if (!selectedPath.empty()) {
        size_t bufferSize = std::wcstombs(nullptr, selectedPath.c_str(), 0) + 1;
        char* narrowString = new char[bufferSize];

        std::wcstombs(narrowString, selectedPath.c_str(), bufferSize);
        Json::Value body;
        body["path"] = narrowString;

        auto jsonResp = HttpResponse::newHttpJsonResponse(body);
        jsonResp->setStatusCode(HttpStatusCode::k200OK);
        jsonResp->setContentTypeCode(ContentType::CT_APPLICATION_JSON);
        callback(jsonResp);
    }
    else {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(HttpStatusCode::k404NotFound);
        resp->setContentTypeCode(ContentType::CT_APPLICATION_JSON);
        callback(resp);
    }
}

void Path::include(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
	Json::Value json = *req->getJsonObject();

    std::string data = json["path"].asString();
    char buffer[MAX_PATH];
    strncpy_s(buffer, data.c_str(), sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    Record path{ json["id"].asUInt() | writer.nextId() };
    strcpy_s(path.data, buffer);
	writer.write(path);

	auto resp = HttpResponse::newHttpResponse();
	resp->setStatusCode(HttpStatusCode::k200OK);
	resp->setContentTypeCode(ContentType::CT_APPLICATION_JSON);
	callback(resp);
}

void Path::deletePath(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
	Json::Value json = *req->getJsonObject();
	const size_t id = json["id"].asUInt();
	writer.deleteRecord(id);

	auto resp = HttpResponse::newHttpResponse();
	resp->setStatusCode(HttpStatusCode::k200OK);
	resp->setContentTypeCode(ContentType::CT_APPLICATION_JSON);
	callback(resp);
}
