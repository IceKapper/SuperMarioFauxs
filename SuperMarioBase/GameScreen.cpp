#include "GameScreen.h"

GameScreen::GameScreen(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}

GameScreen::~GameScreen()
{
	m_renderer = nullptr;
}

void GameScreen::Render(float deltaTime)
{

}

void GameScreen::Update(float deltaTime, SDL_Event e)
{

}