#pragma once
#include "Vector2.h"
#include "ShapeObject.h"

class TouchManager {
protected:
	TouchManager() {}
	~TouchManager() {}
	TouchManager(const TouchManager &) {}
	TouchManager& operator =(const TouchManager &) {}
public:
	static void CreateInstance()
	{
		if (ms_pInstance == nullptr)
			ms_pInstance = new TouchManager;
	}
	static TouchManager * GetInstance()
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
	static TouchManager * ms_pInstance;

private:
	float m_updatePosInterval = 0.1;
	float m_timeCounter;
	float m_moveMultiplier = 10;
	Vector2 m_prevPos;
	ShapeObject * m_AffectedObject = NULL;
	Vector2 m_DeltaPos; //NOTE: distance between shape anchor and touch position
public:
	void OnTouchScreen(int x, int y);

	void HoldObject(int x, int y);
	void MoveAffectedObject(int x, int y);
	void ReleaseObject(int x, int y);
};