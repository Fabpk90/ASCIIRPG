#pragma once

#include <Windows.h>

class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	DWORD getInput(INPUT_RECORD **eventBuffer);
};

