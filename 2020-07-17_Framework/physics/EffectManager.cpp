#include "EffectManager.h"
#include "Firework.h"



void EffectManager::Update(float deltaTime) {
	int index = 0;
	for (std::vector<Effect*>::iterator iter = m_listEffect.begin(); iter != m_listEffect.end(); /*do nothing*/) {
		(*iter)->Update(deltaTime);
		if ((*iter)->m_iLoopCount == 0) {
			delete m_listEffect[index];
			iter = m_listEffect.erase(iter);
		}
		else {
			iter++;
			index++;
		}
	}
}
void EffectManager::Render() {
	for (int i = 0; i < EffectManager::m_listEffect.size(); i++) {
		m_listEffect[i]->Render();
	}
}
void EffectManager::CreateFirework(Vector2 position, int loopCount, int typeId) {
	m_listEffect.push_back(Firework::CreateFirework(position, loopCount, typeId));
}

EffectManager * EffectManager::ms_pInstance = nullptr;