#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GameObject.h"
#include "GameObjectManager.h"

class Renderer
{
	friend GameObjectManager;
public:
	Renderer(GameObjectManager*);
	~Renderer() {};

	void IntializeTexture();

	void Draw();
	void BuildTransforms(GameObject* GameObject);
	void ApplyTexture(GameObject* gameObject);
	void Toggle();
	void Clear();

private:
	GameObjectManager* mGameObjects;
	glm::mat4 projectionMatrix, modelMatrix;
	GLuint texture;
	int renderMode;
};