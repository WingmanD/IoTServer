#include "Util.h"

#include <iostream>
#include <drogon/HttpClient.h>
#include <json/reader.h>
#include <json/value.h>
#include <chrono>
#include <fmt/format.h>

std::string Util::ThingsBoardHost = "http://161.53.19.19:45080";
std::string Util::SensorDeviceId = "564a8980-f58e-11ed-993d-8d74c2abdddd";
std::string Util::VirtualDeviceAccessToken = "0fPIFyn0CVshpSEzlfDn";
int Util::RequiredTemperatureForTurningOff = 60;

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

std::expected<std::string, drogon::HttpStatusCode> Util::Login(const std::string& username, const std::string& password)
{
    if (username.empty() || password.empty())
    {
        return std::unexpected(drogon::HttpStatusCode::k400BadRequest);
    }
    
    const auto client = drogon::HttpClient::newHttpClient(ThingsBoardHost);

    Json::Value requestJson;
    requestJson["username"] = username;
    requestJson["password"] = password;

    const drogon::HttpRequestPtr request = drogon::HttpRequest::newHttpJsonRequest(requestJson);
    request->setMethod(drogon::HttpMethod::Post);
    request->setPath("/api/auth/login");

    const auto respPair = client->sendRequest(request);
    const auto reqResult = respPair.first;
    const auto& resp = respPair.second;

    if (reqResult != drogon::ReqResult::Ok)
    {
        return std::unexpected(resp->getStatusCode());
    }

    const Json::Value loginResponseJson = resp->getJsonObject() ? *resp->getJsonObject() : Json::Value();

    return loginResponseJson["token"].asString();
}

Json::Value Util::GetDeviceTelemetry(const std::string& token, const std::string& deviceId, const std::string& keys)
{
    if (token.empty() || deviceId.empty())
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

    const drogon::HttpRequestPtr request = drogon::HttpRequest::newHttpRequest();
    request->setMethod(drogon::HttpMethod::Get);
    request->setPath(fmt::format("/api/plugins/telemetry/DEVICE/{}/values/timeseries?keys={}&startTs={}&endTs={}&limit={}&agg=NONE", deviceId, keys, startTs, endTs, limit));
    request->addHeader("X-Authorization", "Bearer " + token);

    const auto client = drogon::HttpClient::newHttpClient(ThingsBoardHost);
    const auto respPair = client->sendRequest(request);
    const auto& resp = respPair.second;

    return resp->getJsonObject() ? *resp->getJsonObject() : Json::Value();
}

Json::Value Util::GetDeviceCurrentTelemetry(const std::string& token, const std::string& deviceId,const std::string& keys)
{
    if (token.empty() || deviceId.empty())
    {
        return {};
    }

    const drogon::HttpRequestPtr request = drogon::HttpRequest::newHttpRequest();
    request->setMethod(drogon::HttpMethod::Get);
    request->setPath(fmt::format("/api/plugins/telemetry/DEVICE/{}/values/timeseries?keys={}", deviceId, keys));
    request->addHeader("X-Authorization", "Bearer " + token);

    const auto client = drogon::HttpClient::newHttpClient(ThingsBoardHost);
    const auto respPair = client->sendRequest(request);
    const auto& resp = respPair.second;

    return resp->getJsonObject() ? *resp->getJsonObject() : Json::Value();
}

Json::Value Util::GetDeviceAlarms(const std::string& token, const std::string& deviceId)
{
    if (token.empty() || deviceId.empty())
    {
        return {};
    }

    constexpr int pageSize = 10;
    constexpr int page = 0;
    
    const drogon::HttpRequestPtr request = drogon::HttpRequest::newHttpRequest();
    request->setMethod(drogon::HttpMethod::Get);
    request->setPath(fmt::format("/api/alarm/DEVICE/{}?pageSize={}&page={}", deviceId, pageSize, page));
    request->addHeader("X-Authorization", "Bearer " + token);

    const auto client = drogon::HttpClient::newHttpClient(ThingsBoardHost);
    const auto respPair = client->sendRequest(request);
    const auto& resp = respPair.second;

    return resp->getJsonObject() ? *resp->getJsonObject() : Json::Value();
}

Json::Value Util::GetDeviceAttributes(const std::string& token, const std::string& deviceAccessToken, const std::string& attributes)
{
    if (token.empty() || deviceAccessToken.empty() || attributes.empty())
    {
        return {};
    }
    
    const drogon::HttpRequestPtr request = drogon::HttpRequest::newHttpRequest();
    request->setMethod(drogon::HttpMethod::Get);
    request->setPath(fmt::format("/api/v1/{}/attributes?clientKeys={}&sharedKeys=-", deviceAccessToken, attributes));
    request->addHeader("X-Authorization", "Bearer " + token);

    const auto client = drogon::HttpClient::newHttpClient(ThingsBoardHost);
    const auto respPair = client->sendRequest(request);
    const auto& resp = respPair.second;

    return resp->getJsonObject() ? *resp->getJsonObject() : Json::Value();
}

drogon::HttpStatusCode Util::PostDeviceAttributes(const std::string& token, const std::string& deviceAccessToken, const Json::Value& attributes)
{
    if (token.empty() || deviceAccessToken.empty() || attributes.empty())
    {
        return drogon::HttpStatusCode::k400BadRequest;
    }

    const drogon::HttpRequestPtr request = drogon::HttpRequest::newHttpRequest();
    request->setMethod(drogon::HttpMethod::Post);
    request->setPath(fmt::format("/api/v1/{}/attributes", deviceAccessToken));
    request->setBody(attributes.toStyledString());
    request->addHeader("X-Authorization", "Bearer " + token);

    const auto client = drogon::HttpClient::newHttpClient(ThingsBoardHost);
    const auto respPair = client->sendRequest(request);
    const auto& resp = respPair.second;
    
    return resp->statusCode();
}
