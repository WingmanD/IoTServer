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

    const Json::Value telemetry = Util::GetDeviceTelemetry(cookies["jwt"],
                                                           "564a8980-f58e-11ed-993d-8d74c2abdddd",
                                                           "temperature,humidity");
    
    data.insert("username", cookies["username"]);
    data.insert("telemetry", telemetry);
    
    const auto resp = drogon::HttpResponse::newHttpViewResponse("home.csp", data);
    callback(resp);
}
