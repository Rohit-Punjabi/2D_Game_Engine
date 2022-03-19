/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: InputManager.h
Purpose: Handles game inputs
Language: C++, gpp
Platform: gpp
- End Header --------------------------------------------------------*/

#pragma once

#include "SDL_stdinc.h"

class InputManager
{
public:
	InputManager();
	~InputManager();

	void Update();
	bool IsKeyPressed(unsigned int KeyScanCode);
	bool IsKeyTriggered(unsigned int KeyScanCode);
	bool IsKeyReleased(unsigned int KeyScanCode);

	bool mouseIsTriggeredL();
	bool mouseIsTriggeredR();
public:



private:
private:
	Uint8 mCurrentState[512];
	Uint8 mPreviousState[512];
	int mousePositionX, mousePositionY;
	Uint32 mousePrevious;
	Uint32 mouseCurrent;

};
