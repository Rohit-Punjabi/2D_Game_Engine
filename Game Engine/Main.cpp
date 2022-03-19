#include <SDL.h>
#include <SDL_image.h>
#include <glad/glad.h>
#include "stdio.h"

#include "Windows.h"

#include "InputManager.h"
#include "FrameRateController.h"
#include "ResourceManager.h"
#include "Player.h"
#include "GameObjectManager.h"
#include "GameObjectFactory.h"
#include "GameObject.h"
#include "Renderer.h"
#include "EventManager.h"
#include "Component.h"
#include "EnemySpawner.h"
#include "CollisionManager.h"
#include "UpDown.h"
#include "Sprite.h"

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include "Transform.h"


GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
	-0.5f,  0.5f, 0.0f,     0.0f, 0.12f, 0.0f,	0.0f, 1.0f, // Upper left corner
	 0.5f,  0.5f, 0.0f,     0.0f, 0.25f, 1.0f,	1.0f, 1.0f, // Upper right corner
	 0.5f, -0.5f, 0.0f,     0.4f, 0.7f, 1.0f,	1.0f, 0.0f  // Lower right corner
};

// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1, // Upper triangle
	0, 3, 2 // Lower triangle
};


FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}

#pragma comment(lib, "legacy_stdio_definitions.lib")

SDL_Window* pWindow;
InputManager* pInputManager;
FrameRateController* gpFRC;
ResourceManager* gpResourceManager;
GameObjectManager* pGameObjectManager;
GameObjectFactory* pGOF;
GameObject* pGameObject;
Renderer* pRenderer;
Shader* pShader;
VAO* pVAO;
EventManager* pEventManager;
EnemySpawner* pEnemySpawner;
CollisionManager* pCollisionManager;
UpDown* pUpDown;

