#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include "Collisions.h"
#include "CharacterKoopa.h"
#include <iostream>
using namespace std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_level_map = nullptr;
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	m_background_texture = nullptr;
	delete character_mario;
	character_mario = nullptr;
	delete character_luigi;
	character_luigi = nullptr;
	delete m_pow_block;
	m_pow_block = nullptr;
	m_enemies.clear();
}

void GameScreenLevel1::Render()
{
	//draw the enemies
	for (int i = 0; i  < m_enemies.size(); i++)
	{
		m_enemies[i]->Render();
	}

	//draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);
	character_mario->Render();
	character_luigi->Render();
	m_pow_block->Render();

}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	character_mario->Update(deltaTime, e);
	character_luigi->Update(deltaTime, e);
	UpdatePowBlock();
	UpdateEnemies(deltaTime, e);

	//Check for Player collision
	if (Collisions::Instance()->Box(character_mario->GetCollisionBox(), character_luigi->GetCollisionBox()))
	{
		cout << "Circle hit!" << endl;
	}

	//Shake screen if required
	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		if (m_shake_time <= 0.0f)
		{
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}
	}
}

bool GameScreenLevel1::SetUpLevel()
{
	SetLevelMap();

	//set up player character
	character_mario = new CharacterMario(m_renderer, "Images/RequiredImages/Mario.png", Vector2D(64, 330), m_level_map);
	character_luigi = new CharacterLuigi(m_renderer, "Images/RequiredImages/Luigi.png", Vector2D(372, 330), m_level_map);
	m_pow_block = new PowBlock(m_renderer, m_level_map);
	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);

	m_screenshake = false;
	m_background_yPos = 0.0f;

	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/RequiredImages/BackgroundMB.PNG"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}
	else
	{
		return true;
	}
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
					  { 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//set the new one
	m_level_map = new LevelMap(map);

}

void GameScreenLevel1::UpdatePowBlock()
{
	if (Collisions::Instance()->Box(m_pow_block->GetCollisionBox(), character_mario->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable())
		{
			//Collided While Jumping
			if (character_mario->IsJumping())
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				character_mario->CancelJump();
			}
		}
	}

	if (Collisions::Instance()->Box(m_pow_block->GetCollisionBox(), character_luigi->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable())
		{
			//Collided While Jumping
			if (character_luigi->IsJumping())
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				character_luigi->CancelJump();
			}
		}
	}
}

void GameScreenLevel1::DoScreenShake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;
	for ( int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->TakeDamage();
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!m_enemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			//check if the enemy is on the bottom row of tiles
			if (m_enemies[i]->GetPosition().y > 300.0f)
			{
				//is the enemy off screen to the left or right?
				if (m_enemies[i]->GetPosition().x < (float)(-m_enemies[i]->GetCollisionBox().width * 0.5f) || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(m_enemies[i]->GetCollisionBox().width * 0.55f))
					m_enemies[i]->SetAlive(false);
			}

			//Now do the update
			m_enemies[i]->Update(deltaTime, e);

			//Check to see if an enemy collides with a player
			if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]->GetPosition().y <= 64.0f) && (m_enemies[i]->GetPosition().x < 64.0f || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//ignore collisions behind pipe
			}
			else
			{
				if (Collisions::Instance()->Circle(m_enemies[i]->GetCollisionRadius(), character_mario->GetCollisionRadius()))
				{
					if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
					}
					else
					{
						//Kill Mario
					}
				}
				if (Collisions::Instance()->Circle(m_enemies[i]->GetCollisionRadius(), character_luigi->GetCollisionRadius()))
				{
					if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
					}
					else
					{
						//Kill Luigi
					}
				}
			}
			if (!m_enemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}
		//remove dead enemies -1 each update
		if (enemyIndexToDelete != -1)
		{
			m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	koopa = new CharacterKoopa(m_renderer, "Images/RequiredImages/koopa.png", position, m_level_map, direction, speed);
	m_enemies.push_back(koopa);
}
