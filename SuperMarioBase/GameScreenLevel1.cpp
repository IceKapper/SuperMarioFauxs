#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include <iostream>

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	m_background_texture = nullptr;
	delete character_mario;
	character_mario = nullptr;
	delete character_luigi;
	character_luigi = nullptr;
}

void GameScreenLevel1::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
	character_mario->Render();
	character_luigi->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	character_mario->Update(deltaTime, e);
	character_luigi->Update(deltaTime, e);
}

bool GameScreenLevel1::SetUpLevel()
{
	//set up player character
	character_mario = new CharacterMario(m_renderer, "Images/RequiredImages/Mario.png", Vector2D(64, 330));
	character_luigi = new CharacterLuigi(m_renderer, "Images/RequiredImages/Luigi.png", Vector2D(64, 330));

	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/test.bmp"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}
	else
	{
		return true;
	}

}