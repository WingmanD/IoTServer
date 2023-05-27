#include "Util.h"

#include <iostream>
#include <drogon/HttpClient.h>
#include <json/reader.h>
#include <json/value.h>
#include <chrono>
#include <fmt/format.h>

std::string Util::ThingsboardHost = "http://161.53.19.19:45080";

Json::Value Util::ParseJson(const std::string& text)
{
    Json::Value json;

    Json::CharReaderBuilder builder;
    std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    std::string errors;

    if (!reader->parse(text.c_str(), text.c_str() + text.length(), &json, &errors))
    {
        std::cerr << "Failed to parse JSON" << std::endl;
        std::cerr << errors << std::endl;
    }

    return json;
}

std::string Util::Login(const std::string& username, const std::string& password)
{
    const auto client = drogon::HttpClient::newHttpClient(ThingsboardHost);

    Json::Value requestJson;
    requestJson["username"] = username;
    requestJson["password"] = password;

    const drogon::HttpRequestPtr loginRequest = drogon::HttpRequest::newHttpJsonRequest(requestJson);
    loginRequest->setMethod(drogon::HttpMethod::Post);
    loginRequest->setPath("/api/auth/login");

    const auto loginRespPair = client->sendRequest(loginRequest);
    const auto loginReqResult = loginRespPair.first;
    const auto& loginResponse = loginRespPair.second;

    if (loginReqResult != drogon::ReqResult::Ok)
    {
        return "";
    }

    const Json::Value loginResponseJson = *loginResponse->getJsonObject();

    return loginResponseJson["token"].asString();
}

Json::Value Util::GetDeviceTelemetry(const std::string& token, const std::string& deviceId, const std::string& keys)
{
    if (token.empty())
    {
        return {};
    }

    constexpr int64_t startTs = 0;
    constexpr int limit = 10;

    const auto now = std::chrono::system_clock::now();
    const auto nowMs = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    const auto epoch = nowMs.time_since_epoch();
    const auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
    const auto endTs = value.count();

    const drogon::HttpRequestPtr telemetryRequest = drogon::HttpRequest::newHttpRequest();
    telemetryRequest->setMethod(drogon::HttpMethod::Get);
    telemetryRequest->setPath(fmt::format("/api/plugins/telemetry/DEVICE/{}/values/timeseries?keys={}&startTs={}&endTs={}&limit={}&agg=NONE", deviceId, keys, startTs, endTs, limit));
    telemetryRequest->addHeader("X-Authorization", "Bearer " + token);

    const auto client = drogon::HttpClient::newHttpClient(ThingsboardHost);
    const auto respPair = client->sendRequest(telemetryRequest);
    const auto& resp = respPair.second;

    return *resp->getJsonObject();
}
