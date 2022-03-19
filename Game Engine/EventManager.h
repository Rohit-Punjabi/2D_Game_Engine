#pragma once

#include <list>
#include <unordered_map>

class GameObject;

enum class EventType
{
	BULLET,
	SUBEVENT,

	NUM
};

class Event
{
public:
	Event(EventType Type)
	{
		mType = Type;
		mTimer = 0.0f;
	}
	virtual ~Event() {}

public:
	EventType mType;
	float mTimer;
};

class EventManager
{
public:
	EventManager();
	~EventManager();

	void BroadcastEvent(Event* pEvent);
	void BroadcastEventToSubscribers(Event* pEvent);
	void AddTimedEvent(Event* pEvent);
	void Update(float FrameTime);

	void Subscribe(EventType Et, GameObject* pGameObject);

public:
	std::list<Event*>mEvents;

	std::unordered_map<EventType, std::list<GameObject*>> mSubscriptions;
};
