#pragma once

#include <drogon/HttpTypes.h>
#include <json/json_features.h>
#include <expected>

class Util
{
public:
    static std::string ThingsBoardHost;
    static std::string SensorDeviceId;
    static std::string VirtualDeviceAccessToken;
    static int RequiredTemperatureForTurningOff;
    
public:
    static Json::Value ParseJson(const std::string& text);
    
    static std::expected<std::string, drogon::HttpStatusCode> Login(const std::string& username, const std::string& password);
    
    static Json::Value GetDeviceTelemetry(const std::string& token, const std::string& deviceId, const std::string& keys);
    static Json::Value GetDeviceCurrentTelemetry(const std::string& token, const std::string& deviceId, const std::string& keys);

    static Json::Value GetDeviceAlarms(const std::string& token, const std::string& deviceId);

    static Json::Value GetDeviceAttributes(const std::string& token, const std::string& deviceAccessToken, const std::string& attributes);
    static drogon::HttpStatusCode PostDeviceAttributes(const std::string& token, const std::string& deviceAccessToken, const Json::Value& attributes);
};
