#pragma once

#include <vector>

class GameObject;

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void AddGameObject(GameObject* GameObject);

	void DeleteGameObjects();

	void ClearVector();

public:
	std::vector<GameObject* > mGameObjects;

private:
private:

};