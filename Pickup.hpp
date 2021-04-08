#pragma once
#include <SFML/Graphics.hpp>
#include "Configuration.hpp"
#include "TextureHolder.hpp"

using namespace sf;

class Pickup {
private:
	Sprite m_Sprite;
	IntRect m_Arena;
	int m_Value;
	PickupType m_Type;
	bool m_Spawned;
	float m_SecondsSinceSpawn;
	float m_SecondsSinceDeSpawn;
	float m_SecondsToWait;
	float m_SecondsToLive;

public:
	Pickup(PickupType type);
	void setArena(IntRect arena);
	void spawn();
	FloatRect getPosition();
	Sprite getSprite();
	void update(float elapsedTime);
	bool isSpawned();
	int gotIt();
	void upgrade();
};