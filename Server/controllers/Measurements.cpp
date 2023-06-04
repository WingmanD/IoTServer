#include "Measurements.h"
#include "../Util.h"
#include <drogon/HttpClient.h>

void Measurements::GetAllMeasurements(const drogon::HttpRequestPtr& req, std::function<void(const drogon::HttpResponsePtr&)>&& callback)
{
    auto cookies = req->getCookies();
    if (!cookies.contains("jwt") || !cookies.contains("username"))
    {
        const auto response = drogon::HttpResponse::newHttpResponse();
        response->setStatusCode(drogon::HttpStatusCode::k401Unauthorized);
        callback(response);
        return;
    }
    
    const auto result = Util::GetDeviceTelemetry(cookies["jwt"], Util::SensorDeviceId, "temperature,humidity");
    if (!Util::Verify(result, callback))
    {
        return;
    }

    const Json::Value& telemetry = *result;
    
    const auto response = drogon::HttpResponse::newHttpJsonResponse(telemetry);
    callback(response);
}

void Measurements::GetAttributes(const drogon::HttpRequestPtr& req, std::function<void(const drogon::HttpResponsePtr&)>&& callback)
{
    auto cookies = req->getCookies();
    if (!cookies.contains("jwt") || !cookies.contains("username"))
    {
        const auto response = drogon::HttpResponse::newHttpResponse();
        response->setStatusCode(drogon::HttpStatusCode::k401Unauthorized);
        callback(response);
        return;
    }

    const std::string attributes = req->getParameter("attr");
    
    const auto result = Util::GetDeviceAttributes(cookies["jwt"], Util::VirtualDeviceAccessToken, attributes);
    if (!Util::Verify(result, callback))
    {
        return;
    }

    const Json::Value& attributeValues = *result;
    
    const auto response = drogon::HttpResponse::newHttpJsonResponse(attributeValues);
    callback(response);
}

void Measurements::PostAttributes(const drogon::HttpRequestPtr& req, std::function<void(const drogon::HttpResponsePtr&)>&& callback)
{
    auto cookies = req->getCookies();
    if (!cookies.contains("jwt") || !cookies.contains("username"))
    {
        const auto response = drogon::HttpResponse::newHttpResponse();
        response->setStatusCode(drogon::HttpStatusCode::k401Unauthorized);
        callback(response);
        return;
    }

    if (req->getJsonObject() == nullptr)
    {
        const auto response = drogon::HttpResponse::newHttpResponse();
        response->setStatusCode(drogon::HttpStatusCode::k400BadRequest);
        callback(response);
        return;
    }
    
    const drogon::HttpStatusCode result = Util::PostDeviceAttributes(cookies["jwt"], Util::VirtualDeviceAccessToken, req->getJsonObject().get());
    
    const auto response = drogon::HttpResponse::newHttpResponse();
    response->setStatusCode(result);
    callback(response);
}

void Measurements::GetDeviceStatus(const drogon::HttpRequestPtr& req, std::function<void(const drogon::HttpResponsePtr&)>&& callback)
{
    auto cookies = req->getCookies();
    if (!cookies.contains("jwt") || !cookies.contains("username"))
    {
        const auto response = drogon::HttpResponse::newHttpResponse();
        response->setStatusCode(drogon::HttpStatusCode::k401Unauthorized);
        callback(response);
        return;
    }
    
    const auto& attributesResult = Util::GetDeviceAttributes(cookies["jwt"], Util::VirtualDeviceAccessToken, "active");
    if (!Util::Verify(attributesResult, callback))
    {
        return;
    }

    Json::Value attributeValues = *attributesResult;

    const auto& telemetryResult = Util::GetDeviceCurrentTelemetry(cookies["jwt"], Util::SensorDeviceId, "temperature");
    if (!Util::Verify(telemetryResult, callback))
    {
        return;
    }

    const Json::Value& telemetry = *telemetryResult;

    const std::string temp = telemetry["temperature"][0]["value"].asString();
    const int temperature = std::stoi(temp);

    attributeValues["canDisable"] = temperature >= Util::RequiredTemperatureForTurningOff;

    const auto response = drogon::HttpResponse::newHttpJsonResponse(attributeValues);
    callback(response);
}

void Measurements::PostDeviceStatus(const drogon::HttpRequestPtr& req, std::function<void(const drogon::HttpResponsePtr&)>&& callback)
{
    auto cookies = req->getCookies();
    if (!cookies.contains("jwt") || !cookies.contains("username"))
    {
        const auto response = drogon::HttpResponse::newHttpResponse();
        response->setStatusCode(drogon::HttpStatusCode::k401Unauthorized);
        callback(response);
        return;
    }

    const auto& result = Util::GetDeviceCurrentTelemetry(cookies["jwt"], Util::SensorDeviceId, "temperature");
    if (!Util::Verify(result, callback))
    {
        return;
    }

    const auto& telemetry = *result;

    const std::string temp = telemetry["temperature"][0]["value"].asString();
    const int temperature = std::stoi(temp);

    if (temperature < Util::RequiredTemperatureForTurningOff)
    {
        const auto response = drogon::HttpResponse::newHttpResponse();
        response->setStatusCode(drogon::HttpStatusCode::k403Forbidden);
        callback(response);
        return;
    }

    Json::Value attributes;
    attributes["active"] = req->getParameter("active");
    
    const drogon::HttpStatusCode attributeValues = Util::PostDeviceAttributes(cookies["jwt"], Util::VirtualDeviceAccessToken, attributes);
    
    const auto response = drogon::HttpResponse::newHttpResponse();
    response->setStatusCode(attributeValues);
    callback(response);
}
