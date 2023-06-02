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
    
    const Json::Value telemetry = Util::GetDeviceTelemetry(cookies["jwt"], Util::SensorDeviceId, "temperature,humidity");
    if (telemetry.empty())
    {
        const auto response = drogon::HttpResponse::newHttpResponse();
        response->setStatusCode(drogon::HttpStatusCode::k500InternalServerError);
        callback(response);
        return;
    }
    
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
    
    const Json::Value attributeValues = Util::GetDeviceAttributes(cookies["jwt"], Util::VirtualDeviceAccessToken, attributes);
    if (attributeValues.empty())
    {
        const auto response = drogon::HttpResponse::newHttpResponse();
        response->setStatusCode(drogon::HttpStatusCode::k500InternalServerError);
        callback(response);
        return;
    }
    
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
    
    const Json::Value attributeValues = Util::PostDeviceAttributes(cookies["jwt"], Util::VirtualDeviceAccessToken, req->getJsonObject().get());
    if (attributeValues.empty())
    {
        const auto response = drogon::HttpResponse::newHttpResponse();
        response->setStatusCode(drogon::HttpStatusCode::k500InternalServerError);
        callback(response);
        return;
    }
    
    const auto response = drogon::HttpResponse::newHttpJsonResponse(attributeValues);
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
    
    const Json::Value attributeValues = Util::GetDeviceAttributes(cookies["jwt"], Util::VirtualDeviceAccessToken, "active");
    if (attributeValues.empty())
    {
        const auto response = drogon::HttpResponse::newHttpResponse();
        response->setStatusCode(drogon::HttpStatusCode::k500InternalServerError);
        callback(response);
        return;
    }
    
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

    const Json::Value telemetry = Util::GetDeviceCurrentTelemetry(cookies["jwt"], Util::SensorDeviceId, "temperature");
    if (telemetry.empty())
    {
        const auto response = drogon::HttpResponse::newHttpResponse();
        response->setStatusCode(drogon::HttpStatusCode::k500InternalServerError);
        callback(response);
        return;
    }

    std::cout << "Telemetry: " << telemetry << std::endl;
    std::cout << "Temperature: " << telemetry["temperature"][0]["value"] << std::endl;

    const std::string temp = telemetry["temperature"][0]["value"].asString();
    const int temperature = std::stoi(temp);

    if (temperature > Util::RequiredTemperatureForTurningOff)
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
