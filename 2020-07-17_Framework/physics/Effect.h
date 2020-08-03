#pragma once
#include "Vector2.h"
class Effect {
public:
	Vector2 m_position;
	int m_iLoopCount;
	bool m_isEnabled = true;

	Effect(Vector2 position, int loopCount=1) : m_position(position), m_iLoopCount(loopCount) {
	}

	virtual ~Effect(){}

	virtual void Update(float deltaTime) {
		if (!m_isEnabled) return;
	}
	virtual void Render() {
		if (!m_isEnabled) return;
	}
};