#include "Dashboard.h"
#include "../Util.h"

void Dashboard::Home(const drogon::HttpRequestPtr& req, std::function<void(const drogon::HttpResponsePtr&)>&& callback)
{
    drogon::HttpViewData data;
    
    auto cookies = req->getCookies();
    if (!cookies.contains("jwt") || !cookies.contains("username"))
    {
        const auto resp = drogon::HttpResponse::newRedirectionResponse("/auth/login");
        callback(resp);
        return;
    }

    data.insert("username", cookies["username"]);
    
    const auto resp = drogon::HttpResponse::newHttpViewResponse("home.csp", data);
    callback(resp);
}
