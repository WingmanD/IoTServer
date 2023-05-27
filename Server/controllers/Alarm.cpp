#include "Alarm.h"
#include "../Util.h"
#include <fmt/format.h>
#include <drogon/HttpClient.h>

void Alarm::Clear(const drogon::HttpRequestPtr& req, std::function<void(const drogon::HttpResponsePtr&)>&& callback)
{
    auto cookies = req->getCookies();
    if (!cookies.contains("jwt") || !cookies.contains("username"))
    {
        const auto resp = drogon::HttpResponse::newRedirectionResponse("/auth/login");
        callback(resp);
        return;
    }

    const std::string token = cookies["jwt"];
    const std::string alarmId = req->getParameter("id");
    
    const drogon::HttpStatusCode ackResponseCode = AcknowledgeAlarm(token, alarmId);
    if (ackResponseCode != drogon::HttpStatusCode::k200OK)
    {
        const auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(ackResponseCode);
        resp->setBody("Failed to acknowledge alarm!");
        callback(resp);

        return;
    }

    const drogon::HttpStatusCode clearResponseCode = ClearAlarm(token, alarmId);
    if (clearResponseCode != drogon::HttpStatusCode::k200OK)
    {
        const auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(clearResponseCode);
        resp->setBody("Failed to clear alarm!");
        callback(resp);

        return;
    }

    const auto resp = drogon::HttpResponse::newHttpResponse();
    resp->setStatusCode(drogon::HttpStatusCode::k200OK);
    callback(resp);
}

drogon::HttpStatusCode Alarm::AcknowledgeAlarm(const std::string& token, const std::string& alarmId) const
{
    if (token.empty())
    {
        return drogon::HttpStatusCode::k401Unauthorized;
    }

    const drogon::HttpRequestPtr request = drogon::HttpRequest::newHttpRequest();
    request->setMethod(drogon::HttpMethod::Post);
    request->setPath(fmt::format("/api/alarm/{}/ack", alarmId));
    request->addHeader("X-Authorization", "Bearer " + token);

    const auto client = drogon::HttpClient::newHttpClient(Util::ThingsBoardHost);
    const auto respPair = client->sendRequest(request);
    const auto& resp = respPair.second;

    return resp->statusCode();
}

drogon::HttpStatusCode Alarm::ClearAlarm(const std::string& token, const std::string& alarmId) const
{
    if (token.empty())
    {
        return drogon::HttpStatusCode::k401Unauthorized;
    }

    const drogon::HttpRequestPtr request = drogon::HttpRequest::newHttpRequest();
    request->setMethod(drogon::HttpMethod::Post);
    request->setPath(fmt::format("/api/alarm/{}/clear", alarmId));
    request->addHeader("X-Authorization", "Bearer " + token);

    const auto client = drogon::HttpClient::newHttpClient(Util::ThingsBoardHost);
    const auto respPair = client->sendRequest(request);
    const auto& resp = respPair.second;

    return resp->statusCode();
}
