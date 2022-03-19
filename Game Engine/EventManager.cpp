#include "EventManager.h"
#include "GameObjectManager.h"
#include "GameObject.h"

extern GameObjectManager* pGameObjectManager;

EventManager::EventManager() {}
EventManager::~EventManager() {}

void EventManager::BroadcastEvent(Event* pEvent)
{
	for (auto pGO : pGameObjectManager->mGameObjects)
	{
		pGO->HandleEvent(pEvent);
	}
}

void EventManager::BroadcastEventToSubscribers(Event* pEvent)
{
	std::list<GameObject*>& listOfSubscribers = mSubscriptions[pEvent->mType];

	for (auto pGO : listOfSubscribers)
	{
		pGO->HandleEvent(pEvent);
	}
}

void EventManager::AddTimedEvent(Event* pEvent)
{
	mEvents.push_back(pEvent);
}

void EventManager::Update(float FrameTime)
{
	std::list<Event*>::iterator it = mEvents.begin();

	while (it != mEvents.end())
	{
		Event* pEvent = *it;

		pEvent->mTimer -= FrameTime;

		if (pEvent->mTimer <= 0.0f)
		{
			BroadcastEvent(pEvent);
			delete pEvent;
			it = mEvents.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void EventManager::Subscribe(EventType Et, GameObject* pGameObject)
{
	std::list<GameObject*>& listOfSubscribers = mSubscriptions[Et];

	for (auto pGO : listOfSubscribers)
	{
		if (pGO == pGameObject)
		{
			return;
		}
	}

	listOfSubscribers.push_back(pGameObject);
}





