#include "stdafx.h"
#include "SceneManager.h"
#include <math.h>
#include "Globals.h"

SceneManager::~SceneManager()
{
	for (int i = 0; i < m_listObject.size(); i++) {
		m_listObject[i]->OnDestroy();
		delete m_listObject[i];
	}
	delete m_mainCamera;
}

void SceneManager::Init(char * dataSceneFile) {
	m_fogStart = 750;
	m_fogLength = 300;
	m_fogColor = Vector4(1,.9,.9,1);

	const char *resourceDir = Globals::resourceDir;
	char filePath[512];
	strcpy(filePath, resourceDir);
	strcat(filePath, dataSceneFile);
	FILE * fIn = fopen(filePath, "r");
	if (fIn == nullptr) {
		printf("Fails to load scene file");
		return;
	}

	GameObject * obj;
	int iNumOfObject, iObjectId = 0;
	int iModelId;
	int iMaterialId;
	/*int iNumOfTexture, iNumOfCubeTexture, iShaderId;
	int * aiTextureId, *aiCubeTexId;*/
	Vector3 position, rotation, scale;
	fscanf(fIn, "#Objects: %d\n", &iNumOfObject);
	for (int i = 0; i < iNumOfObject; i++) {
		obj = new GameObject(iObjectId);

		fscanf(fIn, "\nID %d\n", &iObjectId);
		fscanf(fIn, "MODEL %d\n", &iModelId);

		/*fscanf(fIn, "TEXTURES %d\n", &iNumOfTexture);
		aiTextureId = new int[iNumOfTexture];
		for (int j = 0; j < iNumOfTexture; j++) {
			fscanf(fIn, "TEXTURE %d\n", aiTextureId + j);
		}

		fscanf(fIn, "CUBETEXTURE %d\n", &iNumOfCubeTexture);
		aiCubeTexId = new int[iNumOfCubeTexture];
		for (int j = 0; j < iNumOfCubeTexture; j++) {
			fscanf(fIn, "CUBETEX %d\n", aiCubeTexId + j);
		}

		fscanf(fIn, "SHADER %d\n", &iShaderId);*/

		//obj->GetRenderer().Init(iModelId, iNumOfTexture, aiTextureId, iNumOfCubeTexture, aiCubeTexId, iShaderId);
		
		fscanf(fIn, "MATERIAL %d\n", &iMaterialId); 
		fscanf(fIn, "POSITION %f %f %f\n", &(position.x), &(position.y), &(position.z));
		fscanf(fIn, "ROTATION %f %f %f\n", &(rotation.x), &(rotation.y), &(rotation.z));
		rotation = rotation * 2 * 3.1416 / 360;
		fscanf(fIn, "SCALE %f %f %f\n", &(scale.x), &(scale.y), &(scale.z));
		
		obj->Init(position,rotation,scale, iModelId, iMaterialId);
		
		AddObject(obj);

		/*delete[] aiCubeTexId;
		delete[] aiTextureId;*/

		printf("[msg] SceneManager: Loaded Object %d\n",iObjectId);
	}

	float nearPlane, farPlane, fov, angleLimit;
	float moveSpeedX, moveSpeedY, moveSpeedZ, rotateSpeedV, rotateSpeedH, dutchSpeed;
	Vector3 target;
	fscanf(fIn, "\n#CAMERA\n");
	fscanf(fIn, "NEAR %f\n", &nearPlane);
	fscanf(fIn, "FAR %f\n", &farPlane);
	fscanf(fIn, "FOV %f\n", &fov);
	fscanf(fIn, "LIMIT %f\n", &angleLimit);
	angleLimit = angleLimit * 2 * M_PI / 360;
	fscanf(fIn, "MOVE SPEED %f %f %f\n", &moveSpeedX, &moveSpeedY, &moveSpeedZ);
	fscanf(fIn, "ROTATE SPEED %f %f\n", &rotateSpeedH, &rotateSpeedV);
	fscanf(fIn, "DUTCH SPEED %f\n", &dutchSpeed);
	rotateSpeedH = rotateSpeedH * 2 * M_PI / 360;
	rotateSpeedV = rotateSpeedV * 2 * M_PI / 360;
	dutchSpeed = dutchSpeed * 2 * M_PI / 360;
	fscanf(fIn, "POSITION %f %f %f\n", &(position.x), &(position.y), &(position.z));
	fscanf(fIn, "TARGET %f %f %f\n", &(target.x), &(target.y), &(target.z));
	rotation = rotation * 2 * 3.1416 / 360;
	Camera * camera = new Camera();
	camera->Init(position, target, nearPlane, farPlane, fov, Globals::screenWidth/(float)Globals::screenHeight, angleLimit);
	camera->SetSpeed(moveSpeedX, moveSpeedY, moveSpeedZ, rotateSpeedH, rotateSpeedV, dutchSpeed);
	SetMainCamera(camera);
	printf("[msg] SceneManager: Set up Camera\n");

	obj = NULL;
	camera = NULL;
}

void SceneManager::SetMainCamera(Camera * camera)
{
	m_mainCamera = camera;
}

Camera & SceneManager::GetMainCamera()
{
	return *m_mainCamera;
}

void SceneManager::Update(float frameTime) {
	for (int i = 0; i < m_listObject.size(); i++) {
		m_listObject[i]->Update(frameTime);
	}
}
void SceneManager::Render() {
	for (int i = 0; i < m_listObject.size(); i++) {
		m_listObject[i]->Render(m_mainCamera);
	}
}
void SceneManager::AddObject(GameObject *object) {
	m_listObject.push_back(object);
	object->Init();
}
GameObject& SceneManager::GetObject(int id)
{
	for (int i = 0; i < m_listObject.size(); i++) {
		if (m_listObject[i]->GetId() == id)
			return *(m_listObject[i]);
	}
}
//void SceneManager::RemoveObject(GameObject *object) {
//	int index = 0;
//	for (std::vector<GameObject*>::iterator iter = m_listObject.begin(); iter != m_listObject.end(); /*do nothing*/) {
//		if ((*iter) == object) {
//			m_listObject[index]->OnDestroy();
//			delete m_listObject[index];
//			iter = m_listObject.erase(iter);
//		}
//		else {
//			iter++;
//			index++;
//		}
//	}
//}

std::vector<GameObject*>& SceneManager::GetListObject() {
	return m_listObject;
}

SceneManager * SceneManager::ms_pInstance = NULL;