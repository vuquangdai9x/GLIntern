#include "CollisionInfo.h"

CollisionInfo::CollisionInfo() {}
CollisionInfo::CollisionInfo(ShapeObject * collidedObj, bool collidedOnPrevFrame, bool collidedOnCurrentFrame) :
	m_collidedObj(collidedObj),
	m_collidedOnPrevFrame(collidedOnPrevFrame),
	m_collidedOnCurrentFrame(collidedOnCurrentFrame)
{}