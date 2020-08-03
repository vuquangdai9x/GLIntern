#include "stdafx.h"
#include "Camera.h"
#include "AnimationFunction.h"

void Camera::UpdateViewMatrix()
{
	m_ViewMatrix.m[0][0] = m_xaxis.x;				m_ViewMatrix.m[0][1] = m_yaxis.x;				m_ViewMatrix.m[0][2] = m_zaxis.x;				m_ViewMatrix.m[0][3] = 0.0f;
	m_ViewMatrix.m[1][0] = m_xaxis.y;				m_ViewMatrix.m[1][1] = m_yaxis.y;				m_ViewMatrix.m[1][2] = m_zaxis.y;				m_ViewMatrix.m[1][3] = 0.0f;
	m_ViewMatrix.m[2][0] = m_xaxis.z;				m_ViewMatrix.m[2][1] = m_yaxis.z;				m_ViewMatrix.m[2][2] = m_zaxis.z;				m_ViewMatrix.m[2][3] = 0.0f;
	m_ViewMatrix.m[3][0] =-m_position.Dot(m_xaxis);	m_ViewMatrix.m[3][1] =-m_position.Dot(m_yaxis);	m_ViewMatrix.m[3][2] =-m_position.Dot(m_zaxis);	m_ViewMatrix.m[3][3] = 1.0f;
}

Camera::Camera()
{
	m_smoothTime = 0.2f;
	m_smoothFunc = AnimationFunction::EaseOutCirc;
	m_moveSpeed = 0.05;
	m_flySpeed = 0.05;
	m_rotateSpeed = 0.5 * (2 * 3.1416 / 360);
	m_up = Vector3(0, 1, 0);
	m_rotateLimit = 10 * (2 * 3.1416 / 360);
	m_timeCounterMove = m_timeCounterFly = m_timeCounterRotate = -1;
}

void Camera::Init(Vector3 position, Vector3 target, float nearPlane, float farPlane, float FOV, float aspectRatio)
{
	m_target = target;
	m_position = position;
	m_zaxis = (m_position-m_target).Normalize();
	m_xaxis = (m_up.Cross(m_zaxis)).Normalize();
	m_yaxis = (m_zaxis.Cross(m_xaxis)).Normalize();
	UpdateViewMatrix();
	m_PerspectiveMatrix.SetPerspective(FOV, aspectRatio, nearPlane, farPlane);
}

void Camera::SetSpeed(float move, float fly, float rotate)
{
	m_moveSpeed = move;
	m_flySpeed = fly;
	m_rotateSpeed = rotate;
}

void Camera::Update(float deltaTime)
{
	if (m_timeCounterMove > 0) {
		MoveRelative(m_moveDirection, m_smoothFunc(0,1,m_timeCounterMove / m_smoothTime));
		m_timeCounterMove -= deltaTime;
	}
	if (m_timeCounterFly > 0) {
		Fly(m_flyDirection, m_smoothFunc(0, 1, m_timeCounterFly / m_smoothTime));
		m_timeCounterFly -= deltaTime;
	}
	if (m_timeCounterRotate > 0) {
		Rotate(m_rotateDirection, m_smoothFunc(0, 1, m_timeCounterRotate / m_smoothTime));
		m_timeCounterRotate -= deltaTime;
	}
}

void Camera::MoveSmooth(Vector3 localDirection) {
	if (localDirection.Length() == 0) return;
	m_timeCounterMove = m_smoothTime;
	m_moveDirection = localDirection;
}
void Camera::RotateSmooth(Vector3 rotateDirection) {
	if (rotateDirection.Length() == 0) return;
	m_timeCounterRotate = m_smoothTime;
	m_rotateDirection = rotateDirection;
}
void Camera::FlySmooth(int flyDirection) {
	if (flyDirection == 0) return;
	m_timeCounterFly = m_smoothTime;
	m_flyDirection = flyDirection;
}


void Camera::OnDestroy()
{
}

void Camera::MoveRelative(Vector3 localDirection, float speedMultiplier)
{
	if (localDirection.Length() == 0) return;
	Vector3 deltaMove;
	deltaMove = (m_xaxis * localDirection.x) + (m_yaxis * localDirection.y) + (-m_zaxis * localDirection.z);
	deltaMove = deltaMove.Normalize() * m_moveSpeed * speedMultiplier;
	m_position += deltaMove;
	m_target += deltaMove;

	UpdateViewMatrix();
}

void Camera::Move(Vector3 worldDirection, float speedMultiplier)
{
	if (worldDirection.Length() == 0) return;
	Vector3 deltaMove = worldDirection.Normalize() * m_moveSpeed * speedMultiplier;
	m_position += deltaMove; 
	m_target += deltaMove;
	UpdateViewMatrix();
}

void Camera::Rotate(Vector3 direction, float speedMultiplier)
{
	if (direction.Length() == 0) return;
	direction = direction.Normalize() * m_rotateSpeed * speedMultiplier;

	Vector3 worldDeltaPosCameraTarget = m_target - m_position;
	float currAngle = acos(m_up.Dot(worldDeltaPosCameraTarget) / (worldDeltaPosCameraTarget.Length()));
	if ((currAngle + direction.x < 0 + m_rotateLimit) || (currAngle + direction.x > 3.1416 - m_rotateLimit)) {
		direction.x = 0;
	}

	Vector4 localTargetPosition(0, 0, (m_position - m_target).Length(), 1);
	Vector4 newLocalTargetPosition = localTargetPosition * Matrix().SetRotationZ(direction.z) * Matrix().SetRotationX(direction.x) * Matrix().SetRotationY(direction.y);

	m_target = m_position + (m_xaxis*newLocalTargetPosition.x + m_yaxis*newLocalTargetPosition.y - m_zaxis*newLocalTargetPosition.z);

	m_zaxis = (m_position - m_target).Normalize();
	m_xaxis = (m_up.Cross(m_zaxis)).Normalize();
	m_yaxis = (m_zaxis.Cross(m_xaxis)).Normalize();

	//printf("%f ; %f ; %f \n", m_target.x, m_target.y, m_target.z);
	UpdateViewMatrix();
}

void Camera::Fly(int direction, float speedMultiplier)
{
	Vector3 deltaMove = Vector3(0,1,0) * m_flySpeed * speedMultiplier * direction;
	m_position += deltaMove;
	m_target += deltaMove;
	UpdateViewMatrix();
}

Matrix & Camera::GetViewMatrix()
{
	return m_ViewMatrix;
}

Matrix & Camera::GetPerspectiveMatrix()
{
	return m_PerspectiveMatrix;
}
