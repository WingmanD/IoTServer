#include "Measurements.h"

#include <drogon/HttpClient.h>

void Measurements::GetAllMeasurements(const drogon::HttpRequestPtr& req,
                                      std::function<void(const drogon::HttpResponsePtr&)>&& callback)
{
    // todo ip:port
    const auto client = drogon::HttpClient::newHttpClient("http://127.0.0.1:8080");

    // todo access token
    const std::string requestPath("/api/tenant/devices");

    drogon::HttpRequestPtr request = drogon::HttpRequest::newHttpRequest();
    request->setMethod(drogon::HttpMethod::Get);
    request->setPath(requestPath);

    const auto respPair = client->sendRequest(request);
    const auto reqResult = respPair.first;
    const auto& resp = respPair.second;
    
    if (reqResult != drogon::ReqResult::Ok) {
        std::cerr << "Failed to retrieve device IDs: error " << reqResult << std::endl;
        
        const auto response = drogon::HttpResponse::newHttpResponse();
        response->setStatusCode(drogon::HttpStatusCode::k500InternalServerError);
        callback(response);
    }

    std::cout << "Device IDs retrieved successfully!" << std::endl;
    std::cout << "Response body: " << resp->getBody() << std::endl;
    
    Json::Value deviceIDs;
    Json::CharReaderBuilder builder;
    std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    std::string errors;
    
    if (!reader->parse(resp->getBody().data(), resp->getBody().data() + resp->getBody().size(), &deviceIDs, &errors))
    {
        std::cerr << "Failed to parse JSON" << std::endl;
        
        const auto response = drogon::HttpResponse::newHttpResponse();
        response->setStatusCode(drogon::HttpStatusCode::k500InternalServerError);
        callback(response);
    }
    
    Json::Value responseJson;

    for (const auto& deviceID : deviceIDs)
    {
        const std::string deviceIDString = deviceID.asString();
        std::cout << "Device ID: " << deviceIDString << std::endl;

        // todo: access token
        const std::string devicePath = "/api/v1/" + deviceIDString + "/telemetry";
        
        drogon::HttpRequestPtr deviceRequest = drogon::HttpRequest::newHttpRequest();
        deviceRequest->setMethod(drogon::HttpMethod::Get);
        deviceRequest->setPath(devicePath);
        
        const auto deviceRespPair = client->sendRequest(deviceRequest);
        const auto deviceReqResult = deviceRespPair.first;
        const auto& deviceResp = deviceRespPair.second;
        
        if (deviceReqResult != drogon::ReqResult::Ok) {
            std::cerr << "Failed to retrieve device measurements: error " << deviceReqResult << std::endl;
            
            const auto response = drogon::HttpResponse::newHttpResponse();
            response->setStatusCode(drogon::HttpStatusCode::k500InternalServerError);
            callback(response);
        }
        
        std::cout << "Device measurements retrieved successfully!" << std::endl;
        std::cout << "Response body: " << deviceResp->getBody() << std::endl;
        
        Json::Value deviceMeasurements;
        
        if (!reader->parse(deviceResp->getBody().data(), deviceResp->getBody().data() + deviceResp->getBody().size(), &deviceMeasurements, &errors))
        {
            std::cerr << "Failed to parse JSON" << std::endl;
            
            const auto response = drogon::HttpResponse::newHttpResponse();
            response->setStatusCode(drogon::HttpStatusCode::k500InternalServerError);
            callback(response);
        }

        // todo parse
        for (const auto& measurement : deviceMeasurements)
        {
            Json::Value measurementJson;
            measurementJson["ID"] = measurement["ts"];
            measurementJson["Value"] = measurement["value"];
            measurementJson["Timestamp"] = measurement["ts"];
            responseJson.append(measurementJson);
        }
    }

    const auto response = drogon::HttpResponse::newHttpJsonResponse(responseJson);
    callback(response);
}
