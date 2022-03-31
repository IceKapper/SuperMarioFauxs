#pragma once
#ifndef _POWBLOCK_H
#define _POWBLOCK_H

#include <SDL.h>
#include "LevelMap.h"
#include "Commons.h"
#include "Texture2D.h"

class PowBlock
{
public:
	PowBlock(SDL_Renderer* sdl_renderer, LevelMap* level_map);
	~PowBlock();

	void Render();
	void TakeHit();
	Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y, m_single_sprite_w, m_single_sprite_h); }
	bool IsAvailable() { return m_num_hits_left > 0; }
	Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight()); }

private:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	LevelMap* m_level_map;

	float m_single_sprite_w;
	float m_single_sprite_h;
	int m_num_hits_left;




};

#endif // _POWBLOCK_H
