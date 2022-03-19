#include "GameObjectFactory.h"
#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Controller.h"
#include "UpDown.h"
#include "Sprite.h"
#include "FrameRateController.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "GameObjectManager.h"
#include "EventManager.h"
#include "..\JSON Parser\include\istreamwrapper.h"
#include "..\JSON Parser\include\document.h"
#include "..\JSON Parser\include\filereadstream.h"

extern GameObjectManager* pGameObjectManager;
extern EventManager* pEventManager;


GameObjectFactory::GameObjectFactory()
{
}

GameObjectFactory::~GameObjectFactory()
{
}

GameObject* GameObjectFactory::LoadGameObject(const char* pFileName)
{

	FILE* fp;
	rapidjson::Document document;
	GameObject* pNewGameObject = new GameObject();

	fopen_s(&fp, pFileName, "r");

	char buffer[512] = { 0 };
	rapidjson::FileReadStream FRS(fp, buffer, sizeof(buffer));

	document.ParseStream(FRS);

	if (document.HasMember("Transform"))
	{
		pNewGameObject->AddComponent(TRANSFORM);
		((Transform*)pNewGameObject->GetComponent("Transform"))->Serialize(document["Transform"].GetObject());
	}
	
	if (document.HasMember("Sprite"))
	{
		pNewGameObject->AddComponent(SPRITE);
		((Sprite*)pNewGameObject->GetComponent("Sprite"))->Serialize(document["Sprite"].GetString());
		
	}
	
	if (document.HasMember("Tag"))
	{
		pNewGameObject->Tag = document["Tag"].GetString();
	}

	if (document.HasMember("UpDown"))
	{
		pNewGameObject->AddComponent(UPDOWN);
	}
	
	if (document.HasMember("Controller"))
	{
		pNewGameObject->AddComponent(CONTROLLER);
	}

	pGameObjectManager->AddGameObject(pNewGameObject);
	
	return pNewGameObject;
}

void GameObjectFactory::LoadLevel(const char* pFileName)
{
	FILE* fp;
	rapidjson::Document document;
	GameObject* pTempGameObject = nullptr;

	fopen_s(&fp, pFileName, "r");

	char buffer[512] = { 0 };
	rapidjson::FileReadStream FRS(fp, buffer, sizeof(buffer));

	document.ParseStream(FRS);

	rapidjson::Value& objects = document["objects"];

	for ( unsigned int i = 0; i < objects.Size(); ++i)
	{
		rapidjson::GenericObject<false, rapidjson::Value::ValueType> jsonObject = objects[i].GetObject();
		if (jsonObject.HasMember("Name")) 
		{
			pTempGameObject = LoadGameObject(jsonObject["Name"].GetString());

			if (jsonObject.HasMember("Transform")) 
			{
				((Transform*)pTempGameObject->GetComponent("Transform"))->Serialize(jsonObject["Transform"].GetObject());
			}
			if (jsonObject.HasMember("Sprite")) 
			{
				((Sprite*)pTempGameObject->GetComponent("Sprite"))->Serialize(document["Sprite"].GetString());

			}
		}
	}
}
