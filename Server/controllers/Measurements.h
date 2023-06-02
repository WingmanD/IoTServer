#pragma once

#include <drogon/HttpController.h>

class Measurements : public drogon::HttpController<Measurements>
{
public:
    METHOD_LIST_BEGIN
        METHOD_ADD(Measurements::GetAllMeasurements, "/", drogon::Get);
        METHOD_ADD(Measurements::GetAttributes, "/attributes", drogon::Get);
        METHOD_ADD(Measurements::PostAttributes, "/attributes", drogon::Post);
        METHOD_ADD(Measurements::GetDeviceStatus, "/status", drogon::Get);
        METHOD_ADD(Measurements::PostDeviceStatus, "/status", drogon::Post);
    METHOD_LIST_END

public:
    void GetAllMeasurements(const drogon::HttpRequestPtr& req,
                            std::function<void (const drogon::HttpResponsePtr&)>&& callback);
    
    void GetAttributes(const drogon::HttpRequestPtr& req,
                       std::function<void (const drogon::HttpResponsePtr&)>&& callback);
    void PostAttributes(const drogon::HttpRequestPtr& req,
                        std::function<void (const drogon::HttpResponsePtr&)>&& callback);

    void GetDeviceStatus(const drogon::HttpRequestPtr& req,
                         std::function<void (const drogon::HttpResponsePtr&)>&& callback);
    void PostDeviceStatus(const drogon::HttpRequestPtr& req,
                          std::function<void (const drogon::HttpResponsePtr&)>&& callback);
};
