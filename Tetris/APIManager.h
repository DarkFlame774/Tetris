#pragma once
#include "Request.h"
typedef long long ll;

class APIManager {
private:
	HINTERNET hSession;
	HINTERNET hConnect;

public:
	APIManager();
	~APIManager();

	json Login(std::string& name, std::string& pass);
	void Register(std::string& name, std::string& pass);

	ll StartSession(json id);
	void EndSession(ll sessionId, int linesCleared, int score);

	json GetDashboard(json id);


};
