#pragma once

#include <drogon/HttpTypes.h>
#include <json/json_features.h>
#include <expected>
#include <drogon/HttpResponse.h>

class Util
{
public:
    static std::string ThingsBoardHost;
    static std::string SensorDeviceId;
    static std::string VirtualDeviceAccessToken;
    static int RequiredTemperatureForTurningOff;
    
public:
    using TBResult = std::expected<Json::Value, drogon::HttpStatusCode>;
    
    static Json::Value ParseJson(const std::string& text);
    
    static std::expected<std::string, drogon::HttpStatusCode> Login(const std::string& username, const std::string& password);
    
    static TBResult GetDeviceTelemetry(const std::string& token, const std::string& deviceId, const std::string& keys);
    static TBResult GetDeviceCurrentTelemetry(const std::string& token, const std::string& deviceId, const std::string& keys);

    static TBResult GetDeviceAlarms(const std::string& token, const std::string& deviceId);

    static TBResult GetDeviceAttributes(const std::string& token, const std::string& deviceAccessToken, const std::string& attributes);
    static drogon::HttpStatusCode PostDeviceAttributes(const std::string& token, const std::string& deviceAccessToken, const Json::Value& attributes);

    static bool Verify(const TBResult& result, const std::function<void(const drogon::HttpResponsePtr&)>& callback);
};
