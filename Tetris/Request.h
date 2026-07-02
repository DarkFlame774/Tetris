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


	private:

		void Send(std::string& payload) {
			if (!WinHttpSendRequest(
				request,
				L"Content-Type: application/json\r\n",
				(DWORD)-1L,
				(LPVOID)payload.c_str(),
				(DWORD)payload.size(),
				(DWORD)payload.size(),
				0
			)) 
			{
				throw std::runtime_error(" Could not Send the request!!! , Check Internet connection.");
			}
		}

		json RecieveResponse() {
			if (!WinHttpReceiveResponse(
				request,
				nullptr
			)) 
			{
				throw std::runtime_error("Error Recieving the request.");
			}
			DWORD bytesRead = 0;

			if (!WinHttpReadData(
				request,
				buffer,
				sizeof(buffer),
				&bytesRead
			)) 
			{
				throw std::runtime_error("Error reading data");
			}
			if(bytesRead == 0) return json{};
			std::string str(buffer, bytesRead);
			json response = json::parse(std::string(buffer, bytesRead));
			return response;
		}

	public:

		DWORD GetStatus() {
			DWORD statusCode;
			DWORD size = sizeof(statusCode);
			WinHttpQueryHeaders(
				request,
				WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER,
				WINHTTP_HEADER_NAME_BY_INDEX,
				&statusCode,
				&size,
				WINHTTP_NO_HEADER_INDEX
			);
			return statusCode;
		}

		json Execute(std::string& payload) {
			Send(payload);
			json response = RecieveResponse();
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