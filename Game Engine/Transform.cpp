#include "Transform.h"
#include "EventManager.h"
#include "Sprite.h"
#include "ResourceManager.h"
#include "GameObjectManager.h"

extern ResourceManager* gpResourceManager;
extern GameObjectManager* pGameObjectManager;

Transform::Transform() : Component(TRANSFORM), mPositionX(0.0f), mPositionY(0.0f), rot(0.0f), mScale(0.0f, 0.0f)
{}

void Transform::Serialize(rapidjson::GenericObject<false, rapidjson::Value::ValueType> Object) 
{
	if (Object.HasMember("posx"))
	{
		mPositionX = Object["posx"].GetFloat();
	}
	if (Object.HasMember("posy"))
	{
		mPositionY = Object["posy"].GetFloat();
	}
	if (Object.HasMember("scaleX"))
	{
		mScale.x = Object["scaleX"].GetFloat();
	}
	if (Object.HasMember("scaleY"))
	{
		mScale.y = Object["scaleY"].GetFloat();
	}
}

void Transform::HandleEvent(Event* pEvent)
{}
