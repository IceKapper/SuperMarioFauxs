#pragma once
#ifndef _CHARACTER_COIN
#define _CHARACTER_COIN
#include "Character.h"

class CharacterCoin : public Character
{
public:
	CharacterCoin(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing, float movement_speed);
	~CharacterCoin();

	virtual void Update(float deltaTime, SDL_Event e);
	virtual void Render();
	virtual void FlipDirection();

private:

	virtual void AnimateCoin(float deltaTime);
	float m_single_sprite_w;
	float m_single_sprite_h;

	float m_frame_delay;
	float m_current_frame;

	FACING m_facing_direction;
	float m_movement_speed;
};

#endif //_CHARACTER_COIN