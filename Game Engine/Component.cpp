#include "Component.h"

Component::Component()
{
}

Component::Component(unsigned int type)
{
	mType = type;
	mpOwner = nullptr;
}

Component::~Component()
{}
