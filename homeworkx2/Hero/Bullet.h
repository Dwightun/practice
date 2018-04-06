#pragma once
#include <SFML\Graphics.hpp>


class Bullet
{
public:
	float x, y;
	sf::Vector2f velocity;
	sf::CircleShape shape;

	Bullet(float x, float y, const sf::Vector2f& velocity, float size = 20.0f);

	void move(sf::Time time);
	bool isActive(const sf::Window& window) const;
};