#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "yhirose/httplib.h"    // https://github.com/yhirose/cpp-httplib
#include "nlohmann/json.hpp"    // https://github.com/nlohmann/json

#include <iostream>

using json = nlohmann::json;

int main(int argc, char **argv)
{
    httplib::SSLClient cli("api.github.com");
    std::string user = argv[1];
    std::string since = argc == 3 ? argv[2] : "2019-08-05T00:00:00Z";
    auto res = cli.Get(std::string("/users/" + user + "/repos").c_str());
    if (res && res->status == 200)
    {
        auto repos = json::parse(res->body);
        for (auto& repo : repos)
        {
            std::string repo_name = repo["full_name"];
            std::cout << repo_name << "\n";
            auto commits_res = cli.Get(
                std::string("/repos/" + repo_name + "/commits?author=" + user + "&since=" + since).c_str());
            if (commits_res && commits_res->status == 200)
            {
                auto commits_json = json::parse(commits_res->body);
                std::cout << commits_json.size() << "\n";
            }
        }
    }
}
