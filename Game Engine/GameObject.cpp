#include "GameObject.h"

#include "Sprite.h"
#include "Transform.h"
#include "Controller.h"
#include "UpDown.h"
#include "Component.h"


GameObject::GameObject()
{
}

GameObject::~GameObject()
{
	for (auto i = mComponents.begin(); i != mComponents.end(); ++i) 
	{
		delete i->second;
	}
	mComponents.clear();
}

void GameObject::Update()
{
	for (auto i = mComponents.begin(); i != mComponents.end(); ++i)
	{
		i->second->Update();
	}
}

Component* GameObject::GetComponent(std::string CompType)
{
	if (mComponents.find(CompType) == mComponents.end()) 
	{
		return nullptr;
	}
	return mComponents[CompType];
}

Component* GameObject::AddComponent(unsigned int type)
{
	Component* pNewComponent = nullptr;

	if (pNewComponent == nullptr)
	{
		switch (type)
		{
		case TRANSFORM:
			pNewComponent = new Transform();
			mComponents["Transform"] = pNewComponent;
			break;

		case SPRITE:
			pNewComponent = new Sprite();
			mComponents["Sprite"] = pNewComponent;
			break;

		case UPDOWN:
			pNewComponent = new UpDown();
			mComponents["UpDown"] = pNewComponent;
			break;

		case CONTROLLER:
			pNewComponent = new Controller();
			mComponents["Controller"] = pNewComponent;
			break;


		}
		pNewComponent->mpOwner = this;
	}

	return pNewComponent;
}

void GameObject::HandleEvent(Event* pEvent)
{
	for (auto i = mComponents.begin(); i != mComponents.end(); ++i)
	{
		i->second->HandleEvent(pEvent);
	}
}
