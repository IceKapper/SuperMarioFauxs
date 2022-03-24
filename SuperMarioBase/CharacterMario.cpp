#include "CharacterMario.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map)
{

}

CharacterMario::~CharacterMario()
{

}

void CharacterMario::Update(float deltaTime, SDL_Event e)
{

	Character::Update(deltaTime, e);

	if (m_moving_left)
	{
		MoveLeft(deltaTime);
	}
	else if (m_moving_right)
	{
		MoveRight(deltaTime);
	}

	switch (e.type)
	{

	case SDL_KEYDOWN:

		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			m_moving_left = true;
			break;

		case SDLK_d:
			m_moving_right = true;
			break;

		case SDLK_SPACE:
			Jump();
			break;

		default:
			break;
		}

	default:
		break;
	}

	switch (e.type)
	{

	case SDL_KEYUP:

		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			m_moving_left = false;
			break;

		case SDLK_d:
			m_moving_right = false;
			break;

		default:
			break;
		}

	default:
		break;
	}
}
