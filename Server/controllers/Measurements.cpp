#include "Measurements.h"

#include "../DB/DBStatics.h"
#include "sqlite_orm/sqlite_orm.h"

void Measurements::GetAllMeasurements(const drogon::HttpRequestPtr& req,
                                        std::function<void(const drogon::HttpResponsePtr&)>&& callback)
{
    Json::Value responseJson;

    DBStatics::DBStorage.sync_schema();
    
    const auto allMeasurements = DBStatics::DBStorage.get_all<Measurement>();
    
    for (const auto& measurement : allMeasurements)
    {
        Json::Value measurementJson;
        measurementJson["ID"] = measurement.ID;
        measurementJson["Value"] = measurement.Value;
        measurementJson["Timestamp"] = measurement.Timestamp;
        responseJson.append(measurementJson);
    }

    const auto response = drogon::HttpResponse::newHttpJsonResponse(responseJson);
    callback(response);
}

void Measurements::AddMeasurement(const drogon::HttpRequestPtr& req,
                                    std::function<void(const drogon::HttpResponsePtr&)>&& callback)
{
    DBStatics::DBStorage.sync_schema();
    DBStatics::DBStorage.insert(Measurement{0, 0, "2020-01-01 01:00:00"});
    DBStatics::DBStorage.sync_schema();
    
    const auto response = drogon::HttpResponse::newHttpResponse();
    response->setStatusCode(drogon::k200OK);
    
    callback(response);
}
