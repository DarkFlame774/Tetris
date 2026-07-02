#pragma once
#include <string>
struct ConfigDemo
{
    std::string backendHost = "localhost";
    uint16_t backendPort = 8080;
    bool useHttps = false;
};
ConfigDemo g_configDemo;