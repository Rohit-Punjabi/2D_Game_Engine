#include "Controller.h"
#include "InputManager.h"
#include "FrameRateController.h"
#include "SDL.h"
#include "Transform.h"
#include "EventManager.h"
#include "GameObjectFactory.h"
#include "GameObjectManager.h"

extern InputManager* pInputManager;
extern FrameRateController* gpFRC;
extern EventManager* pEventManager;
extern GameObjectManager* pGameObjectManager;
extern GameObjectFactory* pGOF;

Controller::Controller() 
{
}

Controller::~Controller()
{
}

void Controller::Update()
{
	Transform* pT = static_cast<Transform*>(mpOwner->GetComponent("Transform"));

	if(pInputManager->IsKeyPressed(SDL_SCANCODE_UP) || pInputManager->IsKeyPressed(SDL_SCANCODE_W))
	{
		pT->mPositionY -= 200 * gpFRC->GetDeltaTime();
	}
	if (pInputManager->IsKeyPressed(SDL_SCANCODE_DOWN) || pInputManager->IsKeyPressed(SDL_SCANCODE_S)) 
	{
		if (pT->mPositionY > 720)
		{
			return;
		}
		else
		{
			pT->mPositionY += 200 * gpFRC->GetDeltaTime();
		}
	}
	if (pInputManager->IsKeyPressed(SDL_SCANCODE_LEFT) || pInputManager->IsKeyPressed(SDL_SCANCODE_A)) 
	{
		pT->mPositionX -= 225 * gpFRC->GetDeltaTime();
	}
	if (pInputManager->IsKeyPressed(SDL_SCANCODE_RIGHT) || pInputManager->IsKeyPressed(SDL_SCANCODE_D))
	{
		pT->mPositionX += 225 * gpFRC->GetDeltaTime();
	}

	if (pInputManager->IsKeyTriggered(SDL_SCANCODE_3))
	{
		Event* event = new Event(EventType::SUBEVENT);
		pEventManager->BroadcastEventToSubscribers(event);
	}
}
