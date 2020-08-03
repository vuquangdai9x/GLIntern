#pragma once
#include "Rectangle.h"
#include "videoDriver.h"

class PlaneShape : public RectangleShape {
private:
	bool m_isVerticalPlane;
	float bounce = 0.8;
public:
	PlaneShape(bool isVerticalPlane, float posX, float posY, float width, float height, float mass = 1, float vx = 0, float vy = 0) :
		RectangleShape(posX, posY, width, height, mass, vx, vy),
		m_isVerticalPlane(isVerticalPlane)
	{
		m_isRigid = false;
		m_isTouchDetectable = false;
		m_hasCollider = true;
	}

	void onStartCollision(ShapeObject * collidedObject, Vector2 collideDirection) {
		ShapeObject::onStartCollision(collidedObject, collideDirection);
	}

	// TODO: fix error slow velocity make object get through plane
	//virtual void onStartCollision(ShapeObject * collidedObject, Vector2 collideDirection) {
	//	if (collidedObject->m_isRigid) {
	//		Vector2 collidedObjectVelocity = collidedObject->GetVelocity();
	//		if (m_isVerticalPlane) {
	//			collidedObject->SetVelocity(Vector2(-collidedObjectVelocity.x*bounce, collidedObjectVelocity.y));
	//		}
	//		else {
	//			collidedObject->SetVelocity(Vector2(collidedObjectVelocity.x, -collidedObjectVelocity.y*bounce));
	//		}
	//	}
	//}

	//virtual void onStayCollision(ShapeObject * collidedObject, Vector2 collideDirection) {
	//	if (collidedObject->m_isRigid) {
	//		float velocity_threshold = 1;
	//		Vector2 collidedObjectVelocity = collidedObject->GetVelocity();
	//		if (m_isVerticalPlane) {
	//			if (fabs(collidedObjectVelocity.x) < velocity_threshold) {
	//				collidedObject->AddForce(Vector2(-collidedObject->GetForce().x, 0));
	//				collidedObject->SetVelocity(Vector2(0, collidedObjectVelocity.y));
	//			}
	//		}
	//		else {
	//			if (fabs(collidedObjectVelocity.y) < velocity_threshold) {
	//				collidedObject->AddForce(Vector2(0, -collidedObject->GetForce().y));
	//				collidedObject->SetVelocity(Vector2(collidedObjectVelocity.x, 0));
	//			}
	//		}
	//	}
	//}
};