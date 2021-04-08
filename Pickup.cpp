#include "Pickup.hpp"

Pickup::Pickup(PickupType type) {
	m_Type = type;
	switch (type) {
	case PickupType::AMMO:
		m_Sprite = Sprite(TextureHolder::GetTexture(Paths::AMMO_PATH));
		m_Value = Configs::AMMO_START_VAL;
		break;
	case PickupType::HEALTH:
		m_Sprite = Sprite(TextureHolder::GetTexture(Paths::HEALTH_PATH));
		m_Value = Configs::HEALTH_START_VAL;
		break;
	}
	m_Sprite.setOrigin(Coordinates::PLAYER_ORIGIN_X, Coordinates::PLAYER_ORIGIN_Y);
	m_SecondsToLive = Configs::START_SECONDS_TO_LIVE;
	m_SecondsToWait = Configs::START_WAIT_TIME;
}

void Pickup::setArena(IntRect arena) {
	m_Arena.left = arena.left + Configs::PICKUP_ARENA_OFFSET;
	m_Arena.width = arena.width - Configs::PICKUP_ARENA_OFFSET;
	m_Arena.top = arena.top + Configs::PICKUP_ARENA_OFFSET;
	m_Arena.height = arena.height - Configs::PICKUP_ARENA_OFFSET;

	spawn();
}

void Pickup::spawn() {
	srand((int)time(0) / (rand() % 2 + 1));
	int x = (rand() % m_Arena.width);
	srand((int)time(0) * (rand() % 2 + 1));
	int y = (rand() % m_Arena.height);

	m_SecondsSinceSpawn = 0;
	m_Spawned = true;
	m_Sprite.setPosition(x, y);
}

FloatRect Pickup::getPosition() {
	return m_Sprite.getGlobalBounds();
}

Sprite Pickup::getSprite() {
	return m_Sprite;
}

void Pickup::update(float elapsedTime) {
	if (m_Spawned) {
		m_SecondsSinceSpawn += elapsedTime;
	}
	else {
		m_SecondsSinceDeSpawn += elapsedTime;
	}

	if (m_SecondsSinceSpawn > m_SecondsToLive && m_Spawned) {
		m_Spawned = false;
		m_SecondsSinceDeSpawn = 0;
	}
	if (m_SecondsSinceDeSpawn > m_SecondsToLive && !m_Spawned) {
		spawn();
	}
}

bool Pickup::isSpawned() {
	return m_Spawned;
}

int Pickup::gotIt() {
	m_Spawned = false;
	m_SecondsSinceDeSpawn = 0;
	return m_Value;
}

void Pickup::upgrade() {
	switch (m_Type) {
	case PickupType::AMMO:
		m_Value += Configs::AMMO_START_VAL * 0.5;
		break;
	case PickupType::HEALTH:
		m_Value += Configs::HEALTH_START_VAL * 0.5;
		break;
	}
	m_SecondsToLive += (Configs::START_SECONDS_TO_LIVE / 10);
	m_SecondsToWait -= (Configs::START_WAIT_TIME / 10);
}