#include "Measurements.h"
#include "../Util.h"
#include <drogon/HttpClient.h>

void Measurements::GetAllMeasurements(const drogon::HttpRequestPtr& req,
                                      std::function<void(const drogon::HttpResponsePtr&)>&& callback)
{
    auto cookies = req->getCookies();
    if (!cookies.contains("jwt") || !cookies.contains("username"))
    {
        const auto response = drogon::HttpResponse::newHttpResponse();
        response->setStatusCode(drogon::HttpStatusCode::k401Unauthorized);
        callback(response);
        return;
    }

    constexpr const char* sensorDeviceId = "564a8980-f58e-11ed-993d-8d74c2abdddd";

    const Json::Value telemetry = Util::GetDeviceTelemetry(cookies["jwt"], sensorDeviceId, "temperature,humidity");
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
