#include "APIManager.h"
#include <iostream>

void CheckResponse(DWORD status, json& response)
{
	if (status != 200 && status != 201) {
		std::string message = response["message"];
		throw std::runtime_error(message.c_str());
	}
}

APIManager::APIManager() {
	hSession = WinHttpOpen(
		L"Tetris/1.0",
		WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
		WINHTTP_NO_PROXY_NAME,
		WINHTTP_NO_PROXY_BYPASS,
		0
	);

	hConnect = WinHttpConnect(
		hSession,
		std::wstring(g_config.backendHost.begin(),g_config.backendHost.end()).c_str(),
		g_config.backendPort,
		0
	);
}

APIManager::~APIManager() {
	WinHttpCloseHandle(hConnect);
	WinHttpCloseHandle(hSession);
}

void APIManager::Register(std::string& name, std::string& pass) {
	json requestBody;
	requestBody["name"] = name;
	requestBody["password"] = pass;
	std::string payload = requestBody.dump();
	json response;
	RegisterRequest req(hConnect);
	response = req.Execute(payload);
	DWORD status = req.GetStatus();
	CheckResponse(status, response);
}

json APIManager::Login(std::string& name, std::string& pass) {
	json requestBody;
	requestBody["name"] = name;
	requestBody["password"] = pass;
	std::string payload = requestBody.dump();
	LoginRequest req(hConnect);
	json response = req.Execute(payload);
	DWORD status = req.GetStatus();
	CheckResponse(status, response);
	return response;
}

ll APIManager::StartSession(json id) {
	std::string payload = id.dump();
	StartSessionRequest req(hConnect);
	json response = req.Execute(payload);
	DWORD status = req.GetStatus();
	CheckResponse(status, response);
	return response["sessionId"];
}

void APIManager::EndSession(ll sessionId, int linesCleared, int score) {
	json body;
	body["sessionId"] = sessionId;
	body["linesCleared"] = linesCleared;
	body["score"] = score;
	std::string payload = body.dump();
	EndSessionRequest req(hConnect);
	json response = req.Execute(payload);
	DWORD status = req.GetStatus();
	CheckResponse(status, response);
}

json APIManager::GetDashboard(json id) {
		std::string payload = id.dump();
		LeaderboardRequest req(hConnect);
		json response = req.Execute(payload);
		DWORD status = req.GetStatus();
		CheckResponse(status, response);
		return response;
}
