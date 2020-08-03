#include "PhysicsManager.h"
#include <vector>
#include "ShapeObject.h"
#include "Rectangle.h"
#include "Circle.h"
#include "SceneManager.h"
#include <math.h>



void PhysicsManager::AddGlobalForce(Vector2 force) {
	std::vector<ShapeObject*> &listObject = SceneManager::GetInstance()->GetListObject();
	for (int i = 0; i < listObject.size(); i++) {
		listObject[i]->AddForce(force);
	}
}

void PhysicsManager::CheckCollision() {
	std::vector<ShapeObject*> &listObject = SceneManager::GetInstance()->GetListObject();
	RectangleShape * ptr_rect_i, *ptr_rect_j;
	CircleShape * ptr_circle_i, *ptr_circle_j;
	for (int i = 0; i < listObject.size(); i++) {
		if (!listObject[i]->m_hasCollider) continue;
		for (int j = i + 1; j < listObject.size(); j++) {
			if (!listObject[j]->m_hasCollider) continue;
			if ((ptr_circle_i = dynamic_cast<CircleShape*>(listObject[i])) != NULL) {
				if ((ptr_circle_j = dynamic_cast<CircleShape*>(listObject[j])) != NULL) {
					if (CheckCollisionCircleCircle(ptr_circle_i, ptr_circle_j)) {
						/*float dx = listObject[i]->GetPosition().x - listObject[j]->GetPosition().x;
						float dy = listObject[i]->GetPosition().y - listObject[j]->GetPosition().y;
						m_collisionDirection = Vector2(dx, dy);*/

						//printf("Circle %d collide with Circle %d\n", i, j);
						ptr_circle_i->onCollision(ptr_circle_j, m_collisionDirection);
						m_collisionDirection.Revert();
						ptr_circle_j->onCollision(ptr_circle_i, m_collisionDirection);
					}
				}
				else if ((ptr_rect_j = dynamic_cast<RectangleShape*>(listObject[j])) != NULL) {
					if (CheckCollisionRectangleCircle(ptr_rect_j, ptr_circle_i)) {
						//printf("Circle %d collide with Rect %d\n", i, j);
						ptr_rect_j->onCollision(ptr_circle_i, m_collisionDirection);
						m_collisionDirection.Revert();
						ptr_circle_i->onCollision(ptr_rect_j, m_collisionDirection);
					}
				}
			}
			else if ((ptr_rect_i = dynamic_cast<RectangleShape*>(listObject[i])) != NULL) {
				if ((ptr_circle_j = dynamic_cast<CircleShape*>(listObject[j])) != NULL) {
					if (CheckCollisionRectangleCircle(ptr_rect_i, ptr_circle_j)) {
						//printf("Rect %d collide with Circle %d\n", i, j);
						ptr_rect_i->onCollision(ptr_circle_j, m_collisionDirection);
						m_collisionDirection.Revert();
						ptr_circle_j->onCollision(ptr_rect_i, m_collisionDirection);
					}
				}
				else if ((ptr_rect_j = dynamic_cast<RectangleShape*>(listObject[j])) != NULL) {
					if (CheckCollisionRectangleRectangle(ptr_rect_i, ptr_rect_j)) {
						//printf("Rect %d collide with Rect %d\n", i, j);
						ptr_rect_i->onCollision(ptr_rect_j, m_collisionDirection);
						m_collisionDirection.Revert();
						ptr_rect_j->onCollision(ptr_rect_i, m_collisionDirection);
					}
				}
			}
		}
	}
}

