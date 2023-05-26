#include "Measurements.h"
#include "../Util.h"
#include <drogon/HttpClient.h>

void Measurements::GetAllMeasurements(const drogon::HttpRequestPtr& req,
                                      std::function<void(const drogon::HttpResponsePtr&)>&& callback)
{
    const std::string token = Util::Login("tenant@thingsboard.org", "tenant");
    if (token.empty())
    {
        const auto response = drogon::HttpResponse::newHttpResponse();
        response->setStatusCode(drogon::HttpStatusCode::k401Unauthorized);
        callback(response);

        return;
    }
    
    const Json::Value telemetry = Util::GetDeviceTelemetry(token, "c32e6c20-ca4f-11ed-993d-8d74c2abdddd", "temperature,humidity");
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
