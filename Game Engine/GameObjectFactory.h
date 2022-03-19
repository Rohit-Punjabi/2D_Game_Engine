#pragma once


class GameObject;

class GameObjectFactory
{
public:
	GameObjectFactory();
	~GameObjectFactory();

	GameObject* LoadGameObject(const char* pFileName);
	void LoadLevel(const char* pFileName);

public:

private:
private:

};