bool PhysicsManager::CheckCollisionCircleCircle(CircleShape* ptr_c1, CircleShape* ptr_c2) {
	//float dx = ptr_c1->GetPosition().x - ptr_c2->GetPosition().x;
	//float dy = ptr_c1->GetPosition().y - ptr_c2->GetPosition().y;
	//if (sqrt(dx*dx + dy*dy) <= ptr_c1->GetRadius() + ptr_c2->GetRadius()) {
	//	return true;
	//}
	//return false;
	float dx = ptr_c2->GetPosition().x - ptr_c1->GetPosition().x;
	float dy = ptr_c2->GetPosition().y - ptr_c1->GetPosition().y;
	if (sqrt(dx*dx + dy*dy) <= ptr_c1->GetRadius() + ptr_c2->GetRadius()) {
		float d = sqrtf(dx*dx + dy*dy);
		m_collisionDirection = Vector2(dx/d, dy/d);
		return true;
	}
	return false;
}
bool PhysicsManager::CheckCollisionRectangleCircle(RectangleShape* ptr_r, CircleShape* ptr_c) {
	//float radius = ptr_c->GetRadius(),
	//	x = ptr_c->GetPosition().x,
	//	y = ptr_c->GetPosition().y,
	//	left = ptr_r->GetPosition().x,
	//	right = ptr_r->GetPosition().x + ptr_r->GetSize().x,
	//	top = ptr_r->GetPosition().y,
	//	bottom = ptr_r->GetPosition().y + ptr_r->GetSize().y;
	//if (top <= y && y <= bottom) {
	//	if (left - radius <= x && x <= right + radius) {
	//		return true;
	//	}
	//}
	//if (left <= x && x <= right) {
	//	if (top - radius <= y && y <= bottom + radius) {
	//		return true;
	//	}
	//}
	//float dx, dy;
	//if (x < left) dx = left - x;
	//else dx = x - right;
	//if (y < top) dy = top - y;
	//else dy = y - bottom;
	//if (dx*dx + dy*dy < radius*radius) return true;
	//return false;
	float radius = ptr_c->GetRadius(),
		x = ptr_c->GetPosition().x,
		y = ptr_c->GetPosition().y,
		left = ptr_r->GetPosition().x,
		right = ptr_r->GetPosition().x + ptr_r->GetSize().x,
		top = ptr_r->GetPosition().y,
		bottom = ptr_r->GetPosition().y + ptr_r->GetSize().y;

	if (x<left - radius || x>right + radius || y<top - radius || y>bottom + radius) {
		return false;
	}

	// suy bien cac canh ve 0, chi can xet cac truong hop o goc
	float dx, dy;
	if (x < left) dx = x - left;
	else if (x > right) dx = x - right;
	else dx = 0;

	if (y < top) dy = y - top;
	else if (y > bottom) dy = y - bottom;
	else dy = 0;

	if (dx*dx + dy*dy > radius*radius) {
		return false;
	}

	//if (dx == 0 && dy == 0) {
	//	dx = x - (left + right) / 2;
	//	dy = y - (top + bottom) / 2;
	//}

	//// rotate coordinate counter-clockwise 45 degree
	//float sqrt2div2 = sqrt(2) / 2;
	//float dx2 = sqrt2div2*dx + sqrt2div2*dy;
	//float dy2 = -sqrt2div2*dx + sqrt2div2*dy;

	//if (dx2 > 0) {
	//	if (dy2 > 0) {
	//		m_collisionDirection = Vector2(0, 1); //up
	//	}
	//	else {
	//		m_collisionDirection = Vector2(1, 0); //right
	//	}
	//}
	//else {
	//	if (dy2 > 0) {
	//		m_collisionDirection = Vector2(-1, 0); //left
	//	}
	//	else {
	//		m_collisionDirection = Vector2(0, -1); //down
	//	}
	//}

	if (dx == 0 && dy == 0) {
		dx = x - (left + right) / 2;
		dy = y - (top + bottom) / 2;
		float d = sqrtf(dx*dx + dy*dy);
		m_collisionDirection = Vector2(dx/d, dy/d);
	}
	else if (dx == 0) {
		if (dy > 0) m_collisionDirection = Vector2(0, 1); //up
		else m_collisionDirection = Vector2(0, -1); //down
	}
	else if (dy == 0){
		if (dx > 0) m_collisionDirection = Vector2(1, 0); //right
		else m_collisionDirection = Vector2(-1, 0); //left
	}
	else {
		float d = sqrtf(dx*dx + dy*dy);
		m_collisionDirection = Vector2(dx / d, dy / d);
	}
	return true;
}
bool PhysicsManager::CheckCollisionRectangleRectangle(RectangleShape* ptr_r1, RectangleShape* ptr_r2) {
	//if (ptr_r2->GetPosition().x - ptr_r1->GetSize().x <= ptr_r1->GetPosition().x
	//	&& ptr_r1->GetPosition().x <= ptr_r2->GetPosition().x + ptr_r2->GetSize().x
	//	&& ptr_r2->GetPosition().y - ptr_r1->GetSize().y <= ptr_r1->GetPosition().y
	//	&& ptr_r1->GetPosition().y <= ptr_r2->GetPosition().y + ptr_r2->GetSize().y){
	//	return true;
	//}
	//return false;
	if (ptr_r2->GetPosition().x - ptr_r1->GetSize().x <= ptr_r1->GetPosition().x
		&& ptr_r1->GetPosition().x <= ptr_r2->GetPosition().x + ptr_r2->GetSize().x
		&& ptr_r2->GetPosition().y - ptr_r1->GetSize().y <= ptr_r1->GetPosition().y
		&& ptr_r1->GetPosition().y <= ptr_r2->GetPosition().y + ptr_r2->GetSize().y) {
		
		float x = ptr_r2->GetPosition().x + ptr_r2->GetSize().x / 2;
		float y = ptr_r2->GetPosition().y + ptr_r2->GetSize().y / 2;
		float dx, dy;
		if (x < ptr_r1->GetPosition().x) dx = x - ptr_r1->GetPosition().x;
		else if (x > ptr_r1->GetPosition().x + ptr_r1->GetSize().x) dx = x - (ptr_r1->GetPosition().x + ptr_r1->GetSize().x);
		else dx = 0;
		if (y < ptr_r1->GetPosition().y) dy = y - ptr_r1->GetPosition().y;
		else if (y > ptr_r1->GetPosition().y + ptr_r1->GetSize().y) dy = y - (ptr_r1->GetPosition().y + ptr_r1->GetSize().y);
		else dy = 0;

		if (dx == 0 && dy == 0) {
			dx = x - ptr_r1->GetPosition().x + ptr_r1->GetSize().x / 2;
			dy = y - ptr_r1->GetPosition().y + ptr_r1->GetSize().y / 2;
		}

		dx = dx / (float)ptr_r2->GetSize().x;
		dy = dy / (float)ptr_r2->GetSize().y;

		// rotate coordinate counter-clockwise 45 degree
		float sqrt2div2 = sqrt(2) / 2;
		float dx2 = sqrt2div2*dx + sqrt2div2*dy;
		float dy2 = -sqrt2div2*dx + sqrt2div2*dy;

		if (dx2 > 0) {
			if (dy2 > 0) {
				m_collisionDirection = Vector2(0, 1); //down
			}
			else {
				m_collisionDirection = Vector2(1, 0); //right
			}
		}
		else {
			if (dy2 > 0) {
				m_collisionDirection = Vector2(-1, 0); //left
			}
			else {
				m_collisionDirection = Vector2(0, -1); //up
			}
		}
		return true;
	}
	return false;
}

PhysicsManager * PhysicsManager::ms_pInstance = NULL;