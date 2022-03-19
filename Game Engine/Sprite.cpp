#include "Sprite.h"
#include "..\Game Engine\ResourceManager.h"
#include "SDL_Surface.h"
#include "Component.h"
#include "Transform.h"

extern ResourceManager* gpResourceManager;
extern SDL_Window* pWindow;

Sprite::Sprite() : Component(SPRITE), mHeight(100.0f), mWidth(100.0f)
{
	mpSurface = nullptr;
}

Sprite::~Sprite()
{

}

void Sprite::Update()
{
	SDL_Rect destRect;
	Transform* newTrans = static_cast <Transform* >(mpOwner->GetComponent("Transform"));
	destRect.x = newTrans->mPositionX;
	destRect.y = newTrans->mPositionY;
	//SDL_BlitSurface(mpSurface, NULL, SDL_GetWindowSurface(pWindow), &destRect);
}

void Sprite::Serialize(std::string object)
{
	mpSurface = gpResourceManager->LoadSurface(object.c_str());
}
