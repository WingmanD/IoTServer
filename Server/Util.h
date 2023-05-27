#pragma once

#include <drogon/HttpTypes.h>
#include <json/json_features.h>

class Util
{
public:
    static std::string ThingsBoardHost;
public:
    static Json::Value ParseJson(const std::string& text);
    
    static std::string Login(const std::string& username, const std::string& password);
    
    static Json::Value GetDeviceTelemetry(const std::string& token, const std::string& deviceId, const std::string& keys);

    static Json::Value GetDeviceAlarms(const std::string& token, const std::string& deviceId);
};
