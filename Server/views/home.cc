//this file is generated by program(drogon_ctl) automatically,don't modify it!
#include "home.h"
#include <drogon/utils/OStringStream.h>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <list>
#include <deque>
#include <queue>

     #include <drogon/drogon.h>

using namespace drogon;
std::string home::genText(const DrTemplateData& home_view_data)
{
	drogon::OStringStream home_tmp_stream;
	std::string layoutName{""};
 
    auto params = home_view_data.get<std::unordered_map<std::string,std::string>>("params");
    auto username = home_view_data.get<std::string>("username");
	home_tmp_stream << "<head>\n";
	home_tmp_stream << "    <meta charset=\"UTF-8\">\n";
	home_tmp_stream << "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
	home_tmp_stream << "    <meta http-equiv=\"refresh\" content=\"300\">\n";
	home_tmp_stream << "    <link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css\" rel=\"stylesheet\"\n";
	home_tmp_stream << "          integrity=\"sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC\" crossorigin=\"anonymous\">\n";
	home_tmp_stream << "    <link rel=\"stylesheet\" href=\"/main.css\">\n";
	home_tmp_stream << "    <script src=\"https://cdn.jsdelivr.net/npm/chart.js@4.3.0/dist/chart.umd.min.js\"></script>\n";
	home_tmp_stream << "    <script src=\"https://cdn.jsdelivr.net/npm/moment@2.29.4/moment.min.js\"></script>\n";
	home_tmp_stream << "    <script src=\"https://cdn.jsdelivr.net/npm/chartjs-adapter-moment@1.0.1/dist/chartjs-adapter-moment.min.js\"></script>\n";
	home_tmp_stream << "    <script src=\"/renderchart.js\"></script>\n";
	home_tmp_stream << "    <title>Water Leak Dashboard</title>   \n";
	home_tmp_stream << "</head>\n";
home_tmp_stream<<"\n";
	home_tmp_stream << "<body>\n";
	home_tmp_stream << "<nav class=\"navbar navbar-expand-lg navbar-light bg-light\">\n";
	home_tmp_stream << "    <div class=\"container\">\n";
	home_tmp_stream << "        <a class=\"navbar-brand\" href=\"/\">Water Leak Dashboard</a>\n";
	home_tmp_stream << "        <button class=\"navbar-toggler\" type=\"button\" data-toggle=\"collapse\" data-target=\"#navbarSupportedContent\"\n";
	home_tmp_stream << "                aria-controls=\"navbarSupportedContent\" aria-expanded=\"false\" aria-label=\"Toggle navigation\">\n";
	home_tmp_stream << "            <span class=\"navbar-toggler-icon\"></span>\n";
	home_tmp_stream << "        </button>\n";
home_tmp_stream<<"\n";
	home_tmp_stream << "        <div class=\"collapse navbar-collapse\" id=\"navbarSupportedContent\">\n";
	home_tmp_stream << "            <ul class=\"navbar-nav mr-auto\">\n";
	home_tmp_stream << "                <li class=\"nav-item active\">\n";
	home_tmp_stream << "                    <a class=\"nav-link\" href=\"/\">Home <span class=\"sr-only\">(current)</span></a>\n";
	home_tmp_stream << "                </li>\n";
	home_tmp_stream << "            </ul>\n";
	home_tmp_stream << "            ";
 if (username.empty()) {
	home_tmp_stream << "            <span class=\"navbar-text\">\n";
	home_tmp_stream << "                <a class=\"nav-link\" href=\"/auth/login\">Login</a>\n";
	home_tmp_stream << "            </span>\n";
	home_tmp_stream << "            ";
 } else {
	home_tmp_stream << "            <span class=\"navbar-text\">\n";
	home_tmp_stream << "                <a class=\"nav-link\" href=\"\" onclick=\"logout();return false;\">";
home_tmp_stream<<username;
	home_tmp_stream << " Logout</a>\n";
	home_tmp_stream << "            </span>\n";
	home_tmp_stream << "            ";
 } 
	home_tmp_stream << "        </div>\n";
	home_tmp_stream << "    </div>\n";
	home_tmp_stream << "</nav>\n";
	home_tmp_stream << "<div class=\"container align-content-center blur\">\n";
	home_tmp_stream << "    <br>\n";
	home_tmp_stream << "    <h1>Dashboard</h1>\n";
	home_tmp_stream << "    <br>\n";
	home_tmp_stream << "    <h2>Alarms</h2>\n";
	home_tmp_stream << "    <br>\n";
	home_tmp_stream << "    <div class=\"row\">\n";
	home_tmp_stream << "        <span id=\"alError\"></span>\n";
	home_tmp_stream << "    </div>\n";
	home_tmp_stream << "    <div class=\"row align-items-center\" id=\"alarmBase\">\n";
	home_tmp_stream << "        <div class=\"col-auto\">\n";
	home_tmp_stream << "            <button>❌ Dismiss</button>\n";
	home_tmp_stream << "        </div>\n";
	home_tmp_stream << "        <div class=\"col\">\n";
	home_tmp_stream << "            <span></span>\n";
	home_tmp_stream << "        </div>\n";
	home_tmp_stream << "    </div>\n";
	home_tmp_stream << "    <br>\n";
	home_tmp_stream << "    <h2>Devices</h2>\n";
	home_tmp_stream << "    <div class=\"row align-items-center d-none\" id=\"devcontainer\">\n";
	home_tmp_stream << "        <div class=\"col-auto text-end\">\n";
	home_tmp_stream << "            Virtual Device\n";
	home_tmp_stream << "        </div>\n";
	home_tmp_stream << "        <div class=\"col-auto\" id=\"devstatus\"></div>\n";
	home_tmp_stream << "        <div class=\"col\"><button id=\"devdisable\">❌ Shut down</button></div>\n";
	home_tmp_stream << "    </div>\n";
	home_tmp_stream << "    <br>\n";
	home_tmp_stream << "    <h2>Measurement History</h2>\n";
	home_tmp_stream << "    <br>\n";
	home_tmp_stream << "    <div class=\"row\">\n";
	home_tmp_stream << "        <span id=\"chError\"></span>\n";
	home_tmp_stream << "        <div class=\"col\">\n";
	home_tmp_stream << "            <canvas id=\"chHumidity\"></canvas>\n";
	home_tmp_stream << "        </div>\n";
	home_tmp_stream << "        <div class=\"col\">\n";
	home_tmp_stream << "            <canvas id=\"chTemperature\"></canvas>\n";
	home_tmp_stream << "        </div>\n";
	home_tmp_stream << "    </div>\n";
	home_tmp_stream << "</div>\n";
	home_tmp_stream << "</body>\n";
	home_tmp_stream << "</html>\n";
home_tmp_stream<<"\n";
	home_tmp_stream << "<script>\n";
	home_tmp_stream << "async function POST_reload(url) {\n";
	home_tmp_stream << "    var res = await fetch(url, { method: 'POST' });\n";
	home_tmp_stream << "    if (res.status == 200) location.reload();\n";
	home_tmp_stream << "    else {\n";
	home_tmp_stream << "        alert(`${url} returned ${res.status}`);\n";
	home_tmp_stream << "        console.log(res);\n";
	home_tmp_stream << "    }\n";
	home_tmp_stream << "}\n";
home_tmp_stream<<"\n";
	home_tmp_stream << "async function LoadAlarms() {\n";
	home_tmp_stream << "    var alarms = await (await fetch(\"/alarm/\")).json();\n";
	home_tmp_stream << "    var err = document.getElementById(\"alError\");\n";
	home_tmp_stream << "    var errRow = document.getElementById(\"alErrorRow\");\n";
home_tmp_stream<<"\n";
	home_tmp_stream << "    if (alarms.errorCode) {\n";
	home_tmp_stream << "        err.textContent = `${alarms.status}[${alarms.errorCode}]: ${alarms.message}`;\n";
	home_tmp_stream << "        base.remove();\n";
	home_tmp_stream << "        return;\n";
	home_tmp_stream << "    }\n";
home_tmp_stream<<"\n";
	home_tmp_stream << "    alarms = alarms.data.filter(i => i.status === \"ACTIVE_UNACK\");\n";
	home_tmp_stream << "    \n";
	home_tmp_stream << "    if (alarms.length == 0) {\n";
	home_tmp_stream << "        err.textContent = \"There are no active alarms at this time.\";\n";
	home_tmp_stream << "        base.remove();\n";
	home_tmp_stream << "        return;\n";
	home_tmp_stream << "    }\n";
home_tmp_stream<<"\n";
	home_tmp_stream << "    errRow.remove();\n";
home_tmp_stream<<"\n";
	home_tmp_stream << "    alarms.sort((a, b) => b.createdTime - a.createdTime);\n";
	home_tmp_stream << "    \n";
	home_tmp_stream << "    var base = document.getElementById(\"alarmBase\");\n";
home_tmp_stream<<"\n";
	home_tmp_stream << "    for (const alarm of alarms) {\n";
	home_tmp_stream << "        var elem = base.cloneNode(true);\n";
	home_tmp_stream << "        elem.removeAttribute(\"id\");\n";
	home_tmp_stream << "        elem.children[0].children[0].onclick = async () => await POST_reload(`/alarm/clear?id=${alarm.id.id}`);\n";
	home_tmp_stream << "        elem.children[1].children[0].textContent = `${new Date(alarm.createdTime).toLocaleString()}: ${alarm.severity} - ${alarm.name}`;\n";
	home_tmp_stream << "        base.after(elem);\n";
	home_tmp_stream << "    }\n";
home_tmp_stream<<"\n";
	home_tmp_stream << "    base.remove();\n";
	home_tmp_stream << "}\n";
home_tmp_stream<<"\n";
	home_tmp_stream << "async function LoadStatus() {\n";
	home_tmp_stream << "    var measurements = await (await fetch(\"/measurements/status\")).json();\n";
	home_tmp_stream << "    document.getElementById(\"devstatus\").textContent = measurements.client.active? \"🟢 Active\" : \"🔴 Inactive\";\n";
	home_tmp_stream << "    \n";
	home_tmp_stream << "    var btn = document.getElementById(\"devdisable\");\n";
home_tmp_stream<<"\n";
	home_tmp_stream << "    if (measurements.canDisable) {\n";
	home_tmp_stream << "        btn.onclick = async () => await POST_reload(\"/measurements/status?active=false\");\n";
	home_tmp_stream << "    } else {\n";
	home_tmp_stream << "        btn.remove();\n";
	home_tmp_stream << "    }\n";
home_tmp_stream<<"\n";
	home_tmp_stream << "    document.getElementById(\"devcontainer\").classList.remove(\"d-none\");\n";
	home_tmp_stream << "}\n";
home_tmp_stream<<"\n";
	home_tmp_stream << "async function LoadMeasurements() {\n";
	home_tmp_stream << "    var telemetry = await (await fetch(\"/measurements/\")).json();\n";
	home_tmp_stream << "    var err = document.getElementById(\"chError\");\n";
home_tmp_stream<<"\n";
	home_tmp_stream << "    if (telemetry.errorCode) {\n";
	home_tmp_stream << "        err.textContent = `${telemetry.status}[${telemetry.errorCode}]: ${telemetry.message}`;\n";
	home_tmp_stream << "        return;\n";
	home_tmp_stream << "    }\n";
home_tmp_stream<<"\n";
	home_tmp_stream << "    err.remove();\n";
home_tmp_stream<<"\n";
	home_tmp_stream << "    RenderChart(\n";
	home_tmp_stream << "        document.getElementById(\"chHumidity\"),\n";
	home_tmp_stream << "        telemetry.humidity,\n";
	home_tmp_stream << "        \"Humidity\", \"%\", 0, 100\n";
	home_tmp_stream << "    );\n";
home_tmp_stream<<"\n";
	home_tmp_stream << "    RenderChart(\n";
	home_tmp_stream << "        document.getElementById(\"chTemperature\"),\n";
	home_tmp_stream << "        telemetry.temperature,\n";
	home_tmp_stream << "        \"Temperature\", \"°C\"\n";
	home_tmp_stream << "    );\n";
	home_tmp_stream << "}\n";
home_tmp_stream<<"\n";
	home_tmp_stream << "function DeleteCookie(name) {\n";
	home_tmp_stream << "    document.cookie = name + '=;expires=Thu, 01 Jan 1970 00:00:01 GMT;path=/;';\n";
	home_tmp_stream << "}\n";
home_tmp_stream<<"\n";
	home_tmp_stream << "function logout() {\n";
	home_tmp_stream << "    DeleteCookie(\"username\");\n";
	home_tmp_stream << "    DeleteCookie(\"jwt\");\n";
	home_tmp_stream << "    location.reload();\n";
	home_tmp_stream << "}\n";
home_tmp_stream<<"\n";
	home_tmp_stream << "document.addEventListener(\"DOMContentLoaded\", LoadAlarms);\n";
	home_tmp_stream << "document.addEventListener(\"DOMContentLoaded\", LoadStatus);\n";
	home_tmp_stream << "document.addEventListener(\"DOMContentLoaded\", LoadMeasurements);\n";
	home_tmp_stream << "</script>\n";
if(layoutName.empty())
{
std::string ret{std::move(home_tmp_stream.str())};
return ret;
}else
{
auto templ = DrTemplateBase::newTemplate(layoutName);
if(!templ) return "";
HttpViewData data = home_view_data;
auto str = std::move(home_tmp_stream.str());
if(!str.empty() && str[str.length()-1] == '\n') str.resize(str.length()-1);
data[""] = std::move(str);
return templ->genText(data);
}
}
