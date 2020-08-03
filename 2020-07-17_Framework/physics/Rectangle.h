#pragma once
#include "ShapeObject.h"
#include "videoDriver.h"

class RectangleShape : public ShapeObject {
private:
	Vector2 m_size;
public:
	RectangleShape(float posX, float posY, float width, float height, float mass = 1, float vx = 0, float vy = 0): 
		ShapeObject(Vector2(posX,posY),true,true,true,mass,Vector2(vx,vy)), 
		m_size(Vector2(width,height)) {}
	void Render() {
		if (m_isOnCollision) VideoDriver::GetInstance()->SetColor(COLLIDED_COLOR);
		VideoDriver::GetInstance()->FillRect(m_position.x, m_position.y, m_size.x, m_size.y);
		VideoDriver::GetInstance()->SetColor(DEFAULT_COLOR);
	};
	bool CheckIsTouchInside(int x, int y) {
		if (!m_isTouchDetectable) return false;
		return (m_position.x < x && x < m_position.x + m_size.x && m_position.y < y && y < m_position.y + m_size.y);
	}
	Vector2 & GetSize() { return m_size; }
	virtual void onStartCollision(ShapeObject * collidedObject, Vector2 collideDirection) {
		ShapeObject::onStartCollision(collidedObject, collideDirection);
		EffectManager::GetInstance()->CreateFirework(Vector2(m_position.x + m_size.x / 2 + collideDirection.x*m_size.x / 2, m_position.y + m_size.y / 2 + collideDirection.y*m_size.y / 2), 1, -1);
	}
};