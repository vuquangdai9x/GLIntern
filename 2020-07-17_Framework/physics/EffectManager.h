#pragma once
#include "Effect.h"
#include "Vector2.h"
#include <vector>
class EffectManager {
protected:
	EffectManager() {}
	~EffectManager() {
		for (int i = 0; i < EffectManager::m_listEffect.size(); i++) {
			delete m_listEffect[i];
		}
	}
	EffectManager(const EffectManager &) {}
	EffectManager& operator =(const EffectManager &) {}

public:
	static void CreateInstance()
	{
		if (ms_pInstance == nullptr)
			ms_pInstance = new EffectManager;
	}
	static EffectManager * GetInstance()
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
	static EffectManager * ms_pInstance;

private:
	std::vector<Effect*> m_listEffect;
public:
	//int numOfParticles, Vector2 m_ExternalForce, float lifeTime, float startVelocity, float startSize, unsigned int uiColor
	void Update(float deltaTime);
	void Render();
	void CreateFirework(Vector2 position, int loopCount = 1, int typeId = -1);
};