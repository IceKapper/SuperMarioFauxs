#include "CharacterCoin.h"

CharacterCoin::CharacterCoin(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing, float movement_speed) : Character(renderer, imagePath, start_position, map)
{
	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_position = start_position;
	m_frame_delay = ANIMATION_DELAY;
	m_current_frame = 0;

	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();
}

CharacterCoin::~CharacterCoin()
{

}


void CharacterCoin::Update(float deltaTime, SDL_Event e)
{
	//use the code within the base class
	Character::Update(deltaTime, e);

	AnimateCoin(deltaTime);

	//move
	if (m_facing_direction == FACING_LEFT)
	{
		m_position.x -= deltaTime * m_movement_speed;
	}
	else if (m_facing_direction == FACING_RIGHT)
	{
		m_position.x += deltaTime * m_movement_speed;
	}
}

void CharacterCoin::Render()
{
	//get the portion of the sprite sheet you want to draw {xpos, ypos, width of sprite, height of sprite}
	SDL_Rect portion_of_sprite = { m_single_sprite_w * m_current_frame, 0, m_single_sprite_w, m_single_sprite_h };
	SDL_Rect dest_rect = { static_cast<int>(m_position.x), static_cast<int>(m_position.y), m_single_sprite_w, m_single_sprite_h };

	//Then draw it facing the correct direction
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(portion_of_sprite, dest_rect, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(portion_of_sprite, dest_rect, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterCoin::FlipDirection()
{
	//Flip to opposite direction
	if (m_facing_direction == FACING_LEFT)
	{
		m_facing_direction = FACING_RIGHT;
	}
	else
	{
		m_facing_direction = FACING_LEFT;
	}
}

void CharacterCoin::AnimateCoin(float deltaTime)
{
	m_frame_delay -= deltaTime;
	//Looping between sprites with animation
	if (m_frame_delay <= 0.0f)
	{
		//reset drame delay amount
		m_frame_delay = ANIMATION_DELAY;

		//move the frame over
		m_current_frame++;

		//loop frame around if it goes beyond number of frames
		if (m_current_frame > 2)
			m_current_frame = 0;
	}
}
