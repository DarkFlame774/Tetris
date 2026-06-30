#pragma once
#include <Windows.h>
#include <winhttp.h>
#include <string>
#include <json.hpp>

typedef nlohmann::json json; 

class Request {
	protected:
		HINTERNET request;
		char buffer[8192];
		
		~Request() {
			WinHttpCloseHandle(request);
		}

		Request(HINTERNET& hConnect, const LPCWSTR& method, const LPCWSTR& url) {
			request = WinHttpOpenRequest(
				hConnect,
				method,
				url,
				nullptr,
				WINHTTP_NO_REFERER,
				WINHTTP_DEFAULT_ACCEPT_TYPES,
				0
			);
		}


	public:
		bool Send(std::string& payload) {
			int err = WinHttpSendRequest(
				request,
				L"Content-Type: application/json\r\n",
				(DWORD)-1L,
				(LPVOID)payload.c_str(),
				(DWORD)payload.size(),
				(DWORD)payload.size(),
				0
			);
			return err;
		}

		json RecieveResponse() {
			WinHttpReceiveResponse(
				request,
				nullptr
			);

			DWORD bytesRead = 0;

			WinHttpReadData(
				request,
				buffer,
				sizeof(buffer),
				&bytesRead
			);
			if(bytesRead == 0) return json{};
			std::string str(buffer, bytesRead);
			json response = json::parse(std::string(buffer, bytesRead));
			return response;
		}
};

class LoginRequest : public Request {
	public:
		LoginRequest(HINTERNET& hConnect) 
		: Request(hConnect, L"POST", L"/api/v1/player/login")
		{}
};

class RegisterRequest : public Request {
	public:
		RegisterRequest(HINTERNET& hConnect)
			: Request(hConnect, L"POST", L"/api/v1/player/register")
		{}
};

class StartSessionRequest : public Request {
	public:
		StartSessionRequest(HINTERNET& hConnect)
			: Request(hConnect, L"POST", L"/api/v1/game/start")
		{}
}; 

class EndSessionRequest : public Request {
	public:
		EndSessionRequest(HINTERNET& hConnect)
			: Request(hConnect, L"POST", L"/api/v1/game/end")
		{}
}; 

class LeaderboardRequest : public Request {
	public:
		LeaderboardRequest(HINTERNET& hConnect)
			: Request(hConnect, L"GET", L"/api/v1/game/leaderboard")
		{}
}; 