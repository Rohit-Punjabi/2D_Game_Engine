#pragma once

#include "Component.h"
#include <SDL_video.h>
#include <string.h>

class GameObject;
struct SDL_Surface;

class Sprite : public Component
{
public:
	Sprite();
	~Sprite();

	void Update();
	void Serialize(std::string object);

public:
	SDL_Surface* mpSurface;
	float mHeight, mWidth;

private:
private:

};