#include "APIManager.h"

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
		L"localhost",
		8080,
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
	RegisterRequest req(hConnect);
	req.Send(payload);
}

json APIManager::Login(std::string& name, std::string& pass) {
	json requestBody;
	requestBody["name"] = name;
	requestBody["password"] = pass;
	std::string payload = requestBody.dump();
	LoginRequest req(hConnect);
	req.Send(payload);
	json response = req.RecieveResponse();
	return response;
}

ll APIManager::StartSession(json id) {
	std::string payload = id.dump();
	StartSessionRequest req(hConnect);
	req.Send(payload);
	json response = req.RecieveResponse();
	return response["sessionId"];
}

void APIManager::EndSession(ll sessionId, int linesCleared, int score) {
	json body;
	body["sessionId"] = sessionId;
	body["linesCleared"] = linesCleared;
	body["score"] = score;
	std::string payload = body.dump();
	EndSessionRequest req(hConnect);
	req.Send(payload);
}

json APIManager::GetDashboard(json id) {
		std::string payload = id.dump();
		LeaderboardRequest req(hConnect);
		req.Send(payload);
		return req.RecieveResponse();
}
