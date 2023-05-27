#pragma once

#include <drogon/HttpController.h>

class Auth : public drogon::HttpController<Auth>
{
public:
    METHOD_LIST_BEGIN
        METHOD_ADD(Auth::GetLogin, "/login", drogon::Get);
        METHOD_ADD(Auth::PostLogin, "/login", drogon::Post);
    METHOD_LIST_END

public:
    void GetLogin(const drogon::HttpRequestPtr& req,
                  std::function<void (const drogon::HttpResponsePtr&)>&& callback);

    void PostLogin(const drogon::HttpRequestPtr& req,
                   std::function<void (const drogon::HttpResponsePtr&)>&& callback);
};
