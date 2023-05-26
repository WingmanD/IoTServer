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
    
    //
    // constexpr const char* thingsBoardHost = "http://161.53.19.19:45080";
    // const auto client = drogon::HttpClient::newHttpClient(thingsBoardHost);
    //
    // Json::Value requestJson;
    // requestJson["username"] = "tenant@thingsboard.org";
    // requestJson["password"] = "tenant";
    //
    // const drogon::HttpRequestPtr loginRequest = drogon::HttpRequest::newHttpJsonRequest(requestJson);
    // loginRequest->setMethod(drogon::HttpMethod::Post);
    // loginRequest->setPath("/api/auth/login");
    //
    // const auto loginRespPair = client->sendRequest(loginRequest);
    // const auto loginReqResult = loginRespPair.first;
    // const auto& loginResponse = loginRespPair.second;
    //
    // if (loginReqResult != drogon::ReqResult::Ok) {
    //     std::cerr << "Login failed: " << loginReqResult << std::endl;
    //     
    //     const auto response = drogon::HttpResponse::newHttpResponse();
    //     response->setStatusCode(drogon::HttpStatusCode::k401Unauthorized);
    //     callback(response);
    //     
    //     return;
    // }
    //
    // const Json::Value loginResponseJson = *loginResponse->getJsonObject();
    // const std::string token = loginResponseJson["token"].asString();
    //
    // drogon::HttpRequestPtr telemetryRequest = drogon::HttpRequest::newHttpRequest(requestJson);
    // telemetryRequest->setMethod(drogon::HttpMethod::Get);
    // telemetryRequest->setPath("/api/plugins/telemetry/DEVICE/c32e6c20-ca4f-11ed-993d-8d74c2abdddd/values/timeseries?keys=temperature,humidity");
    // telemetryRequest->addHeader("X-Authorization", "Bearer " + token);
    //
    // const auto respPair = client->sendRequest(telemetryRequest);
    // const auto reqResult = respPair.first;
    // const auto& resp = respPair.second;
    //
    // if (reqResult != drogon::ReqResult::Ok) {
    //     std::cerr << "Get telemetry failed: " << reqResult << std::endl;
    //     
    //     const auto response = drogon::HttpResponse::newHttpResponse();
    //     response->setStatusCode(drogon::HttpStatusCode::k500InternalServerError);
    //     callback(response);
    //     
    //     return;
    // }
    //
    // const Json::Value telemetryResponseJson = *resp->getJsonObject();
    // std::cout << "Telemetry: " << telemetryResponseJson << std::endl;
    // const auto response = drogon::HttpResponse::newHttpJsonResponse(telemetryResponseJson);
    // callback(response);
    
    /*
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
    */
}
