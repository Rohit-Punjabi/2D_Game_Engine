#pragma once

#include "Component.h"
#include "..\JSON Parser\include\rapidjson.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

class Transform : public Component
{
public:
	Transform();
	~Transform() {}
	
	void Update() {}

	void Serialize(rapidjson::GenericObject<false, rapidjson::Value::ValueType>);

	void HandleEvent(Event* pEvent);
public:
	float mPositionX, mPositionY;
	float rot;
	glm::vec2 mScale;

private:
private:

};