#include "CharacterKoopa.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing, float movement_speed) : Character(renderer, imagePath, start_position, map)
{
	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_position = start_position;
	m_injured = false;

	m_single_sprite_w = m_texture->GetWidth() / 2;
	m_single_sprite_h = m_texture->GetHeight();

}

CharacterKoopa::~CharacterKoopa()
{

}

void CharacterKoopa::TakeDamage()
{
	m_injured = true;
	m_injured_time = INJURED_TIME;
	Jump();
}

void CharacterKoopa::Jump()
{
	m_jump_force = INITIAL_JUMP_FORCE_SMALL;
	m_jumping = true;
	m_can_jump = false;
}

void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	//use the code within the base class
	Character::Update(deltaTime, e);

	if (!m_injured)
	{
		//Enemy is not injured so move
		if (m_facing_direction == FACING_LEFT)
		{
			m_position.x -= deltaTime * m_movement_speed;
		}
		else if (m_facing_direction == FACING_RIGHT)
		{
			m_position.x += deltaTime * m_movement_speed;
		}
	}
	else
	{
		//Don't move while injured
		m_moving_left = false;
		m_moving_right = false;

		//count down the injured time
		m_injured_time -= deltaTime;

		if (m_injured_time <= 0.0f)
		{
			FlipRightWayUp();
		}
	}
}

void CharacterKoopa::Render()
{
	//variable to hold the left position of the sprite we want to draw
	int left = 0.0f;

	//if injured move the left position to be the left position of the second image of the sprite sheet
	if (m_injured)
		left = m_single_sprite_w;

	//get the portion of the sprite sheet you want to draw {xpos, ypos, width of sprite, height of sprite}
	SDL_Rect portion_of_sprite = { left, 0, m_single_sprite_w, m_single_sprite_h };
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

void CharacterKoopa::FlipRightWayUp()
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

	m_injured = false;
	Jump();
}