int main(int argc, char* args[])
{
	if (AllocConsole())
	{
		FILE* file;

		freopen_s(&file, "CONOUT$", "wt", stdout);
		freopen_s(&file, "CONOUT$", "wt", stderr);
		freopen_s(&file, "CONOUT$", "wt", stdin);

		SetConsoleTitle(L"SDL 2.0 Test");
	}
	
	int error = 0;
	bool appIsRunning = true;
	bool HomeScreen = true;
	bool gameState = false;
	bool LoadLevel = false;
	bool ControlMenu = false;
	bool ControlMenuLoader = false, LoadDeadMenu = false, DeadMenu = false;
	SDL_Surface* pWindowSurface = NULL;

	SDL_Surface* pImageSurface = NULL;

	pInputManager = new InputManager();
	gpFRC = new FrameRateController(60);
	gpResourceManager = new ResourceManager();
	pGameObjectManager = new GameObjectManager();
	pGOF = new GameObjectFactory();
	pGameObject = new GameObject();
	pEventManager = new EventManager();
	pCollisionManager = new CollisionManager();
	pUpDown = new UpDown();

	// Initialize SDL
	if((error = SDL_Init( SDL_INIT_VIDEO )) < 0 )
	{
		printf("Couldn't initialize SDL, error %i\n", error);
		return 1;
	}


	pWindow = SDL_CreateWindow("SDL2 window",		// window title
		SDL_WINDOWPOS_UNDEFINED,					// initial x position
		SDL_WINDOWPOS_UNDEFINED,					// initial y position
		750,										// width, in pixels
		750,										// height, in pixels
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	// Check that the window was successfully made
	if (NULL == pWindow)
	{
		// In the event that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	// Initializing SDL Image
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		std::cout << "Could not create window: " << IMG_GetError() << std::endl;
		return 1;
	}

	if (NULL == pImageSurface)
	{
		std::cout << "SDL could not load image! SDL Error: " << SDL_GetError() << std::endl;
	}

	// OpenGL context
	SDL_GLContext glContext = SDL_GL_CreateContext(pWindow);
	SDL_GL_MakeCurrent(pWindow, glContext);

	/////////////////////////////////////////////////////////
	// Graphics Stuff
	////////////////////////////////////////////////////////
	// Loading OpenGL through glad
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		printf("Failed to initialize GLAD\n");
		return 1;
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	//Shader shaderProgram("default.vert", "default.frag");
	pShader = new Shader("default.vert", "default.frag");

	// Generates Vertex Array Object and binds it
	pVAO = new VAO;
	pVAO->Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	pVAO->LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	pVAO->LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	pVAO->LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	pVAO->Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	pRenderer = new Renderer(pGameObjectManager);

	

	//////////////////////////////////////////////////////////////////
	//End of Graphics Stuff
	/////////////////////////////////////////////////////////////////

	
	
	int spawnTimer = 10, wallSpawnTimer = 10, FireballSpawnTimer = 100, LazerUseTime = 0;

	// Game loop
	while(true == appIsRunning)
	{
		pGameObjectManager->ClearVector();
		pGOF->LoadGameObject("..\\JSON Files\\MainMenu.json");

		while (HomeScreen)
		{
			
			SDL_Event e;
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					appIsRunning = false;
				}
			} // done with handling events

			pRenderer->Draw();
			SDL_GL_SwapWindow(pWindow);

			pInputManager->Update();

			// Behaviour Updates
			if (pInputManager->IsKeyPressed(SDL_SCANCODE_ESCAPE))
			{
				appIsRunning = false;
				HomeScreen = false;
			}

			// Behaviour Updates
			if (pInputManager->IsKeyPressed(SDL_SCANCODE_P))
			{
				HomeScreen = false;
				gameState = true;
				LoadLevel = true;
				for (int i = 0; i < pGameObjectManager->mGameObjects.size(); ++i)
				{
					if (pGameObjectManager->mGameObjects[i]->Tag == "MainMenu")
					{
						pGameObjectManager->mGameObjects[i]->isDestroyed = true;
					}
				}
			}

			if (pInputManager->IsKeyPressed(SDL_SCANCODE_C))
			{
				HomeScreen = false;
				ControlMenu = true;
				ControlMenuLoader = true;
				for (int i = 0; i < pGameObjectManager->mGameObjects.size(); ++i)
				{
					if (pGameObjectManager->mGameObjects[i]->Tag == "PlayButton")
					{
						pGameObjectManager->mGameObjects[i]->isDestroyed = true;
					}

					if (pGameObjectManager->mGameObjects[i]->Tag == "Title")
					{
						pGameObjectManager->mGameObjects[i]->isDestroyed = true;
					}

					if (pGameObjectManager->mGameObjects[i]->Tag == "ControlsButton")
					{
						pGameObjectManager->mGameObjects[i]->isDestroyed = true;
					}
				}
			}
			pGameObjectManager->DeleteGameObjects();
		}

		while (ControlMenuLoader)
		{
			pGOF->LoadGameObject("..\\JSON Files\\ControlsScreen.json");
			ControlMenuLoader = false;
		}
		
		while (ControlMenu)
		{
			SDL_Event e;
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					appIsRunning = false;
				}
			} // done with handling events

			pRenderer->Draw();
			SDL_GL_SwapWindow(pWindow);

			pInputManager->Update();


			// Behaviour Updates
			if (pInputManager->IsKeyPressed(SDL_SCANCODE_BACKSPACE))
			{
				ControlMenu = false;
				HomeScreen = true;
				for (int i = 0; i < pGameObjectManager->mGameObjects.size(); ++i)
				{
					if (pGameObjectManager->mGameObjects[i]->Tag == "ControlsScreen")
					{
						pGameObjectManager->mGameObjects[i]->isDestroyed = true;
					}

					if (pGameObjectManager->mGameObjects[i]->Tag == "BackButton")
					{
						pGameObjectManager->mGameObjects[i]->isDestroyed = true;
					}
				}
			}
			pGameObjectManager->DeleteGameObjects();

		}

		if (LoadLevel)
		{
			gpFRC->FrameReset();
			pCollisionManager->CollisionReset();
			pGOF->LoadLevel("..\\JSON Files\\Level1.json");
			LoadLevel = false;
		}

		while (gameState)
		{
			// Get the time at the start of the frame
			gpFRC->FrameStart();

			if (pCollisionManager->GetCollisionState())
			{
				for (int i = 0; i < pGameObjectManager->mGameObjects.size(); ++i)
				{
					pGameObjectManager->mGameObjects[i]->isDestroyed = true;
				}
				gameState = false;
				LoadDeadMenu = true;
				DeadMenu = true;
				break;
			}

			SDL_Event e;
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					gameState = false;
					appIsRunning = false;
				}
			} // done with handling events

			pRenderer->Draw();

			// Swap the back buffer with the front buffer
			SDL_GL_SwapWindow(pWindow);

			pInputManager->Update();


			for (int i = 0; i < pGameObjectManager->mGameObjects.size(); ++i)
			{
				pGameObjectManager->mGameObjects[i]->Update();
			}

			// Bullet Updates
			if (pInputManager->IsKeyTriggered(SDL_SCANCODE_SPACE) || pInputManager->mouseIsTriggeredL())
			{
				Transform* nPlayerTransform = nullptr;
				GameObject* nBullet = new GameObject();
				nBullet->AddComponent(TRANSFORM);
				nBullet->AddComponent(SPRITE);
				nBullet->AddComponent(UPDOWN);
				nBullet->Tag = "Bullet";
				Sprite* nEnemySprite = (Sprite*)nBullet->GetComponent("Sprite");
				nEnemySprite->mpSurface = gpResourceManager->LoadSurface("..\\Resources\\sBullet.png");
				Transform* nBulletTransform = (Transform*)nBullet->GetComponent("Transform");
				for (int i = 0; i < pGameObjectManager->mGameObjects.size(); ++i)
				{
					if (pGameObjectManager->mGameObjects[i]->Tag == "Player")
					{
						nPlayerTransform = (Transform*)pGameObjectManager->mGameObjects[i]->GetComponent("Transform");
						break;
					}
				}
				nBulletTransform->mPositionX = nPlayerTransform->mPositionX;
				nBulletTransform->mPositionY = nPlayerTransform->mPositionY - 25.0f;
				nBulletTransform->mScale = glm::vec2(20.0f, 20.0f);
				pGameObjectManager->AddGameObject(nBullet);
			}

			// PowerUp Updates
			if (LazerUseTime > 1000)
			{
				if (pInputManager->IsKeyTriggered(SDL_SCANCODE_V) || pInputManager->mouseIsTriggeredR())
				{
					Transform* nPlayerTransform = nullptr;
					GameObject* nLazer = new GameObject();
					nLazer->AddComponent(TRANSFORM);
					nLazer->AddComponent(SPRITE);
					nLazer->AddComponent(UPDOWN);
					nLazer->Tag = "Lazer";
					Sprite* nEnemySprite = (Sprite*)nLazer->GetComponent("Sprite");
					nEnemySprite->mpSurface = gpResourceManager->LoadSurface("..\\Resources\\sLazer.png");
					Transform* nBulletTransform = (Transform*)nLazer->GetComponent("Transform");
					for (int i = 0; i < pGameObjectManager->mGameObjects.size(); ++i)
					{
						if (pGameObjectManager->mGameObjects[i]->Tag == "Player")
						{
							nPlayerTransform = (Transform*)pGameObjectManager->mGameObjects[i]->GetComponent("Transform");
							break;
						}
					}

					nBulletTransform->mPositionX = nPlayerTransform->mPositionX;
					nBulletTransform->mPositionY = nPlayerTransform->mPositionY - 25.0f;
					nBulletTransform->mScale = glm::vec2(20.0f, 20.0f);
					pGameObjectManager->AddGameObject(nLazer);
					LazerUseTime = 0;
				}
			}

			// Spawnning Enemies
			if (spawnTimer <= 0)
			{
				pEnemySpawner->NormalEnemySpawner();

				float timer = gpFRC->GameTime();
				if (timer > 60 && timer < 120)
				{
					spawnTimer = pEnemySpawner->RandomGenerator(10.0, 30.0);
				}
				else if (timer > 120)
				{
					spawnTimer = pEnemySpawner->RandomGenerator(5.0, 10.0);
				}
				else
				{
					spawnTimer = pEnemySpawner->RandomGenerator(30.0, 100.0);
				}
			}

			// Spawwing Walls
			if (wallSpawnTimer <= 0)
			{
				pEnemySpawner->WallSpawner();
				wallSpawnTimer = pEnemySpawner->RandomGenerator(100.0, 500.0);
			}

			// Spawwing FireBall
			if (FireballSpawnTimer <= 0)
			{
				pEnemySpawner->FireBallSpawner();
				FireballSpawnTimer = pEnemySpawner->RandomGenerator(500.0, 1500.0);
			}

			--spawnTimer;
			--wallSpawnTimer;
			--FireballSpawnTimer;
			++LazerUseTime;
			SDL_Log("LazerUseTime = %d", LazerUseTime/100);

			// Behaviour Updates
			if (pInputManager->IsKeyPressed(SDL_SCANCODE_ESCAPE))
			{
				gameState = false;
				appIsRunning = false;
			}

			pCollisionManager->Update();
			pEventManager->Update(gpFRC->GetDeltaTime());
			pGameObjectManager->DeleteGameObjects();

			if (pCollisionManager->GetEnemyLeftCounter() >= 5)
			{
				gameState = false;
				LoadDeadMenu = true;
				DeadMenu = true;
			}

			// Lock the frame rate
			gpFRC->FrameEnd();
		}

		if (LoadDeadMenu)
		{
			pGOF->LoadGameObject("..\\JSON Files\\DeadMenu.json");
			LoadDeadMenu = false;
		}
		
		while (DeadMenu)
		{
			SDL_Event e;
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					appIsRunning = false;
				}
			} // done with handling events

			pRenderer->Draw();
			SDL_GL_SwapWindow(pWindow);

			pInputManager->Update();

			// Behaviour Updates
			if (pInputManager->IsKeyPressed(SDL_SCANCODE_ESCAPE))
			{
				appIsRunning = false;
				DeadMenu = false;
			}

			if (pInputManager->IsKeyPressed(SDL_SCANCODE_H))
			{
				DeadMenu = false;
				HomeScreen = true;
				for (int i = 0; i < pGameObjectManager->mGameObjects.size(); ++i)
				{
					if (pGameObjectManager->mGameObjects[i]->Tag == "DeadMenu")
					{
						pGameObjectManager->mGameObjects[i]->isDestroyed = true;
					}
				}
			}
		}
	}

	delete gpFRC;
	delete pInputManager;
	delete gpResourceManager;
	delete pGameObjectManager;
	delete pGOF;
	delete pEventManager;
	delete pEnemySpawner;

	// Delete all the objects we've created
	pVAO->Delete();
	VBO1.Delete();
	EBO1.Delete();
	//shaderProgram.Delete();
	pShader->Delete();

	// Close and destroy the window
	SDL_DestroyWindow(pWindow);

	// Quit SDL subsystems
	SDL_Quit();

	
	return 0;
}