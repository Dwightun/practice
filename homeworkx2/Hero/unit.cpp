#include <SFML\Graphics.hpp>
#include "Bullet.h"
#include <vector>
#include <string>
#include <SFML\Audio.hpp>
//tried to use audio lib, but failed
const float unitVelocity = 500.0f;
const float pi = 3.141592653f;
const float unitScale = 1.0f;
const float firingRate = 0.3f;
const float bulletVelocity = 1500.0f;
const float collisionRadius = 64.0f;

/// вы снова присылаете мне списанную работу. не засчитано

bool isSeekToNull(double lhs, double rhs)// to prevent 1/(0+) devision
{
	return std::abs(lhs - rhs) <= std::numeric_limits<double>::epsilon() * std::max(std::abs(lhs), std::abs(rhs));
	//thx for stackoverflow
}

void vectorNormalize(sf::Vector2f& vector)// clear
{
	float len = std::sqrt(vector.x * vector.x + vector.y * vector.y);
	if (isSeekToNull(len, 0))
		return;
	vector.x /= len;
	vector.y /= len;
}

void moveBullet(std::vector<Bullet>& bullets, sf::Time passed)// Do bullets need to fly?
{
	for (auto& bullet : bullets)
	{
		bullet.move(passed);
	}
}

void drawBullets(std::vector<Bullet>& bullets, sf::RenderWindow& window) // create vector of bullets
{
	if (bullets.empty())
		return;
	int i = 0;
	int bulletsNumber = bullets.size();
	while (i < bulletsNumber)
	{
		if (!bullets[i].isActive(window))
		{
			bullets[i] = bullets[bulletsNumber - 1];
			bullets.pop_back();
			bulletsNumber--;
		}
		else
			i++;
	}
	for (auto& bullet : bullets)
	{
		window.draw(bullet.shape);
	}
}

void moveunit(sf::Sprite& unit, sf::Time time, sf::RenderWindow& window) // clear
{
	float unitAdjustment = time.asSeconds() * unitVelocity;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && unit.getPosition().x - unitAdjustment >= collisionRadius * unitScale)
		unit.move(-unitAdjustment, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && unit.getPosition().x + unitAdjustment <= window.getSize().x - collisionRadius * unitScale)
		unit.move(unitAdjustment, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && unit.getPosition().y - unitAdjustment >= collisionRadius * unitScale)
		unit.move(0, -unitAdjustment);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && unit.getPosition().y + unitAdjustment <= window.getSize().y - collisionRadius * unitScale)
		unit.move(0, unitAdjustment);

	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	sf::Vector2f center = unit.getPosition();
	sf::Vector2f d = sf::Vector2f(mousePosition.x, mousePosition.y) - center;

	unit.setRotation(90 + atan2f(d.y, d.x) * 180 / pi);
}

sf::Texture loadTexture(sf::Texture texture, std::string path, bool smooth) { // clear
	texture.loadFromFile(path);
	texture.setSmooth(smooth); //Are we going to OpenGL?
	return texture;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 768), "unit", sf::Style::Titlebar | sf::Style::Close);

	window.setVerticalSyncEnabled(true); //God bless it
	sf::Clock clock;

	std::string path = "goose.png";
	sf::Texture texture;
	texture = loadTexture(texture, path, 1);
	sf::Sprite unit(texture);

	sf::Vector2u unitSize = unit.getTexture()->getSize();
	unit.setOrigin(unitSize.x / 2, unitSize.y / 2);
	unit.setScale(unitScale, unitScale);
	sf::Vector2u windowSize = window.getSize();
	unit.setPosition(windowSize.x / 2, windowSize.y / 2);
	float totalRun = 0.0f;
	float lastBulletFired = 0.0f;
	std::vector<Bullet> bullets;
	sf::Time time;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}
		//unit movement
		window.clear(sf::Color(154, 205, 50));
		time = clock.getElapsedTime();
		clock.restart();
		totalRun += time.asSeconds();

		

		moveunit(unit, time, window);

		window.draw(unit);

		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		sf::Vector2f center = unit.getPosition();
		sf::Vector2f d = sf::Vector2f(mousePosition.x, mousePosition.y) - center;
		vectorNormalize(d);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F1)) 
		{
			sf::Image Screen = window.capture();
			Screen.saveToFile("screenshot.jpg");
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)))
		{
			if (totalRun - lastBulletFired >= firingRate)
			{
				bullets.push_back(Bullet(unit.getPosition().x + unit.getTexture()->getSize().y * unitScale * d.x,
					unit.getPosition().y + unit.getTexture()->getSize().y * unitScale * d.y,
					sf::Vector2f(d.x * bulletVelocity, d.y * bulletVelocity)));
				lastBulletFired = totalRun;
			}
		}
		moveBullet(bullets, time);
		drawBullets(bullets, window);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && !(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)))
		{
			float maxScreenLen = std::sqrt(window.getSize().x * window.getSize().x + window.getSize().y * window.getSize().y);
			sf::RectangleShape line1(sf::Vector2f(maxScreenLen, 3));
			line1.setFillColor(sf::Color::Yellow);
			line1.setPosition(unit.getPosition().x + 40 * unitScale * d.x + 15 * unitScale* d.y,
				unit.getPosition().y + 40 * unitScale* d.y - 15 * unitScale* d.x);

			line1.setRotation(atan2f(d.y, d.x) * 180 / pi);
			window.draw(line1);
		}
		window.display();

	}

	return 0;
}
