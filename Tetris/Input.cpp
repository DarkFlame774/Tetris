#include "Input.h"
#ifndef _WIN32
	termios oldTerm;

	void SignalHandler(int signal) {
		RESTORE_TERMINAL;
		std::exit(signal);
	}

#endif

bool Input::GetKeyState(Key key) {
	return HandleInput(key);
}

bool HandleInput(Key key) {
	#ifdef _WIN32 
		switch (key) {
			case Key::Right :
				return (GetAsyncKeyState('D') || (GetAsyncKeyState(VK_RIGHT) & 0x8000));
			case Key::Left :
				return (GetAsyncKeyState('A') || (GetAsyncKeyState(VK_LEFT) & 0x8000));
			case Key::Down :
				return (GetAsyncKeyState('S') || (GetAsyncKeyState(VK_DOWN) & 0x8000));
			case Key::Space :
				return (GetAsyncKeyState(VK_SPACE));
			default:
				return false;
		}
	#else
		char c1;
		if (read(STDIN_FILENO, &c1, 1)) return false;
		switch (key) {
			case Key::Right:
				return (c1 == 'd');
		
			case Key::Left:
				return (c1 == 'a');
		
			case Key::Down:
				return (c1 == 's');
		
			case Key::Space:
				return (c1 == ' ');
		
			default:
				return false;
		}
	#endif
}
