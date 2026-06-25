#include "Input.h"
#include <iostream>
#ifndef _WIN32
	termios oldTerm;

	void SignalHandler(int signal) {
		RESTORE_TERMINAL;
		std::exit(signal);
	}

#endif

Key Input::GetKey() {
#ifdef _WIN32 
    if (GetAsyncKeyState('D') || (GetAsyncKeyState(VK_RIGHT) & 0x8000)) return Key::Right;
    else if (GetAsyncKeyState('A') || (GetAsyncKeyState(VK_LEFT) & 0x8000)) return Key::Left;
    else if (GetAsyncKeyState('S') || (GetAsyncKeyState(VK_DOWN) & 0x8000)) return Key::Down;
    else if (GetAsyncKeyState(VK_SPACE)) return Key::Space;
    else return Key::None;

#else
    char c1;
    if (read(STDIN_FILENO, &c1, 1) <= 0) return Key::None;
    else std::cout << "(" << c1 << ")";
    switch (c1)
    {
    case 'd':
    case 'D':
        std::cout << " RIGHT ";
        return Key::Right;

    case 'a':
    case 'A':
        std::cout << " LEFT ";
        return Key::Left;

    case 's':
    case 'S':
        std::cout << " DOWN ";
        return Key::Down;

    case ' ':
        std::cout << " SPACE ";
        return Key::Space;

    default:
        std::cout << " NONE ";
        return Key::None;
    }
#endif
}

