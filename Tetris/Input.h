#pragma once
#include "Terminal.h"

enum Key {Right,Left,Down,Up,Space};

class Input {
	public:
		static bool GetKeyState(Key key);
};
bool HandleInput(Key key);