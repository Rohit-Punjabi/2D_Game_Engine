#pragma once

#include <vector>
#include <unordered_map>

class Component;
class Event;

class GameObject
{
public:
	GameObject();
	~GameObject();

	void Update();
	Component* GetComponent(std::string CompType);
	Component* AddComponent(unsigned int type);

	void HandleEvent(Event* pEvent);


public:
	//std::vector<Component*> mComponents;

	std::unordered_map<std::string, Component*> mComponents;
	std::string Tag;
	bool isDestroyed = false;

private:
private:

};