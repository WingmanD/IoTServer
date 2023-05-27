#pragma once
#include <drogon/HttpController.h>

class Dashboard : public drogon::HttpController<Dashboard>
{
public:
    METHOD_LIST_BEGIN
    METHOD_ADD(Dashboard::Home, "/", drogon::Get);
    METHOD_LIST_END

public:
    void Home(const drogon::HttpRequestPtr& req,
                           std::function<void (const drogon::HttpResponsePtr&)>&& callback);
    
};
