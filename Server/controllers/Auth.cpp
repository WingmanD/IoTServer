#include "Auth.h"
#include "../Util.h"

void Auth::GetLogin(const drogon::HttpRequestPtr& req, std::function<void(const drogon::HttpResponsePtr&)>&& callback)
{
    const auto resp = drogon::HttpResponse::newHttpViewResponse("login.csp");
    callback(resp);
}

void Auth::PostLogin(const drogon::HttpRequestPtr& req,
                     std::function<void(const drogon::HttpResponsePtr&)>&& callback)
{
    const std::string username = req->getParameter("username");
    const std::string password = req->getParameter("password");

    if (username.empty() || password.empty())
    {
        const auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::HttpStatusCode::k400BadRequest);
        callback(resp);
    }

    const std::string token = Util::Login(username, password);

    if (token.empty())
    {
        const auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::HttpStatusCode::k401Unauthorized);
        callback(resp);
    }

    drogon::Cookie jwtCookie("jwt", token);
    jwtCookie.setPath("/");
    jwtCookie.setHttpOnly(false);
    jwtCookie.setSecure(true);
    jwtCookie.setSameSite(drogon::Cookie::SameSite::kNone);

    drogon::Cookie usernameCookie("username", username);
    usernameCookie.setPath("/");
    usernameCookie.setHttpOnly(false);
    usernameCookie.setSecure(true);
    usernameCookie.setSameSite(drogon::Cookie::SameSite::kNone);

    const auto resp = drogon::HttpResponse::newRedirectionResponse("/dashboard/");
    resp->addCookie(jwtCookie);
    resp->addCookie(usernameCookie);
    callback(resp);
}
