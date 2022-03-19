/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: ResourceManager.h
Purpose: Loads and maintains resources for use
Language: C++, gpp
Platform: gpp
- End Header --------------------------------------------------------*/

#pragma once

#include <unordered_map>

class SDL_Surface; //Forward declaration helps avoid using the header


class ResourceManager {
public:
	ResourceManager();
	~ResourceManager();
	
	SDL_Surface* LoadSurface(const char* pFilePath);
public:


private:
private:

	std::unordered_map<std::string, SDL_Surface*> mSurfaces;
};
