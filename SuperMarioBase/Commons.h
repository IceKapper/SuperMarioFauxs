#pragma once

float x;
float y;

struct Vector2D
{
	Vector2D() 
	{
		float x = 0.0f;
		float y = 0.0f;
	}

	Vector2D(float initial_x, float initial_y)
	{
		x = initial_x;
		y = initial_y;
	};
};


