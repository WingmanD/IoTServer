#include <drogon/drogon.h>

int main(int argc, char* argv[])
{
    drogon::app().loadConfigFile("bin/config.json");

    drogon::HttpAppFramework::instance()
        .registerHandler("/",
                         [=](const drogon::HttpRequestPtr& req,
                             std::function<void (const drogon::HttpResponsePtr&)>&& callback)
                         {
                             // todo redirect to dashboard controller which will handle data and views
                             // instead of having this in main

                             auto params = req->getParameters();
                             auto cookies = req->getCookies();

                             drogon::HttpViewData data;
                             data.insert("params", params);

                             if (cookies.contains("user"))
                             {
                                 const std::string userData = drogon::utils::base64Decode(cookies.at("user"));

                                 Json::Value user;
                                 Json::CharReaderBuilder builder;
                                 std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
                                 std::string errors;

                                 if (!userData.empty() && cookies.contains("session"))
                                 {
                                     const bool parsingSuccessful = reader->parse(
                                         userData.c_str(), userData.c_str() + userData.size(), &user,
                                         &errors);
                                     if (parsingSuccessful)
                                     {
                                         data.insert("user", user);
                                     }
                                     else
                                     {
                                         std::cout << "Failed to parse JSON" << std::endl;
                                         std::cout << errors << std::endl;
                                     }
                                 }
                             }
                             
                             const auto resp = drogon::HttpResponse::newHttpViewResponse("home.csp", data);
                             callback(resp);
                         });
    
    drogon::app().run();
    
    return 0;
}
