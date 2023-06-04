#include <drogon/drogon.h>

int main(int argc, char* argv[])
{
    drogon::app().loadConfigFile("config.json");

    drogon::HttpAppFramework::instance()
        .registerHandler("/",
                         [=](const drogon::HttpRequestPtr& req,
                             std::function<void (const drogon::HttpResponsePtr&)>&& callback)
                         {
                             const auto resp = drogon::HttpResponse::newRedirectionResponse("/dashboard/");
                             callback(resp);
                         });

    drogon::app().run();
    return 0;
}
