#pragma once
#ifndef _CHARACTER_KOOPA
#define _CHARACTER_KOOPA
#include "Character.h"

class CharacterKoopa : public Character
{

public:
	CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing, float movement_speed);
	~CharacterKoopa();

	void TakeDamage();
	void Jump();

	virtual void Update(float deltaTime, SDL_Event e);
	virtual void Render();
	bool GetInjured() { return m_injured; }

private:
	void FlipRightWayUp();

	float m_single_sprite_w;
	float m_single_sprite_h;

	FACING m_facing_direction;
	float m_movement_speed;
	bool m_injured;
	float m_injured_time;

};

#endif //_CHARACTER_KOOPA