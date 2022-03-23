#pragma once
#ifndef _CHARACTERLUIGI_H
#define _CHARACTERLUIGI_H

#include "character.h"

class CharacterLuigi : public Character
{
public: 
	CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position);
	~CharacterLuigi();

	virtual void Update(float deltaTime, SDL_Event e);
};

#endif //_CHARACTERMARIO_H