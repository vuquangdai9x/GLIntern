#pragma once
class InputManager {
protected:
	InputManager();
	~InputManager() {}
	InputManager(const InputManager &) {}
	InputManager& operator =(const InputManager &) {}
public:
	static void CreateInstance()
	{
		if (ms_pInstance == nullptr)
			ms_pInstance = new InputManager;
	}
	static InputManager * GetInstance()
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
	static InputManager * ms_pInstance;

private:
	unsigned int m_maskKeyPressed, m_maskKeyPressedPrevFrame;
	float m_smoothTime;
	enum Key {A,D,W,S,LSHIFT,SPACE,UP,DOWN,LEFT,RIGHT};

	//void SetBit(unsigned int mask, int offset);
	//bool CheckBit(unsigned int mask, int offset);
public:
	void KeyPressed(unsigned char key, bool isKeyPressed);
	void Update(float deltaTime);
};