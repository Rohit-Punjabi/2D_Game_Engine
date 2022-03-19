#pragma once


#include "..\JSON Parser\include\document.h"
#include <fstream>
#include "GameObject.h"

class GameObject;
class Event;

enum COMPONENT_TYPE
{
	TRANSFORM,
	SPRITE,
	SCALE,
	UPDOWN,
	CONTROLLER,
};

class Component
{
public:
	Component();
	Component(unsigned int type);
	virtual ~Component();

	
	virtual void Update() = 0;

	virtual void Serialize() {}

	unsigned int GetType() { return mType; }

	virtual void HandleEvent(Event* pEvent) {};

public:
	GameObject* mpOwner;

private:
private:
	unsigned int mType;

};