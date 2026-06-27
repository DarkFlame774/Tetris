#pragma once
#include "Request.h"
typedef long long ll;

class APIManager {
private:
	HINTERNET hSession;
	HINTERNET hConnect;

public:
	APIManager() {
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
	~APIManager() {
		WinHttpCloseHandle(hConnect);
		WinHttpCloseHandle(hSession);
	}

	ll Login(std::string& name, std::string& pass) {
		json requestBody;
		requestBody["name"] = name;
		requestBody["password"] = pass;
		std::string payload = requestBody.dump();
		LoginRequest req(hConnect);
		req.Send(payload);
		json response = req.RecieveResponse();
		return response["id"];
	}
	void Register(std::string& name, std::string& pass) {
		json requestBody;
		requestBody["name"] = name;
		requestBody["password"] = pass;
		std::string payload = requestBody.dump();
		RegisterRequest req(hConnect);
		req.Send(payload);
	}
};
