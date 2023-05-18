#pragma once

#include <drogon/HttpController.h>

class Measurements : public drogon::HttpController<Measurements>
{
public:
    METHOD_LIST_BEGIN
        METHOD_ADD(Measurements::GetAllMeasurements, "/", drogon::Get);
        METHOD_ADD(Measurements::AddMeasurement, "/", drogon::Post);
    METHOD_LIST_END

public:
    void GetAllMeasurements(const drogon::HttpRequestPtr& req,
                            std::function<void (const drogon::HttpResponsePtr&)>&& callback);

    void AddMeasurement(const drogon::HttpRequestPtr& req,
                        std::function<void (const drogon::HttpResponsePtr&)>&& callback);
};
