#pragma once
#include <SFML/Graphics.hpp>
#include "Configuration.hpp"
#include "TextureHolder.hpp"

using namespace sf;

class Zombie {
private:
	Vector2f m_Position;
	Sprite m_Sprite;
	float m_Speed;
	float m_Health;
	bool m_Alive;

public:
	bool hit();
	bool isAlive();
	void spawn(float start_x, float start_y, ZombieType type, int seed);
	FloatRect getPosition();
	Sprite getSprite();
	void update(float elapsedTime, Vector2f playerLocation);
};