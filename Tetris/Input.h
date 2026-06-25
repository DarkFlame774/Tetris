#pragma once
#include "Terminal.h"

enum Key {None,Right,Left,Down,Space};

class Input {
	public:
		static Key GetKey();
};
Key PollInput();