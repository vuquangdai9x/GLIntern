#include "TouchManager.h"
#include "SceneManager.h"
#include <vector>
#include "ShapeObject.h"
#include "EffectManager.h"

void TouchManager::OnTouchScreen(int x, int y) {
	EffectManager::GetInstance()->CreateFirework(Vector2(x, y), 1, 0);
}

void TouchManager::HoldObject(int x, int y) {
	std::vector<ShapeObject*> &listObject = SceneManager::GetInstance()->GetListObject();
	for (int i = 0; i < listObject.size(); i++) {
		if (listObject[i]->CheckIsTouchInside(x,y)) {
			m_AffectedObject = listObject[i];
			m_DeltaPos.x = m_AffectedObject->GetPosition().x - x;
			m_DeltaPos.y = m_AffectedObject->GetPosition().y - y;
			m_AffectedObject->SetVelocity(Vector2(0, 0));
			m_AffectedObject->m_isRigid = false;

			m_prevPos = Vector2(x, y);
			m_timeCounter = 0;
			break;
		}
	} 
	
}
void TouchManager::MoveAffectedObject(int x, int y) {
	if (m_AffectedObject != NULL) {
		m_AffectedObject->moveTo(x + m_DeltaPos.x, y + m_DeltaPos.y);
		m_timeCounter += SceneManager::GetInstance()->m_frameTime;
		if (m_timeCounter > m_updatePosInterval) {
			m_timeCounter = 0;
			m_prevPos.x = x;
			m_prevPos.y = y;
		}
	}
}
void TouchManager::ReleaseObject(int x, int y) {
	float frameTime = SceneManager::GetInstance()->m_frameTime;
	if (m_AffectedObject != NULL) {
		m_AffectedObject->m_isRigid = true;
		Vector2 newVelocity = Vector2(0, 0);
		//Vector2 newVelocity = Vector2((x - m_prevPos.x)*METER_PER_PIXEL / m_updatePosInterval * m_moveMultiplier, (y - m_prevPos.y)*METER_PER_PIXEL / m_updatePosInterval * m_moveMultiplier);
		m_AffectedObject->SetVelocity(newVelocity);
	}		
	m_AffectedObject = NULL;
}

TouchManager * TouchManager::ms_pInstance = NULL;