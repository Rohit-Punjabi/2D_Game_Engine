/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: Player.h
Purpose: Tracks and updates variables for the player character
Language: C++, gpp
Platform: gpp
- End Header --------------------------------------------------------*/

#pragma once
#include "math.h"

class Player {
public:
	Player(float xInit, float yInit);
	~Player();

	void Update(int horiz, int vert, float dTime);
	float GetX();
	float GetY();

	void SpeedBoost();



private:
	float mVelHoriz, mVelVert;
	float x, y;
	int mAcceleration, mMaxSpeed;
	float mSlowMod, mExcessSlowMod;
};
