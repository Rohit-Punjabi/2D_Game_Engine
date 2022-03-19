#include "Renderer.h"
#include <SDL.h>
#include <SDL_image.h>
#include <glad/glad.h>
#include"shaderClass.h"
#include "GameObjectManager.h"
#include "Sprite.h"
#include "Transform.h"
#include "InputManager.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

extern Shader* pShader;
extern VAO* pVAO;
extern InputManager* pInputManager;

Renderer::Renderer(GameObjectManager* mGameObj) : mGameObjects(mGameObj), renderMode(0)
{
	projectionMatrix = glm::ortho(0.0f, 750.0f, 750.0f, 0.0f, -1.0f, 1.0f);
	modelMatrix = glm::mat4(1.0f);
	texture = 0;
	IntializeTexture();
}

void Renderer::Draw()
{

	Toggle();
	// Specify the color of the background
	glClearColor(1.0f, 1.0f, 0.0f, 0.0f);
	// Clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);

	for (auto obj : mGameObjects->mGameObjects)
	{
		BuildTransforms(obj);
		ApplyTexture(obj);

		// Tell OpenGL which Shader Program we want to use
		pShader->Activate();

		GLuint uniID = glGetUniformLocation(pShader->ID, "projectionMatrix");
		glUniformMatrix4fv(uniID, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

		uniID = glGetUniformLocation(pShader->ID, "modelMatrix");
		glUniformMatrix4fv(uniID, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		uniID = glGetUniformLocation(pShader->ID, "tex");
		glUniform1i(uniID, texture);

		uniID = glGetUniformLocation(pShader->ID, "renderMode");
		glUniform1i(uniID, renderMode);

		uniID = glGetUniformLocation(pShader->ID, "scale");
		glUniform1f(uniID, 1.5f);

		// Bind the VAO so OpenGL knows to use it
		pVAO->Bind();

		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	
	
}

void Renderer::IntializeTexture()
{
	glGenTextures(0, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Renderer::BuildTransforms(GameObject* GameObject)
{
	Transform* transform = (Transform*)GameObject->GetComponent("Transform");

	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(transform->mPositionX, transform->mPositionY, 0.0f));

	//modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f * (transform->mScale).x, 0.5f * (transform->mScale).y, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(transform->rot), glm::vec3(0.0f, 0.0f, 1.0f));
	//modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5f * (transform->mScale).x, -0.5f * (transform->mScale).y, 0.0f));

	modelMatrix = glm::scale(modelMatrix, glm::vec3(transform->mScale, 0));
}

void Renderer::ApplyTexture(GameObject* gameObject)
{
	Sprite* spriteComp = (Sprite*)gameObject->GetComponent("Sprite");

	void* data = spriteComp->mpSurface->pixels;

	if (data) 
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, spriteComp->mpSurface->w, spriteComp->mpSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
}

void Renderer::Toggle()
{
	if (pInputManager->IsKeyTriggered(SDL_SCANCODE_T))
	{
		renderMode = !renderMode;
	}
}

void Renderer::Clear()
{
}
