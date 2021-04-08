#include "Zombie.hpp"

using namespace std;

bool Zombie::hit() {
	m_Health--;
	if (m_Health < 0) {
		m_Alive = false;
		m_Sprite.setTexture(TextureHolder::GetTexture(Paths::BLOOD_PATH));
		return true;
	}
	return false;
}

bool Zombie::isAlive() {
	return m_Alive;
}

void Zombie::spawn(float start_x, float start_y, ZombieType type, int seed) {
	switch (type) {
	case ZombieType::BLOATER:
		m_Sprite = Sprite(TextureHolder::GetTexture(Paths::BLOATER_PATH));
		m_Speed = Configs::BLOATER_SPEED;
		m_Health = Configs::BLOATER_HEALTH;
		break;
	case ZombieType::CHASER:
		m_Sprite = Sprite(TextureHolder::GetTexture(Paths::CHASER_PATH));
		m_Speed = Configs::CHASER_SPEED;
		m_Health = Configs::CHASER_HEALTH;
		break;
	case ZombieType::CRAWLER:
		m_Sprite = Sprite(TextureHolder::GetTexture(Paths::CRAWLER_PATH));
		m_Speed = Configs::CRAWLER_SPEED;
		m_Health = Configs::CRAWLER_HEALTH;
		break;
	}
	m_Alive = true;
	srand((int)time(0) * seed);
	float modifier = (rand() % Configs::MAX_VARIANCE) + Configs::OFFSET;
	modifier /= Configs::MULTIPLIER;
	m_Speed *= modifier;
	m_Position.x = start_x;
	m_Position.y = start_y;
	m_Sprite.setOrigin(25, 25);
	m_Sprite.setPosition(m_Position);
}

FloatRect Zombie::getPosition() {
	return m_Sprite.getGlobalBounds();
}

Sprite Zombie::getSprite() {
	return m_Sprite;
}

void Zombie::update(float elapsedTime, Vector2f playerLocation) {
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;

	if (playerX > m_Position.x) {
		m_Position.x += m_Speed * elapsedTime;
	}
	if (playerX < m_Position.x) {
		m_Position.x -= m_Speed * elapsedTime;
	}
	if (playerY > m_Position.y) {
		m_Position.y += m_Speed * elapsedTime;
	}
	if (playerY < m_Position.y) {
		m_Position.y -= m_Speed * elapsedTime;
	}

	m_Sprite.setPosition(m_Position);

	float angle = (atan2(playerY - m_Position.y, playerX - m_Position.x) * 180) / Configs::PIE;
	m_Sprite.setRotation(angle);
}