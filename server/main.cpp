#include <drogon/drogon.h>

#define _CRT_SECURE_NO_WARNINGS

int main(int argv, char** argc)
{
    drogon::app()
        .addListener("localhost", 8080)
        .registerPostHandlingAdvice(
            [](const drogon::HttpRequestPtr& req, const drogon::HttpResponsePtr& resp) {
                resp->addHeader("Access-Control-Allow-Origin", "*");
            })
        .run();

    return 0;
}
