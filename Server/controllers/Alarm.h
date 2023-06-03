#pragma once
#include <drogon/HttpController.h>

class Alarm : public drogon::HttpController<Alarm>
{
public:
    METHOD_LIST_BEGIN
        METHOD_ADD(Alarm::GetAllAlarms, "/", drogon::Get);
        METHOD_ADD(Alarm::Clear, "/clear", drogon::Post);
    METHOD_LIST_END

public:
    void GetAllAlarms(const drogon::HttpRequestPtr& req,
               std::function<void(const drogon::HttpResponsePtr&)>&& callback);

    void Clear(const drogon::HttpRequestPtr& req,
               std::function<void (const drogon::HttpResponsePtr&)>&& callback);

private:
    drogon::HttpStatusCode AcknowledgeAlarm(const std::string& token, const std::string& alarmId) const;
    drogon::HttpStatusCode ClearAlarm(const std::string& token, const std::string& alarmId) const;
};
