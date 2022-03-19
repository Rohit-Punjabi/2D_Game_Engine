#include "CollisionManager.h"
#include "GameObjectManager.h"
#include "Component.h"
#include "Transform.h"
#include <SDL_log.h>

extern GameObjectManager* pGameObjectManager;

CollisionManager::CollisionManager() : Collision(false), EnemyLeftCounter(0)
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::Update()
{
	for (int i = 0; i < pGameObjectManager->mGameObjects.size(); ++i)
	{
		if (pGameObjectManager->mGameObjects[i]->Tag == "Player")
		{
			Transform* nPlayerTransform = (Transform*)pGameObjectManager->mGameObjects[i]->GetComponent("Transform");
			float PposX = nPlayerTransform->mPositionX;
			float PposY = nPlayerTransform->mPositionY;
			float Pwidth = nPlayerTransform->mScale.x;
			float Pheight = nPlayerTransform->mScale.y;

			for (int j = 0; j < pGameObjectManager->mGameObjects.size(); ++j)
			{
				if (pGameObjectManager->mGameObjects[j]->Tag == "Enemy")
				{
					Transform* nEnemyTransform = (Transform*)pGameObjectManager->mGameObjects[j]->GetComponent("Transform");
					float EposX = nEnemyTransform->mPositionX;
					float EosY = nEnemyTransform->mPositionY;
					float Ewidth = nEnemyTransform->mScale.x;
					float Eheight = nEnemyTransform->mScale.y;

					if (CollisionDetector(PposX, PposY, Pwidth, Pheight, EposX, EosY, Ewidth, Eheight))
					{
						pGameObjectManager->mGameObjects[j]->isDestroyed = true;
						pGameObjectManager->mGameObjects[i]->isDestroyed = true;
						Collision = true;
					}
				}

				if (pGameObjectManager->mGameObjects[j]->Tag == "Wall")
				{
					Transform* nWallTransform = (Transform*)pGameObjectManager->mGameObjects[j]->GetComponent("Transform");
					float EposX = nWallTransform->mPositionX;
					float EosY = nWallTransform->mPositionY;
					float Ewidth = nWallTransform->mScale.x;
					float Eheight = nWallTransform->mScale.y;

					if (CollisionDetector(PposX, PposY, Pwidth, Pheight, EposX, EosY, Ewidth, Eheight))
					{
						pGameObjectManager->mGameObjects[j]->isDestroyed = true;
						pGameObjectManager->mGameObjects[i]->isDestroyed = true;
						Collision = true;
					}
				}

				if (pGameObjectManager->mGameObjects[j]->Tag == "WallSideR")
				{
					Transform* nWallSideTransform = (Transform*)pGameObjectManager->mGameObjects[j]->GetComponent("Transform");
					float EposX = nWallSideTransform->mPositionX;
					float EosY = nWallSideTransform->mPositionY;
					float Ewidth = nWallSideTransform->mScale.x;
					float Eheight = nWallSideTransform->mScale.y;

					if (CollisionDetector(PposX, PposY, Pwidth, Pheight, EposX, EosY, Ewidth, Eheight))
					{
						pGameObjectManager->mGameObjects[j]->isDestroyed = true;
						pGameObjectManager->mGameObjects[i]->isDestroyed = true;
						Collision = true;
					}
				}

				if (pGameObjectManager->mGameObjects[j]->Tag == "FireBall")
				{
					Transform* nEnemyTransform = (Transform*)pGameObjectManager->mGameObjects[j]->GetComponent("Transform");
					float EposX = nEnemyTransform->mPositionX;
					float EosY = nEnemyTransform->mPositionY;
					float Ewidth = nEnemyTransform->mScale.x;
					float Eheight = nEnemyTransform->mScale.y;

					if (CollisionDetector(PposX, PposY, Pwidth, Pheight, EposX, EosY, Ewidth, Eheight))
					{
						pGameObjectManager->mGameObjects[j]->isDestroyed = true;
						pGameObjectManager->mGameObjects[i]->isDestroyed = true;
						Collision = true;
					}
				}
			}
		}

		if (pGameObjectManager->mGameObjects[i]->Tag == "Bullet")
		{
			Transform* nBulletTransform = (Transform*)pGameObjectManager->mGameObjects[i]->GetComponent("Transform");
			float BposX = nBulletTransform->mPositionX;
			float BposY = nBulletTransform->mPositionY;
			float Bwidth = nBulletTransform->mScale.x;
			float Bheight = nBulletTransform->mScale.y;

			for (int j = 0; j < pGameObjectManager->mGameObjects.size(); ++j)
			{
				if (pGameObjectManager->mGameObjects[j]->Tag == "Enemy")
				{
					Transform* nEnemyTransform = (Transform*)pGameObjectManager->mGameObjects[j]->GetComponent("Transform");
					float EposX = nEnemyTransform->mPositionX;
					float EosY = nEnemyTransform->mPositionY;
					float Ewidth = nEnemyTransform->mScale.x;
					float Eheight = nEnemyTransform->mScale.y;

					if (CollisionDetector(BposX, BposY, Bwidth, Bheight, EposX, EosY, Ewidth, Eheight))
					{
						pGameObjectManager->mGameObjects[j]->isDestroyed = true;
						pGameObjectManager->mGameObjects[i]->isDestroyed = true;
					}
				}

				if (pGameObjectManager->mGameObjects[j]->Tag == "WallSideR")
				{
					Transform* nWallSideTransform = (Transform*)pGameObjectManager->mGameObjects[j]->GetComponent("Transform");
					float EposX = nWallSideTransform->mPositionX;
					float EosY = nWallSideTransform->mPositionY;
					float Ewidth = nWallSideTransform->mScale.x;
					float Eheight = nWallSideTransform->mScale.y;

					if (CollisionDetector(BposX, BposY, Bwidth, Bheight, EposX, EosY, Ewidth, Eheight))
					{
						pGameObjectManager->mGameObjects[i]->isDestroyed = true;
					}
				}
			}
		}

		if (pGameObjectManager->mGameObjects[i]->Tag == "WallSideR")
		{
			Transform* nBulletTransform = (Transform*)pGameObjectManager->mGameObjects[i]->GetComponent("Transform");
			float BposX = nBulletTransform->mPositionX;
			float BposY = nBulletTransform->mPositionY;
			float Bwidth = nBulletTransform->mScale.x;
			float Bheight = nBulletTransform->mScale.y;

			for (int j = 0; j < pGameObjectManager->mGameObjects.size(); ++j)
			{
				if (pGameObjectManager->mGameObjects[j]->Tag == "Enemy")
				{
					Transform* nEnemyTransform = (Transform*)pGameObjectManager->mGameObjects[j]->GetComponent("Transform");
					float EposX = nEnemyTransform->mPositionX;
					float EosY = nEnemyTransform->mPositionY;
					float Ewidth = nEnemyTransform->mScale.x;
					float Eheight = nEnemyTransform->mScale.y;

					if (CollisionDetector(BposX, BposY, Bwidth, Bheight, EposX, EosY, Ewidth, Eheight))
					{
						pGameObjectManager->mGameObjects[j]->isDestroyed = true;
					}
				}

				if (pGameObjectManager->mGameObjects[j]->Tag == "Lazer")
				{
					Transform* nEnemyTransform = (Transform*)pGameObjectManager->mGameObjects[j]->GetComponent("Transform");
					float EposX = nEnemyTransform->mPositionX;
					float EosY = nEnemyTransform->mPositionY;
					float Ewidth = nEnemyTransform->mScale.x;
					float Eheight = nEnemyTransform->mScale.y;

					if (CollisionDetector(BposX, BposY, Bwidth, Bheight, EposX, EosY, Ewidth, Eheight))
					{
						pGameObjectManager->mGameObjects[j]->isDestroyed = true;
					}
				}
			}
		}

		if (pGameObjectManager->mGameObjects[i]->Tag == "Lazer")
		{
			Transform* nBulletTransform = (Transform*)pGameObjectManager->mGameObjects[i]->GetComponent("Transform");
			float BposX = nBulletTransform->mPositionX;
			float BposY = nBulletTransform->mPositionY;
			float Bwidth = nBulletTransform->mScale.x;
			float Bheight = nBulletTransform->mScale.y;

			for (int j = 0; j < pGameObjectManager->mGameObjects.size(); ++j)
			{
				if (pGameObjectManager->mGameObjects[j]->Tag == "Enemy")
				{
					Transform* nEnemyTransform = (Transform*)pGameObjectManager->mGameObjects[j]->GetComponent("Transform");
					float EposX = nEnemyTransform->mPositionX;
					float EosY = nEnemyTransform->mPositionY;
					float Ewidth = nEnemyTransform->mScale.x;
					float Eheight = nEnemyTransform->mScale.y;

					if (CollisionDetector(BposX, BposY, Bwidth, Bheight, EposX, EosY, Ewidth, Eheight))
					{
						pGameObjectManager->mGameObjects[j]->isDestroyed = true;
					}
				}
				if (pGameObjectManager->mGameObjects[j]->Tag == "WallSideR")
				{
					Transform* nEnemyTransform = (Transform*)pGameObjectManager->mGameObjects[j]->GetComponent("Transform");
					float EposX = nEnemyTransform->mPositionX;
					float EosY = nEnemyTransform->mPositionY;
					float Ewidth = nEnemyTransform->mScale.x;
					float Eheight = nEnemyTransform->mScale.y;

					if (CollisionDetector(BposX, BposY, Bwidth, Bheight, EposX, EosY, Ewidth, Eheight))
					{
						pGameObjectManager->mGameObjects[i]->isDestroyed = true;
					}
				}
			}
		}

		if (pGameObjectManager->mGameObjects[i]->Tag == "Enemy")
		{
			Transform* nEnemyTransform = (Transform*)pGameObjectManager->mGameObjects[i]->GetComponent("Transform");
			if (nEnemyTransform->mPositionY > 800)
			{
				++EnemyLeftCounter;
				SDL_Log("Enemy Passed = %d", EnemyLeftCounter);
			}
		}
	}
}

bool CollisionManager::CollisionDetector(float Fposx, float Fposy, float Fwidth, float Fheight, float Sposx, float Sposy, float Swidth, float Sheight)
{

	if (Fposx - Fwidth / 2 <= Sposx + Swidth / 2 &&
		Sposx - Swidth / 2 <= Fposx + Fwidth / 2 &&
		Fposy + Fheight / 2 >=Sposy - Sheight / 2 &&
		Sposy + Sheight / 2 >= Fposy - Fheight / 2)
	{
		return true;
	}
	return false;
}

bool CollisionManager::GetCollisionState()
{
	return Collision;
}

void CollisionManager::CollisionReset()
{
	Collision = false;
	ResetCounter();
}

int CollisionManager::GetEnemyLeftCounter()
{
	return EnemyLeftCounter;
}

void CollisionManager::ResetCounter()
{
	EnemyLeftCounter = 0;
}


