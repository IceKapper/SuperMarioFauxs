#include "PowBlock.h"
#include <iostream>
using namespace std;

PowBlock::PowBlock(SDL_Renderer* sdl_renderer, LevelMap* level_map)
{
	string imagePath = "Images/RequiredImages/PowBlock.png";
	m_texture = new Texture2D(sdl_renderer);

	if (!m_texture->LoadFromFile(imagePath.c_str()))
	{
		cout << "Failed to load texture." << endl;
		return;
	}

	m_level_map = level_map;
	m_single_sprite_w = m_texture->GetWidth() / 3; //There are three images in this sprite sheet
	m_single_sprite_h = m_texture->GetHeight();
	m_num_hits_left = 3;
	m_position = Vector2D((SCREEN_WIDTH * 0.5f) - m_single_sprite_w * 0.5f, 260);
}

PowBlock::~PowBlock()
{
	m_renderer = nullptr;
	delete m_texture;
	m_texture = nullptr;
}

void PowBlock::Render()
{
	if (m_num_hits_left > 0)
	{
		//get the portion of the sheet we want to draw
		int left = m_single_sprite_w * (m_num_hits_left - 1);

		// xpos, ypos, sprite sheet width, sprite sheet height
		SDL_Rect portion_of_sprite = { left, 0, m_single_sprite_w, m_single_sprite_h };

		//determine where to draw it
		SDL_Rect dest_rect = {static_cast<int>(m_position.x), static_cast<int>(m_position.y), m_single_sprite_w, m_single_sprite_h };

		//draw the sprite
		m_texture->Render(portion_of_sprite, dest_rect, SDL_FLIP_NONE);

	}
}

void PowBlock::TakeHit()
{
	m_num_hits_left -= 1;
	
	if (m_num_hits_left <= 0)
	{
		m_num_hits_left = 0;
		m_level_map->ChangeTileAt(8, 7, 0);
		m_level_map->ChangeTileAt(8, 8, 0);
	}
}
