#include "Collisions.h"
#include "Character.h"

//initialise instance to nullptr
Collisions* Collisions::m_instance = nullptr;

Collisions::Collisions()
{

}

Collisions::~Collisions()
{
	m_instance = nullptr;
}

Collisions* Collisions::Instance()
{
	if (!m_instance)
	{
		m_instance = new Collisions;
	}

	return m_instance;
}

bool Collisions::Circle(Radius2D object1, Radius2D object2)
{
	//Calculate the vector between two objects
	Vector2D vec = Vector2D((object1.x - object2.x), 
		(object1.y - object2.y));

	//Calculate length of vector
	double distance = sqrt((vec.x * vec.x) + (vec.y * vec.y));

	//Get collision radius of each character and accumulate them
	double combined_distance = (object1.radius + object2.radius);

	//Check whether the distance is shorter than the accumulates collision radii.
	return distance < combined_distance;
}

bool Collisions::Box(Rect2D rect1, Rect2D rect2)
{
	if(rect1.x + (rect1.width/2) > rect2.x &&
		rect1.x + (rect1.width/2) < rect2.x + rect2.width && 
		rect1.y + (rect1.height/2) > rect2.y &&
		rect1.y + (rect1.height / 2) < rect2.y + rect2.height)
	{
		return true;
	}

	return false;
}
