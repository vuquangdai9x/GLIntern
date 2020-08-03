#pragma once
#include "Vector2.h"
#include <vector>
#include "define.h"
#include "EffectManager.h"

class ShapeObject {
	struct CollisionInfo {
	public:
		ShapeObject * m_collidedObj;
		bool m_collidedOnPrevFrame;
		bool m_collidedOnCurrentFrame;
		Vector2 m_direction;
		CollisionInfo() {}
		CollisionInfo(ShapeObject * collidedObj, Vector2 direction) :
			m_collidedObj(collidedObj),
			m_direction(direction),
			m_collidedOnPrevFrame(false),
			m_collidedOnCurrentFrame(true)
		{}
	};
protected:
	Vector2 m_position;
	float m_mass;
	Vector2 m_velocity;
	Vector2 m_SumForce;
	bool m_isOnCollision;
	std::vector<CollisionInfo> m_listCollisionInfo;
public:
	bool m_isRigid;
	bool m_isTouchDetectable;
	bool m_hasCollider;
public:
	ShapeObject(Vector2 position, bool isRigid, bool isTouchDetectable, bool hasCollider, float mass, Vector2 velocity);
	virtual void Render() = 0;
	void Update(float frameTime);
	void AddForce(Vector2 force);
	Vector2 GetForce();
	Vector2 & GetPosition();
	void moveTo(float x, float y);
	virtual bool CheckIsTouchInside(int x, int y) = 0;
	float GetMass();
	void SetVelocity(Vector2 new_velocity);
	Vector2 GetVelocity();
	void onCollision(ShapeObject * collidedObject, Vector2 collisionDirection);
	virtual void onStartCollision(ShapeObject * collidedObject, Vector2 collideDirection);
	virtual void onStayCollision(ShapeObject * collidedObject, Vector2 collideDirection);
	virtual void onEndCollision(ShapeObject * collidedObject, Vector2 collideDirection);
};

