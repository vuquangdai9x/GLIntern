#pragma once
#include "Vector2.h"
#include <vector>
#include "define.h"
#include "ShapeObject.h"
#include "EffectManager.h"

ShapeObject::ShapeObject(Vector2 position, bool isRigid = true, bool isTouchDetectable = true, bool hasCollider = true, float mass = 1, Vector2 velocity = Vector2(0, 0)) :
		m_position(position),
		m_isRigid(isRigid),
		m_isTouchDetectable(isTouchDetectable),
		m_hasCollider(hasCollider),
		m_mass(mass),
		m_velocity(velocity),
		m_isOnCollision(false)
	{
		m_SumForce.x = m_SumForce.y = 0;
	}
void ShapeObject::Update(float frameTime) {
	//printf("Position: %f,%f\n", m_position.x, m_position.y);
	m_isOnCollision = false;
	for (std::vector<CollisionInfo>::iterator iter = m_listCollisionInfo.begin(); iter != m_listCollisionInfo.end(); /*do nothing*/) {
		if (iter->m_collidedOnCurrentFrame) {
			m_isOnCollision = true;
			if (iter->m_collidedOnPrevFrame) {
				onStayCollision(iter->m_collidedObj,iter->m_direction);
			}
			else {
				onStartCollision(iter->m_collidedObj, iter->m_direction);
			}
			iter->m_collidedOnPrevFrame = true;
			iter->m_collidedOnCurrentFrame = false;
			iter++;
		}
		else {
			onEndCollision(iter->m_collidedObj, iter->m_direction);
			iter = m_listCollisionInfo.erase(iter);
		}
	}

	if (m_isRigid) {
		m_velocity.x += m_SumForce.x / m_mass * frameTime;
		m_velocity.y += m_SumForce.y / m_mass * frameTime;

		m_position.x += m_velocity.x * frameTime / METER_PER_PIXEL;
		m_position.y += m_velocity.y * frameTime / METER_PER_PIXEL;
	}
	m_SumForce.x = m_SumForce.y = 0;
}
void ShapeObject::AddForce(Vector2 force) {
	m_SumForce.x += force.x;
	m_SumForce.y += force.y;
}
Vector2 ShapeObject::GetForce() { return m_SumForce; }
Vector2 & ShapeObject::GetPosition() { return m_position; }
void ShapeObject::moveTo(float x, float y) {
	m_position.x = x;
	m_position.y = y;
}
float ShapeObject::GetMass() { return m_mass; }
void ShapeObject::SetVelocity(Vector2 new_velocity) {
	m_velocity = new_velocity;
}
Vector2 ShapeObject::GetVelocity() { return m_velocity; }

void ShapeObject::onCollision(ShapeObject * collidedObject, Vector2 collisionDirection) {
	bool found = false;
	for (int i = 0; i < m_listCollisionInfo.size(); i++) {
		// TODO: compare 2 pointer
		if (m_listCollisionInfo[i].m_collidedObj == collidedObject) {
			m_listCollisionInfo[i].m_collidedOnCurrentFrame = true;
			found = true;
			break;
		}
	}
	if (!found) {
		m_listCollisionInfo.push_back(CollisionInfo(collidedObject, collisionDirection));
	}
}

void ShapeObject::onStartCollision(ShapeObject * collidedObject, Vector2 collideDirection) {
	//EffectManager::GetInstance()->CreateFirework(Vector2((collidedObject->GetPosition().x + m_position.x) / 2, (collidedObject->GetPosition().y + m_position.y) / 2), 1, -1);
	if (m_isRigid && collidedObject->m_isRigid) {
		float sqrMagnitude = (collideDirection.x*collideDirection.x + collideDirection.y*collideDirection.y);
		float sqrtMagnitude = sqrt(sqrMagnitude);
		collideDirection.x /= sqrtMagnitude;
		collideDirection.y /= sqrtMagnitude;
		Vector2 newVelocity;
		float bounce = 1;
		float t = - 2 * (collideDirection.x*m_velocity.x + collideDirection.y*m_velocity.y);
		if (t < 0) {
			newVelocity.x = (m_velocity.x + t*collideDirection.x)*bounce;
			newVelocity.y = (m_velocity.y + t*collideDirection.y)*bounce;
		}
		else {
			newVelocity.x = (m_velocity.x + collideDirection.x)*bounce;
			newVelocity.y = (m_velocity.y + collideDirection.y)*bounce;
		}
		SetVelocity(newVelocity);
	}
	else {
		float t = -2 * (collideDirection.x*m_velocity.x + collideDirection.y*m_velocity.y) / (collideDirection.x*collideDirection.x + collideDirection.y*collideDirection.y);
		Vector2 newVelocity;
		float bounce = 1;
		newVelocity.x = (m_velocity.x + t*collideDirection.x)*bounce;
		newVelocity.y = (m_velocity.y + t*collideDirection.y)*bounce;
		SetVelocity(newVelocity);
	}
}
void ShapeObject::onStayCollision(ShapeObject * collidedObject, Vector2 collideDirection) {}
void ShapeObject::onEndCollision(ShapeObject * collidedObject, Vector2 collideDirection) {}