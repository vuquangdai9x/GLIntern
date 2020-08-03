#pragma once
#include "stdafx.h"

class Camera {
private:
	Matrix m_PerspectiveMatrix, m_ViewMatrix;
	Vector3 m_target;
	Vector3 m_up, m_xaxis, m_yaxis, m_zaxis;
	Vector3 m_position;
	float m_rotateLimit; // determine what angle with UP vector that can't rotate to (radian)

	Vector3 m_rotateDirection, m_moveDirection;
	int m_flyDirection;
	float m_smoothTime, m_timeCounterMove, m_timeCounterFly, m_timeCounterRotate;
	float(*m_smoothFunc)(float, float, float);
	float m_moveSpeed, m_flySpeed, m_rotateSpeed; // rad/s

	void UpdateViewMatrix();
public:
	Camera();
	void Init(Vector3 position, Vector3 target, float nearPlane, float farPlane, float FOV, float aspectRatio);
	void SetSpeed(float move, float fly, float rotate);
	void Update(float deltaTime);
	void OnDestroy();

	void MoveRelative(Vector3 localDirection, float speedMultiplier = 1);
	void Move(Vector3 worldDirection, float speedMultiplier = 1);
	void Rotate(Vector3 direction, float speedMultiplier = 1);
	void Fly(int direction, float speedMultiplier = 1);

	void MoveSmooth(Vector3 localDirection);
	void RotateSmooth(Vector3 rotateDirection);
	void FlySmooth(int flyDirection);

	Matrix & GetViewMatrix();
	Matrix & GetPerspectiveMatrix();
};