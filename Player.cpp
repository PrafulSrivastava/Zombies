#include "Player.hpp"

Player::Player() {
	m_Speed = Configs::START_SPEED;
	m_Health = Configs::START_HEALTH;
	m_MaxHealth = Configs::START_HEALTH;
	m_Texture = TextureHolder::GetTexture(Paths::PLAYER_PATH);
	m_Sprite.setTexture(m_Texture);
	m_Sprite.setOrigin(Coordinates::PLAYER_ORIGIN_X, Coordinates::PLAYER_ORIGIN_Y);
}

void Player::spawn(Vector2f resolution, IntRect arena, int tileSize) {
	m_Position.x = arena.width / 2;
	m_Position.y = arena.height / 2;
	m_Arena.left = arena.left;
	m_Arena.width = arena.width;
	m_Arena.top = arena.top;
	m_Arena.height = arena.height;
	m_TileSize = tileSize;
	m_Resolution.x = resolution.x;
	m_Resolution.y = resolution.y;
}

void Player::resetPlayerStats() {
	m_Speed = Configs::START_SPEED;
	m_Health = Configs::START_HEALTH;
	m_MaxHealth = Configs::START_HEALTH;
}

Time Player::getLastHitTime() {
	return m_LastHit;
}

bool Player::hit(Time timeHit) {
	if (timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > Configs::HIT_LAG) {
		m_LastHit = timeHit;
		m_Health -= Configs::HEALTH_DROP;
		return true;
	}
	return false;
}

FloatRect Player::getPosition() {
	return m_Sprite.getGlobalBounds();
}

Vector2f Player::getCenter() {
	return m_Position;
}

float Player::getRotation() {
	return m_Sprite.getRotation();
}

Sprite Player::getSprite() {
	return m_Sprite;
}

int Player::getHealth() {
	return m_Health;
}

void Player::stopUp() {
	m_UpPressed = false;
}

void Player::stopDown() {
	m_DownPressed = false;
}

void Player::stopLeft() {
	m_LeftPressed = false;
}

void Player::stopRight() {
	m_RightPressed = false;
}
void Player::moveUp() {
	m_UpPressed = true;
}

void Player::moveDown() {
	m_DownPressed = true;
}

void Player::moveLeft() {
	m_LeftPressed = true;
}

void Player::moveRight() {
	m_RightPressed = true;
}

void Player::update(float elapsedTime, Vector2i mousePosition) {
	if (m_UpPressed) {
		m_Position.y -= m_Speed * elapsedTime;
	}
	if (m_DownPressed) {
		m_Position.y += m_Speed * elapsedTime;
	}
	if (m_LeftPressed) {
		m_Position.x -= m_Speed * elapsedTime;
	}
	if (m_RightPressed) {
		m_Position.x += m_Speed * elapsedTime;
	}
	m_Sprite.setPosition(m_Position);

	if (m_Position.x > m_Arena.width - m_TileSize) {
		m_Position.x = m_Arena.width - m_TileSize;
	}
	if (m_Position.x < m_Arena.left + m_TileSize) {
		m_Position.x = m_Arena.left + m_TileSize;
	}
	if (m_Position.y > m_Arena.height - m_TileSize) {
		m_Position.y = m_Arena.height - m_TileSize;
	}
	if (m_Position.y < m_Arena.top + m_TileSize) {
		m_Position.y = m_Arena.top + m_TileSize;
	}

	float angle = (atan2(mousePosition.y - m_Resolution.y / 2, mousePosition.x - m_Resolution.x / 2) * 180) / Configs::PIE;
	m_Sprite.setRotation(angle);
}

void Player::upgradeSpeed() {
	m_Speed += (Configs::START_SPEED * Configs::SPEED_BOOST);
}

void Player::upgradeHealth() {
	m_Health += (Configs::START_HEALTH * Configs::START_HEALTH);
}

void Player::increaseHealthLevel(int amount) {
	m_Health += amount;
	if (m_Health > m_MaxHealth) {
		m_Health = m_MaxHealth;
	}
}