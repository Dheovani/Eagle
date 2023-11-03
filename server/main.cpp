#include <drogon/drogon.h>

int main() {
    drogon::app().addListener("localhost", 8080);
    drogon::app().registerPostHandlingAdvice(
        [](const drogon::HttpRequestPtr& req, const drogon::HttpResponsePtr& resp) {
            resp->addHeader("Access-Control-Allow-Origin", "*");
        }
    );
    drogon::app().run();
    return 0;
}
