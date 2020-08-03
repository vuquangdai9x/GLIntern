#pragma once
#include "Vector2.h"
#include "Rectangle.h"
#include "Circle.h"

class PhysicsManager {
protected:
	PhysicsManager() {}
	~PhysicsManager() {}
	PhysicsManager(const PhysicsManager &) {}
	PhysicsManager& operator =(const PhysicsManager &) {}

public:
	static void CreateInstance()
	{
		if (ms_pInstance == nullptr)
			ms_pInstance = new PhysicsManager;
	}
	static PhysicsManager * GetInstance()
	{
		return ms_pInstance;
	}
	static void DestroyInstance()
	{
		if (ms_pInstance)
		{
			delete ms_pInstance;
			ms_pInstance = nullptr;
		}
	}

	void SomeFunction() {}

protected:
	static PhysicsManager * ms_pInstance;
private:
	Vector2 m_collisionDirection = Vector2();
	bool CheckCollisionCircleCircle(CircleShape* ptr_c1, CircleShape* ptr_c2);
	bool CheckCollisionRectangleCircle(RectangleShape* ptr_r, CircleShape* ptr_c);
	bool CheckCollisionRectangleRectangle(RectangleShape* ptr_r1, RectangleShape* ptr_r2);
public:
	void AddGlobalForce(Vector2 force);
	void CheckCollision();
};