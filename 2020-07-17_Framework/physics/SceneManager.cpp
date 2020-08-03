#include "SceneManager.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Plane.h"
#include "PhysicsManager.h"
#include "TouchManager.h"
#include "EffectManager.h"

void SceneManager::Update(float frameTime) {
	PhysicsManager::GetInstance()->AddGlobalForce(Vector2(0, 9.8)); // NOTE: Add gravity
	PhysicsManager::GetInstance()->CheckCollision();
	for (int i = 0; i < SceneManager::m_listObject.size(); i++) {
		m_listObject[i]->Update(frameTime);
	}
	EffectManager::GetInstance()->Update(frameTime);
}
void SceneManager::Render() {
	for (int i = 0; i < SceneManager::m_listObject.size(); i++) {
		m_listObject[i]->Render();
	}
	EffectManager::GetInstance()->Render();
}
void SceneManager::AddObject(ShapeObject *object) {
	m_listObject.push_back(object);
}
//void SceneManager::RemoveObject(Object *object) {
//	delete object;
//}

void SceneManager::Init() {
	printf("Initing objects\n");
	FILE* fIn_ObjectList = fopen("./physics/ObjectList.txt", "r");
	int iNumOfObject;

	fscanf(fIn_ObjectList, "#OBJECT_NUM %d\n", &iNumOfObject);
	printf("Num of objects: %d\n",iNumOfObject);

	int iId;
	float mass;
	char strType[7];
	for (int i = 0; i < iNumOfObject; i++) {
		fscanf(fIn_ObjectList, "\n#ID %d\n", &iId);
		fscanf(fIn_ObjectList, "TYPE: %s\n", strType);
		printf("ObjectID #%d: %s\n",iId,strType);

		if (strcmp("RECT", strType) == 0) {
			int iPosX, iPosY, iWidth, iHeight, iVx, iVy;
			fscanf(fIn_ObjectList, "POSITION: %d, %d, %d, %d\n", &iPosX, &iPosY, &iWidth, &iHeight);
			fscanf(fIn_ObjectList, "VELOCITY: %d\n", &iVy);
			fscanf(fIn_ObjectList, "MASS: %f\n", &mass);
			iVx = 0;
			m_listObject.push_back(new RectangleShape(iPosX, iPosY, iWidth, iHeight, mass, iVx, iVy));
			printf("Load RECT #%d \n\tSize: %d,%d \n\tPosition: %d,%d \n\tVelocity: %d,%d \n", iId, iWidth, iHeight, iPosX, iPosY, iVx, iVy);
		}else if (strcmp("CIRCLE", strType) == 0) {
			int iPosX, iPosY, iRadius, iVx, iVy;
			fscanf(fIn_ObjectList, "POSITION: %d, %d, %d\n", &iPosX, &iPosY, &iRadius);
			fscanf(fIn_ObjectList, "VELOCITY: %d\n", &iVy);
			fscanf(fIn_ObjectList, "MASS: %f\n", &mass);
			iVx = 0;
			m_listObject.push_back(new CircleShape(iPosX, iPosY, iRadius, mass, iVx, iVy));
			printf("Load CIRCLE #%d \n\tRadius: %d \n\tPosition: %d,%d \n\tVelocity: %d,%d \n", iId, iRadius, iPosX, iPosY, iVx, iVy);
		}
		else if (strcmp("PLANE", strType) == 0) {
			int iPosX, iPosY, iWidth, iHeight, iVx, iVy;
			fscanf(fIn_ObjectList, "POSITION: %d, %d, %d, %d\n", &iPosX, &iPosY, &iWidth, &iHeight);
			fscanf(fIn_ObjectList, "VELOCITY: %d\n", &iVy);
			iVx = 0;
			bool isVeticalPlane = ((iWidth < iHeight) ? true : false);
			m_listObject.push_back(new PlaneShape(isVeticalPlane,iPosX, iPosY, iWidth, iHeight, 0, iVx, iVy));
			printf("Load PLANE #%d \n\tSize: %d,%d \n\tPosition: %d,%d \n\tVelocity: %d,%d \n", iId, iWidth, iHeight, iPosX, iPosY, iVx, iVy);
		}
	}
	fclose(fIn_ObjectList);

	PhysicsManager::CreateInstance();
	TouchManager::CreateInstance();
	EffectManager::CreateInstance();
}

//void SceneManager::Init() {
//	m_listObject.push_back(new PlaneShape(false, 1, 1, 799, 1)); // top plane
//	m_listObject.push_back(new PlaneShape(true, 1, 1, 1, 479)); // left plane
//	m_listObject.push_back(new PlaneShape(true, 799, 1, 1, 479)); // right plane
//	m_listObject.push_back(new PlaneShape(false, 1, 479, 799, 1)); // bottom plane
//	m_listObject.push_back(new RectangleShape(200, 100, 50, 50, 1, 0, 20));
//	m_listObject.push_back(new RectangleShape(600, 100, 50, 80, 1, 0, 20));
//	m_listObject.push_back(new CircleShape(120, 100, 50, 1, 0, 10));
//	m_listObject.push_back(new CircleShape(420, 100, 70, 1, 0, 10));
//
//	PhysicsManager::CreateInstance();
//	TouchManager::CreateInstance();
//	EffectManager::CreateInstance();
//}

std::vector<ShapeObject*>& SceneManager::GetListObject() {
	return m_listObject;
}

SceneManager * SceneManager::ms_pInstance = NULL;

void SceneManager::OnDestroy() {
	PhysicsManager::DestroyInstance();
	TouchManager::DestroyInstance();
	EffectManager::DestroyInstance();
}