#include "Bullet.hpp"

Bullet::Bullet(){
	m_BulletShape.setSize(Vector2f(Configs::BULLET_WIDTH, Configs::BULLET_HEIGHT));
}

void Bullet::shoot(float startX, float startY, float xTarget, float yTarget) {
	m_InFlight = true;
	m_Position.x = startX;
	m_Position.y = startY;

	float gradient = (startX - xTarget) / (startY - yTarget);
	float angle = (atan2(startY - yTarget / 2, startX - xTarget) * 180) / Configs::PIE;
	
	if (gradient < 0) {
		gradient *= -1;
	}
	float ratioXY = m_BuletSpeed / (1 + gradient);
	m_BulletDistanceY = ratioXY;
	m_BulletDistanceX = ratioXY * gradient;
	if (xTarget < startX) {
		m_BulletDistanceX *= -1;
	}
	if (yTarget < startY) {
		m_BulletDistanceY *= -1;
	}
	float range = Configs::BULLET_RANGE;
	m_MinX = startX - range;
	m_MaxX = startX + range;
	m_MinY = startY - range;
	m_MaxY = startY + range;

	m_BulletShape.setPosition(m_Position);
	m_BulletShape.setRotation(angle);
}

void Bullet::stop() {
	m_InFlight = false;
}

bool Bullet::isInFlight() {
	return m_InFlight;
}

FloatRect Bullet::getPosition() {
	return m_BulletShape.getGlobalBounds();
}

RectangleShape Bullet::getShape() {
	return m_BulletShape;
}

void Bullet::update(float elpasedTime) {
	m_Position.x += elpasedTime * m_BulletDistanceX;
	m_Position.y += elpasedTime * m_BulletDistanceY;

	m_BulletShape.setPosition(m_Position);
	if (m_Position.x < m_MinX || m_Position.x > m_MaxX || m_Position.y < m_MinY || m_Position.y > m_MaxY) {
		m_InFlight = false;
	}
}