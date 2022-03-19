#include <SDL_image.h>
#include "ResourceManager.h"
#include "SDL_surface.h"

ResourceManager::ResourceManager() {
	//
}

ResourceManager::~ResourceManager() 
{
	for (auto &pSurface : mSurfaces)
		SDL_FreeSurface(pSurface.second);

	mSurfaces.clear();
}

SDL_Surface* ResourceManager::LoadSurface(const char* pFilePath) 
{
	// Try to fetch from the hash map
	SDL_Surface* pSurface = mSurfaces[pFilePath];
	if (pSurface)
		return pSurface;

	// Load fresh image
	pSurface = IMG_Load(pFilePath);
	if (pSurface)
		mSurfaces[pFilePath] = pSurface;

	return pSurface;
}