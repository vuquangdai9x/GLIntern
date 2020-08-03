#pragma once
#include "ShapeObject.h"

class CollisionInfo {
public:
	ShapeObject * m_collidedObj;
	bool m_collidedOnPrevFrame;
	bool m_collidedOnCurrentFrame;
	CollisionInfo();
	CollisionInfo(ShapeObject * collidedObj, bool collidedOnPrevFrame, bool collidedOnCurrentFrame);
};