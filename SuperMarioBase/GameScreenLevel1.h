#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include <vector>
#include "GameScreen.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "PowBlock.h"
#include "Commons.h"
#include "LevelMap.h"
#include "CharacterCoin.h"

class Texture2D;
class CharacterMario;
class CharacterLuigi;
class CharacterKoopa;
class PowBlock;
class CharacterCoin;

class GameScreenLevel1 : GameScreen
{

public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void UpdatePowBlock();


private: 
	bool SetUpLevel();
	void SetLevelMap();
	void DoScreenShake();

	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);

	void UpdateCoins(float deltaTime, SDL_Event e);
	void CreateCoin(Vector2D position, FACING direction, float speed);

	Texture2D* m_background_texture;
	CharacterMario* character_mario;
	CharacterLuigi* character_luigi;
	CharacterKoopa* koopa;
	CharacterCoin* coin;
	PowBlock* m_pow_block;
	LevelMap* m_level_map;

	std::vector<CharacterKoopa*> m_enemies;
	std::vector<CharacterCoin*> m_coins;

	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;

	float m_koopa_timer;
	float m_koopa_position;
	float m_coin_timer;
	float m_coin_position;
	float m_coin_counter;
};

#endif //_GAMESCREENLEVEL1_H
