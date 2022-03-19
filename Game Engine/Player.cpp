#include "Player.h"

Player::Player(float xInit, float yInit) 
{
	x = xInit;
	y = yInit;

	mVelHoriz = 0.0f;
	mVelVert = 0.0f;

	mAcceleration = 1200;
	mMaxSpeed = 200;

	mSlowMod = 0.25;
	mExcessSlowMod = 2.0f;
}

Player::~Player() 
{
	//
}

void Player::Update(int horiz, int vert, float dTime) 
{

	/*** Horiz ***/
	mVelHoriz += mAcceleration * horiz * dTime;


	/*** Vert ***/
	mVelVert += mAcceleration * vert * dTime;


	/*** Slowing ***/
	float ang = atan2f(mVelVert, mVelHoriz);
	if (mVelHoriz != 0) {
		if (fabsf(mVelHoriz) - fabsf(mAcceleration * cosf(ang) * mSlowMod * dTime) <= 0) {
			mVelHoriz = 0;
		}
		else {
			mVelHoriz -= mAcceleration * cosf(ang) * mSlowMod * dTime;
		}
	}

	if (mVelVert != 0) {
		if (fabsf(mVelVert) - fabsf(mAcceleration * sinf(ang) * mSlowMod * dTime) <= 0) {
			mVelVert = 0;
		}
		else {
			mVelVert -= mAcceleration * sinf(ang) * mSlowMod * dTime;
		}
	}

	float sqVel = (mVelHoriz * mVelHoriz + mVelVert * mVelVert) / (mMaxSpeed * mMaxSpeed);
	if (sqVel > 1.0f) {
		if (sqrtf(mVelHoriz * mVelHoriz + mVelVert * mVelVert) - mAcceleration * mExcessSlowMod * dTime <= mMaxSpeed) {
			mVelHoriz /= sqVel;
			mVelVert /= sqVel;
		}
		else {
			mVelHoriz -= mAcceleration * cosf(ang) * mExcessSlowMod * dTime;
			mVelVert -= mAcceleration * sinf(ang) * mExcessSlowMod * dTime;
		}
	}

	
	/*** Final Position ***/
	x += mVelHoriz * dTime;
	y += mVelVert * dTime;

}

void Player::SpeedBoost() 
{
	mVelHoriz = 2000;
}

float Player::GetX() 
{
	return x;
}

float Player::GetY() 
{
	return y;
}
