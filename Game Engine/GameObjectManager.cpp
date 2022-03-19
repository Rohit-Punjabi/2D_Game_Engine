#include "GameObjectManager.h"
#include "GameObject.h"
#include "Component.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
	for (auto pGO : mGameObjects)
		delete pGO;

	mGameObjects.clear();
}

void GameObjectManager::AddGameObject(GameObject* GameObject)
{
	mGameObjects.push_back(GameObject);
}

void GameObjectManager::DeleteGameObjects()
{
	for (int i = 0; i < mGameObjects.size(); ++i)
	{
		if (mGameObjects[i]->isDestroyed)
		{
			GameObject* tempGameobject = mGameObjects[i];
			mGameObjects.erase(mGameObjects.begin() + i);
			delete tempGameobject;
		}
	}
}

void GameObjectManager::ClearVector()
{
	mGameObjects.clear();
}
