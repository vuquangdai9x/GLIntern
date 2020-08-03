#pragma once
#include "ShapeObject.h"
#include "videoDriver.h"
#include <math.h>

class CircleShape : public ShapeObject {
public:
	float m_radius;

	CircleShape(float posX, float posY, float radius, float mass = 1, float vx = 0, float vy = 0) : 
		ShapeObject(Vector2(posX, posY), true, true, true, mass, Vector2(vx, vy)),
		m_radius(radius) {}
	void Render() {
		if (m_isOnCollision) VideoDriver::GetInstance()->SetColor(COLLIDED_COLOR);
		VideoDriver::GetInstance()->DrawCircle(m_position.x, m_position.y, m_radius);
		VideoDriver::GetInstance()->SetColor(DEFAULT_COLOR);
	};
	bool CheckIsTouchInside(int x, int y) {
		if (!m_isTouchDetectable) return false;
		float deltaX = m_position.x - x;
		float deltaY = m_position.y - y;
		return (deltaX*deltaX + deltaY*deltaY < m_radius*m_radius);
	}
	float GetRadius() { return m_radius; };
	void onStartCollision(ShapeObject * collidedObject, Vector2 collideDirection) {
		ShapeObject::onStartCollision(collidedObject, collideDirection);
		EffectManager::GetInstance()->CreateFirework(Vector2(m_position.x + collideDirection.x*m_radius, m_position.y + collideDirection.y*m_radius), 1, -1);
	}
};