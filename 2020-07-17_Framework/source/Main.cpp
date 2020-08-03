#include <stdio.h>
#include "esUtil.h"
#include "log.h"
#include "define.h"
#include "VideoDriver.h"
#include <crtdbg.h>
#include "SceneManager.h"
#include "TouchManager.h"
#include "PhysicsManager.h"
#include "EffectManager.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

void PaintObject()
{
	// Limit FPS
	DWORD start, end;
	start = GetTickCount();

	// Render something here
	VideoDriver::GetInstance()->CleanScreen();

	// ---> Render
	SceneManager::GetInstance()->Render();

	// Limit FPS
	end = GetTickCount();
	DWORD frameTime = end - start;
	if (frameTime < 1000.0/LIMIT_FPS)
		Sleep(1000/LIMIT_FPS - frameTime);
}

bool InitGraphics(int w, int h)
{
	// Init scene
	LOGI("Initializing...");
	glViewport(0, 0, w, h);

	

	LOGI("Done!");
	return true;
}

void TouchActionDown(ESContext *esContext,int x, int y)
{
	// Mouse down
	TouchManager::GetInstance()->OnTouchScreen(x, y);
	TouchManager::GetInstance()->HoldObject(x, y);
}

void TouchActionUp(ESContext *esContext,int x, int y)
{
	// Mouse up
	TouchManager::GetInstance()->ReleaseObject(x,y);
}

void TouchActionMove(ESContext *esContext,int x, int y)
{
	// Mouse move
	TouchManager::GetInstance()->MoveAffectedObject(x, y);
}

void KeyDown(ESContext *ESContext, unsigned char keyCode, int x, int y)
{
	float forceStrength = 200;
	switch (keyCode)
	{
	case 'W':
	case 'w':
		PhysicsManager::GetInstance()->AddGlobalForce(Vector2(0,-forceStrength));
		break;
	case 'S':
	case 's':
		PhysicsManager::GetInstance()->AddGlobalForce(Vector2(0, forceStrength));
		break;
	case 'A':
	case 'a':
		PhysicsManager::GetInstance()->AddGlobalForce(Vector2(-forceStrength,0));
		break;
	case 'D':
	case 'd':
		PhysicsManager::GetInstance()->AddGlobalForce(Vector2(forceStrength, 0));
		break;
	case ' ':
		EffectManager::GetInstance()->CreateFirework(Vector2(0, 0), 1, 1);
		break;
	}
}

void KeyUp(ESContext *ESContext, unsigned char keyCode, int x, int y)
{
	switch (keyCode)
	{
	case 'W':
	case 'w':
		break;
	case 'S':
	case 's':
		break;
	case 'A':
	case 'a':
		break;
	case 'D':
	case 'd':
		break;
	}
}

void GameUpdate(ESContext *esContext, float deltaTime)
{
	// ---> Update
	SceneManager::GetInstance()->m_frameTime = deltaTime;
	SceneManager::GetInstance()->Update(deltaTime);
}

void GameDraw(ESContext *esContext)
{
	// Draw scene then swap buffer to display to screen
	PaintObject();
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void GameExit()
{
	// ---> Destroy Allocated Object
	SceneManager::DestroyInstance();
}

int main(int argc, char *argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// ---> Init Scene Manager
	SceneManager::CreateInstance();
	SceneManager::GetInstance()->Init();

	ESContext esContext;
	esInitContext(&esContext );

	esCreateWindow(&esContext, "Framework", (int)SCREEN_W, (int)SCREEN_H, ES_WINDOW_RGB);
	if (!InitGraphics((int)SCREEN_W, (int)SCREEN_H))
		return 0;

	esRegisterDrawFunc(&esContext, GameDraw);
	esRegisterKeyDownFunc(&esContext, KeyDown);
	esRegisterKeyUpFunc(&esContext, KeyUp);
	esRegisterUpdateFunc(&esContext, GameUpdate);
	esRegisterMouseDownFunc(&esContext, TouchActionDown);
	esRegisterMouseUpFunc(&esContext, TouchActionUp);
	esRegisterMouseMoveFunc(&esContext, TouchActionMove);
	esMainLoop(&esContext);
	GameExit();

	_CrtDumpMemoryLeaks();
}