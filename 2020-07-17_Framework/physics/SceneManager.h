#pragma once
#include "ShapeObject.h"
#include <vector>

class SceneManager
{
protected:
	SceneManager() {}
	~SceneManager() {
		for (int i = 0; i < SceneManager::m_listObject.size(); i++) {
			delete m_listObject[i];
		}
	}
	SceneManager(const SceneManager &) {}
	SceneManager& operator =(const SceneManager &) {}

public:
	static void CreateInstance()
	{
		if (ms_pInstance == nullptr)
			ms_pInstance = new SceneManager;
	}
	static SceneManager * GetInstance()
	{
		return ms_pInstance;
	}
	static void DestroyInstance()
	{
		if (ms_pInstance)
		{
			ms_pInstance->OnDestroy();
			delete ms_pInstance;
			ms_pInstance = nullptr;
		}
	}

protected:
	static SceneManager * ms_pInstance;
private:

public:
	std::vector<ShapeObject*> m_listObject;
	float m_frameTime;
public:
	void Update(float frameTime);
	void Render();
	void AddObject(ShapeObject *object);
	void RemoveObject(ShapeObject *object);
	void Init();
	void OnDestroy();
	std::vector<ShapeObject*>& GetListObject();
};