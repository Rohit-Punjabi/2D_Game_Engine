#pragma once

#include "Component.h"

class GameObject;
struct SDL_Surface;

class UpDown : public Component
{
public:
	UpDown();
	~UpDown();

	void Update();
	void Serialize() {};

public:
	bool mGoingUp;
	int mTimer, mTimerLimit;

private:
private:

};
