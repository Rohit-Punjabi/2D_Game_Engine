#include "FrameRateController.h"
#include "limits.h"
#include <SDL_timer.h>

#ifdef _DEBUG
#include <SDL_log.h>
static Uint32 frameCounter{ 0 };
static Uint32 frameRateTimer{ 0 };
#endif // _DEBUG

FrameRateController::FrameRateController(unsigned int MaxFrameRate) {
	if (MaxFrameRate == 0)
		MaxFrameRate = UINT_MAX;

	mMaxFrameRate = MaxFrameRate;
	mTicksPerFrame = 1000 / mMaxFrameRate;
	mTickStart = 0;
	mTickEnd = 0;
	mFrameTime = 0;
	mDeltaTime = 0.0f;
	mGameTime = 0.0f;
}

FrameRateController::~FrameRateController() {
	//
}

void FrameRateController::FrameStart() 
{
	mTickEnd = SDL_GetTicks();

	mFrameTime = mTickEnd - mTickStart;
	mDeltaTime = (float)mFrameTime / 1000.0f;
	mGameTime += mDeltaTime;

	mTickStart = mTickEnd;
}

void FrameRateController::FrameEnd() 
{
	mTickEnd = SDL_GetTicks();
	if (mTickEnd - mTickStart < mTicksPerFrame)
	{
		SDL_Delay(mTicksPerFrame - (mTickEnd - mTickStart));
	}


//#ifdef _DEBUG
//	++frameCounter;
//	frameRateTimer += mFrameTime;
//	if (frameCounter == 120)
//	{
//		SDL_Log("FrameRate avg (past 120 frames) = %f", 120000/static_cast<float>(frameRateTimer));
//		frameCounter = 0;
//		frameRateTimer = 0;
//	}
//#endif

	//SDL_Log("Game Time = %f", mGameTime);
}

unsigned int FrameRateController::GetFrameTime() 
{
	return mFrameTime;
}

float FrameRateController::GetDeltaTime() 
{
	return mDeltaTime;
}

float FrameRateController::GameTime()
{
	return mGameTime;
}

void FrameRateController::FrameReset()
{
	mTickStart = SDL_GetTicks();
	mTickEnd = SDL_GetTicks();
	mFrameTime = 0;
	mDeltaTime = 0.0f;
	mGameTime = 0.0f;
}
