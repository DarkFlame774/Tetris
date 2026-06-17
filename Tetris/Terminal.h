#pragma once
#ifdef _WIN32
	#include "Windows.h"
	#define SETUP_TERMINAL 	SetConsoleOutputCP(CP_UTF8);
	#define RESTORE_TERMINAL
#else
	#include <termios.h>
	#include <unistd.h>
	#include <fcntl.h>
	#include <cstdlib>
	#include <csignal>
	extern termios oldTerm;

	#define RESTORE_TERMINAL tcsetattr(STDIN_FILENO, TCSANOW, &oldTerm);
	
	void SignalHandler(int signal);
	
	#define SETUP_TERMINAL									  \
			tcgetattr(STDIN_FILENO, &oldTerm);				  \
			std::signal(SIGINT, SignalHandler);				  \
			std::signal(SIGTERM, SignalHandler);			  \
			std::signal(SIGHUP, SignalHandler);				  \
			termios newTerm = oldTerm;						  \
			newTerm.c_lflag &= ~(ICANON | ECHO);			  \
			newTerm.c_cc[VMIN] = 0;							  \
			newTerm.c_cc[VTIME] = 0;						  \
			tcsetattr(STDIN_FILENO, TCSANOW, &newTerm);		  \
			fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

#endif