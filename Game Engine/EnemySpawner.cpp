#include "EnemySpawner.h"
#include <cstdlib>
#include <stdlib.h>
#include "GameObject.h"
#include "Transform.h"
#include "GameObjectFactory.h"
#include "Component.h"
#include "Sprite.h"
#include "ResourceManager.h"
#include "GameObjectManager.h"

extern GameObject* pGameObject;
extern GameObjectFactory* pGOF;
extern ResourceManager* gpResourceManager;
extern GameObjectManager* pGameObjectManager;

EnemySpawner::EnemySpawner() : highest(0.0f), lowest(0.0f), rand(0.0f)
{
}

EnemySpawner::~EnemySpawner()
{
}

void EnemySpawner::NormalEnemySpawner()
{
	GameObject* nEnemy = new GameObject();
	nEnemy->AddComponent(TRANSFORM);
	nEnemy->AddComponent(SPRITE);
	nEnemy->AddComponent(UPDOWN);
	nEnemy->Tag = "Enemy";
	Sprite* nEnemySprite = (Sprite*)nEnemy->GetComponent("Sprite");
	nEnemySprite->mpSurface = gpResourceManager->LoadSurface("..\\Resources\\sEnemy.png");
	Transform* nEnemyTransform = (Transform*)nEnemy->GetComponent("Transform");
	nEnemyTransform->mPositionX = RandomGenerator(200.0, 550.0);
	nEnemyTransform->mPositionY = -100.0f;
	float scale = RandomGenerator(20.0, 50.0);
	nEnemyTransform->mScale = glm::vec2(scale, scale);
	pGameObjectManager->AddGameObject(nEnemy);
}

void EnemySpawner::FireBallSpawner()
{
	GameObject* nFireBall = new GameObject();
	nFireBall->AddComponent(TRANSFORM);
	nFireBall->AddComponent(SPRITE);
	nFireBall->AddComponent(UPDOWN);
	nFireBall->Tag = "FireBall";
	Sprite* nEnemySprite = (Sprite*)nFireBall->GetComponent("Sprite");
	nEnemySprite->mpSurface = gpResourceManager->LoadSurface("..\\Resources\\sFireBall.png");
	Transform* nEnemyTransform = (Transform*)nFireBall->GetComponent("Transform");
	nEnemyTransform->mPositionX = RandomGenerator(300.0, 450.0);
	nEnemyTransform->mPositionY = -100.0f;
	float scale = RandomGenerator(80.0, 130.0);
	nEnemyTransform->mScale = glm::vec2(scale, scale);
	pGameObjectManager->AddGameObject(nFireBall);
}

void EnemySpawner::WallSpawner()
{
	float rand = RandomGenerator(0, 2);

	if (rand > 0 && rand < 1)
	{
		GameObject* nWall = new GameObject();
		nWall->AddComponent(TRANSFORM);
		nWall->AddComponent(SPRITE);
		nWall->AddComponent(UPDOWN);
		nWall->Tag = "WallSideR";
		Sprite* nEnemySprite = (Sprite*)nWall->GetComponent("Sprite");
		nEnemySprite->mpSurface = gpResourceManager->LoadSurface("..\\Resources\\sWall.png");
		Transform* nEnemyTransform = (Transform*)nWall->GetComponent("Transform");
		nEnemyTransform->mPositionX = 565.0f;
		nEnemyTransform->mPositionY = -100.0f;
		float scale = RandomGenerator(50.0, 200.0);
		nEnemyTransform->mScale.x = 50.0f;
		nEnemyTransform->mScale.y = scale;
		pGameObjectManager->AddGameObject(nWall);
	}
	else
	{
		GameObject* nWall = new GameObject();
		nWall->AddComponent(TRANSFORM);
		nWall->AddComponent(SPRITE);
		nWall->AddComponent(UPDOWN);
		nWall->Tag = "WallSideR";
		Sprite* nEnemySprite = (Sprite*)nWall->GetComponent("Sprite");
		nEnemySprite->mpSurface = gpResourceManager->LoadSurface("..\\Resources\\sWall.png");
		Transform* nEnemyTransform = (Transform*)nWall->GetComponent("Transform");
		nEnemyTransform->mPositionX = 565.0f;
		nEnemyTransform->mPositionY = -100.0f;
		float scale = RandomGenerator(50.0, 200.0);
		nEnemyTransform->mScale.x = 50.0f;
		nEnemyTransform->mScale.y = scale;
		pGameObjectManager->AddGameObject(nWall);
	}
	
}

float EnemySpawner::RandomGenerator(float lowest, float highest)
{
	return lowest + static_cast <float> (std::rand() / (static_cast <float> (RAND_MAX / (highest - lowest))));
}
