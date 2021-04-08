#pragma once
#include <SFML/Graphics.hpp>
#include "Configuration.hpp"
#include "TextureHolder.hpp"

using namespace sf;

class Player {
private:
	Vector2f m_Position;
	Sprite m_Sprite;
	Texture m_Texture;
	Vector2f m_Resolution;
	IntRect m_Arena;
	int m_TileSize;

	bool m_UpPressed;
	bool m_DownPressed;
	bool m_LeftPressed;
	bool m_RightPressed;

	int m_Health;
	int m_MaxHealth;
	Time m_LastHit;
	float m_Speed;
public:
	Player();
	void spawn(Vector2f resolution, IntRect arena, int tileSize);
	void resetPlayerStats();
	bool hit(Time timeHit);
	Time getLastHitTime();
	FloatRect getPosition();
	Vector2f getCenter();
	float getRotation();
	Sprite getSprite();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void stopUp();
	void stopDown();
	void stopLeft();
	void stopRight();
	void update(float elapsedTime, Vector2i mousePosition);
	void upgradeSpeed();
	void upgradeHealth();
	void increaseHealthLevel(int amount);
	int getHealth();
};