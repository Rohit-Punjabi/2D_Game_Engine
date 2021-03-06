#include "InputManager.h"
#include "memory.h"
#include "SDL_keyboard.h"
#include "SDL_mouse.h"

InputManager::InputManager() : mousePositionX(0), mousePositionY(0), mousePrevious(0), mouseCurrent(0)
{
	memset(mCurrentState, 0, 512 * sizeof(Uint8));
	memset(mPreviousState, 0, 512 * sizeof(Uint8));
}

InputManager::~InputManager() 
{
	//
}

void InputManager::Update() 
{
	int numberOfFetched = 0;
	const Uint8* currentKeyStates = SDL_GetKeyboardState(&numberOfFetched);

	if (numberOfFetched > 512)
		numberOfFetched = 512;

	memcpy(mPreviousState, mCurrentState, numberOfFetched * sizeof(Uint8));
	memcpy(mCurrentState, currentKeyStates, numberOfFetched * sizeof(Uint8));

	// Mouse Stuff
	mousePrevious = mouseCurrent;

	mouseCurrent = SDL_GetMouseState(&mousePositionX, &mousePositionY);
}

bool InputManager::IsKeyPressed(unsigned int KeyScanCode) 
{
	if (KeyScanCode >= 512)
		return false;

	if (mCurrentState[KeyScanCode])
		return true;
	return false;
}

bool InputManager::IsKeyTriggered(unsigned int KeyScanCode) 
{
	if (KeyScanCode >= 512)
		return false;

	if (mCurrentState[KeyScanCode] && !mPreviousState[KeyScanCode])
		return true;
	return false;
}

bool InputManager::IsKeyReleased(unsigned int KeyScanCode) 
{
	if (KeyScanCode >= 512)
		return false;

	if (mPreviousState[KeyScanCode] && !mCurrentState[KeyScanCode])
		return true;
	return false;
}

bool InputManager::mouseIsTriggeredL()
{
	return (static_cast<bool>(mouseCurrent & SDL_BUTTON_LMASK) && !static_cast<bool>(mousePrevious & SDL_BUTTON_LMASK));
}

bool InputManager::mouseIsTriggeredR()
{
	return (static_cast<bool>(mouseCurrent & SDL_BUTTON_RMASK) && !static_cast<bool>(mousePrevious & SDL_BUTTON_RMASK));
}
