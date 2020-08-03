#include "stdafx.h"
#include "InputManager.h"

#include "SceneManager.h"

InputManager * InputManager::ms_pInstance = nullptr;

InputManager::InputManager()
{
	m_maskKeyPressedPrevFrame = 0;
	m_maskKeyPressed = 0;
}

inline void SetBit(unsigned int& mask, int offset)
{
	mask |= (1 << offset);
}
inline void UnsetBit(unsigned int& mask, int offset)
{
	mask &= (~(1 << offset));
}

inline int GetBit(unsigned int& mask, int offset)
{
	return (mask >> offset) & 0x01;
}

void InputManager::KeyPressed(unsigned char key, bool isKeyPressed)
{
	if (isKeyPressed) {
		switch (key)
		{
		case 'a':
		case 'A':
			SetBit(m_maskKeyPressed, Key::A);
			break;
		case 's':
		case 'S':
			SetBit(m_maskKeyPressed, Key::S);
			break;
		case 'd':
		case 'D':
			SetBit(m_maskKeyPressed, Key::D);
			break;
		case 'w':
		case 'W':
			SetBit(m_maskKeyPressed, Key::W);
			break;
		case VK_LSHIFT:
		case VK_RSHIFT:
		case VK_SHIFT:
			SetBit(m_maskKeyPressed, Key::LSHIFT);
			break;
		case VK_SPACE:
			SetBit(m_maskKeyPressed, Key::SPACE);
			break;
		case VK_UP:
			SetBit(m_maskKeyPressed, Key::UP);
			break;
		case VK_DOWN:
			SetBit(m_maskKeyPressed, Key::DOWN);
			break;
		case VK_LEFT:
			SetBit(m_maskKeyPressed, Key::LEFT);
			break;
		case VK_RIGHT:
			SetBit(m_maskKeyPressed, Key::RIGHT);
			break;
		}
	}
	else {
		switch (key)
		{
		case 'a':
		case 'A':
			UnsetBit(m_maskKeyPressed, Key::A);
			break;
		case 's':
		case 'S':
			UnsetBit(m_maskKeyPressed, Key::S);
			break;
		case 'd':
		case 'D':
			UnsetBit(m_maskKeyPressed, Key::D);
			break;
		case 'w':
		case 'W':
			UnsetBit(m_maskKeyPressed, Key::W);
			break;
		case VK_LSHIFT:
		case VK_RSHIFT:
		case VK_SHIFT:
			UnsetBit(m_maskKeyPressed, Key::LSHIFT);
			break;
		case VK_SPACE:
			UnsetBit(m_maskKeyPressed, Key::SPACE);
			break;
		case VK_UP:
			UnsetBit(m_maskKeyPressed, Key::UP);
			break;
		case VK_DOWN:
			UnsetBit(m_maskKeyPressed, Key::DOWN);
			break;
		case VK_LEFT:
			UnsetBit(m_maskKeyPressed, Key::LEFT);
			break;
		case VK_RIGHT:
			UnsetBit(m_maskKeyPressed, Key::RIGHT);
			break;
		}
	}

	/*switch (key)
	{
	case 'a':
	case 'A':
		SceneManager::GetInstance()->GetMainCamera().MoveRelative(Vector3(-1,0,0));
		break;
	case 's':
	case 'S':
		SceneManager::GetInstance()->GetMainCamera().MoveRelative(Vector3(0, 0, -1));
		break;
	case 'd':
	case 'D':
		SceneManager::GetInstance()->GetMainCamera().MoveRelative(Vector3(1, 0, 0));
		break;
	case 'w':
	case 'W':
		SceneManager::GetInstance()->GetMainCamera().MoveRelative(Vector3(0, 0, 1));
		break;
	case VK_LSHIFT:
	case VK_RSHIFT:
	case VK_SHIFT:
		SceneManager::GetInstance()->GetMainCamera().Fly(false);
		break;
	case VK_SPACE:
		SceneManager::GetInstance()->GetMainCamera().Fly(true);
		break;
	case VK_UP:
		SceneManager::GetInstance()->GetMainCamera().Rotate(Vector3(-1, 0, 0));
		break;
	case VK_DOWN:
		SceneManager::GetInstance()->GetMainCamera().Rotate(Vector3(1, 0, 0));
		break;
	case VK_LEFT:
		SceneManager::GetInstance()->GetMainCamera().Rotate(Vector3(0, -1, 0));
		break;
	case VK_RIGHT:
		SceneManager::GetInstance()->GetMainCamera().Rotate(Vector3(0, 1, 0));
		break;
	}*/


	/*if (key == 'a' || key == 'A') 
	if (key == 's' || key == 'S') 
	if (key == 'd' || key == 'D') 
	if (key == 'w' || key == 'W') 
	if (key == VK_LSHIFT || key == VK_RSHIFT || key == VK_SHIFT) 
	if (key == VK_SPACE) 
	if (key == VK_UP) 
	if (key == VK_DOWN) 
	if (key == VK_LEFT) 
	if (key == VK_RIGHT) */
}

void InputManager::Update(float deltaTime) {
	Vector3 cameraMoveDirection(0,0,0);
	cameraMoveDirection.x -= GetBit(m_maskKeyPressed, Key::A);
	cameraMoveDirection.x += GetBit(m_maskKeyPressed, Key::D);
	cameraMoveDirection.z -= GetBit(m_maskKeyPressed, Key::S);
	cameraMoveDirection.z += GetBit(m_maskKeyPressed, Key::W);
	SceneManager::GetInstance()->GetMainCamera().MoveRelative(cameraMoveDirection);
	//SceneManager::GetInstance()->GetMainCamera().MoveSmooth(cameraMoveDirection);

	int flyDirection = GetBit(m_maskKeyPressed, Key::SPACE) - GetBit(m_maskKeyPressed, Key::LSHIFT);
	SceneManager::GetInstance()->GetMainCamera().Fly(flyDirection);
	//SceneManager::GetInstance()->GetMainCamera().FlySmooth(flyDirection);

	Vector3 cameraRotateDirection(0, 0, 0);
	cameraRotateDirection.x -= GetBit(m_maskKeyPressed, Key::UP);
	cameraRotateDirection.x += GetBit(m_maskKeyPressed, Key::DOWN);
	cameraRotateDirection.y -= GetBit(m_maskKeyPressed, Key::LEFT);
	cameraRotateDirection.y += GetBit(m_maskKeyPressed, Key::RIGHT);
	SceneManager::GetInstance()->GetMainCamera().Rotate(cameraRotateDirection);
	//SceneManager::GetInstance()->GetMainCamera().RotateSmooth(cameraRotateDirection);
}