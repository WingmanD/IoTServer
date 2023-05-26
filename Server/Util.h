#pragma once
#include <json/json_features.h>

class Util
{
public:
    static std::string ThingsboardHost;
public:
    static Json::Value ParseJson(const std::string& text);
    
    static std::string Login(const std::string& username, const std::string& password);
    
    static Json::Value GetDeviceTelemetry(const std::string& token, const std::string& deviceId, const std::string& keys);
};
