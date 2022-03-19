#include "UpDown.h"
#include "..\Game Engine\FrameRateController.h"
#include "..\Game Engine\GameObject.h"
#include "Transform.h"
#include "GameObjectManager.h"
#include <SDL_log.h>


extern FrameRateController* gpFRC;
extern GameObjectManager* pGameObjectManager;


UpDown::UpDown() : Component(UPDOWN)
{
	mGoingUp = false;
	mTimerLimit = 1000;
	mTimer = mTimerLimit;
}

UpDown::~UpDown()
{
}

void UpDown::Update()
{
	mTimer -= gpFRC->GetFrameTime();
	float time = gpFRC->GameTime();

	if ( mTimer <= 0)
	{
		mGoingUp = !mGoingUp;
		mTimer = mTimerLimit;
	}

	Transform* pT = (Transform*)(mpOwner->GetComponent("Transform"));
	if (mpOwner->Tag == "FireBall")
	{
		pT->mPositionY += 4.5f * 100.0f * gpFRC->GetDeltaTime();
	}
	else if (mpOwner->Tag == "Bullet")
	{
		pT->mPositionY -= 10.5f * 100.0f * gpFRC->GetDeltaTime();
	}
	else if (mpOwner->Tag == "Lazer")
	{
		pT->mPositionY -= 1.5f * 100.0f * gpFRC->GetDeltaTime();
		pT->rot += 500.0f * gpFRC->GetDeltaTime();
	}
	else if (mpOwner->Tag == "WallSideR")
	{
		pT->mPositionY += 1.5f * 100.0f * gpFRC->GetDeltaTime();
	}
	else if (NULL != pT)
	{
		if (time > 60  && time < 120)
		{
			pT->mPositionY += 1.75f * 100.0f * gpFRC->GetDeltaTime();
			pT->rot += 20.0f * gpFRC->GetDeltaTime();
		}
		else if (time > 120 && time < 180)
		{
			pT->mPositionY += 2.0f * 100.0f * gpFRC->GetDeltaTime();
			pT->rot += 20.0f * gpFRC->GetDeltaTime();
		}
		else if (time > 180 && time < 240)
		{
			pT->mPositionY += 2.25f * 100.0f * gpFRC->GetDeltaTime();
			pT->rot += 20.0f * gpFRC->GetDeltaTime();
		}
		else
		{
			pT->mPositionY += 1.5f * 100.0f * gpFRC->GetDeltaTime();
			pT->rot += 20.0f * gpFRC->GetDeltaTime();
		}
	}

	for (int i = 0; i < pGameObjectManager->mGameObjects.size(); ++i)
	{
		if (pGameObjectManager->mGameObjects[i]->Tag == "Enemy")
		{
			Transform* nEnemyTransform = (Transform*)pGameObjectManager->mGameObjects[i]->GetComponent("Transform");
			if (nEnemyTransform->mPositionY > 800)
			{
				pGameObjectManager->mGameObjects[i]->isDestroyed = true;
			}
		}

		if (pGameObjectManager->mGameObjects[i]->Tag == "Lazer")
		{
			Transform* nEnemyTransform = (Transform*)pGameObjectManager->mGameObjects[i]->GetComponent("Transform");
			if (nEnemyTransform->mScale.y > 50)
			{
				pGameObjectManager->mGameObjects[i]->isDestroyed = true;
			}
		}

		if (pGameObjectManager->mGameObjects[i]->Tag == "Bullet")
		{
			Transform* nBulletTransform = (Transform*)pGameObjectManager->mGameObjects[i]->GetComponent("Transform");
			if (nBulletTransform->mPositionY < 0)
			{
				pGameObjectManager->mGameObjects[i]->isDestroyed = true;
			}
		}

		if (pGameObjectManager->mGameObjects[i]->Tag == "WallSideR")
		{
			Transform* nBulletTransform = (Transform*)pGameObjectManager->mGameObjects[i]->GetComponent("Transform");
			if (nBulletTransform->mPositionY > 850)
			{
				pGameObjectManager->mGameObjects[i]->isDestroyed = true;
			}
		}
	}
}
