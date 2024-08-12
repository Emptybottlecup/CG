#include "Camera.h"
#include <iostream>

Camera::Camera(DirectX::XMFLOAT3 startPosition, HWND* hWnd, InputDevice* inputdevice) : phWnd(hWnd), pInput(inputdevice)
{
	pPosition = startPosition;
	pFront = DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f);
	pUp = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);

	pPositionVector = DirectX::XMLoadFloat3(&pPosition);
	pFrontVector = DirectX::XMLoadFloat3(&pFront);
	pUpVector = DirectX::XMLoadFloat3(&pUp);

	yaw = 0.0f;
	pitch = 0.0f;

	localRotate = DirectX::XMQuaternionIdentity();
}

Camera::Camera(HWND* hWnd, InputDevice* inputdevice) : phWnd(hWnd), pInput(inputdevice)
{
	pPosition = DirectX::XMFLOAT3(0.0f, 0.0f, -5.0f);
	pFront = DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f);
	pUp = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);

	pPositionVector = DirectX::XMLoadFloat3(&pPosition);
	pFrontVector = DirectX::XMLoadFloat3(&pFront);
	pUpVector = DirectX::XMLoadFloat3(&pUp);

	yaw = 0.0f;
	pitch = 0.0f;

	localRotate = DirectX::XMQuaternionIdentity();
}

DirectX::XMMATRIX Camera::GetViewMatrix()
{
	return DirectX::XMMatrixLookToRH(pPositionVector, pFrontVector, pUpVector);
}

DirectX::XMMATRIX Camera::GetProjectionMatrix()
{
	return DirectX::XMMatrixPerspectiveFovRH(DirectX::XMConvertToRadians(74.0f), 1280.0f / 720.0f, 0.1f, 1000.0f);
}

void Camera::ProcessTransformPosition(float deltaTime)
{
	bool leftButton = false;

	if (pInput->IsKeyDown(Keys::LeftButton))
	{
		pFrontVector = DirectX::XMLoadFloat3(&pFront);
		pUpVector = DirectX::XMLoadFloat3(&pUp);

		float sensitivity = 0.05f;
		float deltaX = static_cast<float>(pInput->MousePosition.x - prevx) * sensitivity;
		float deltaY = static_cast<float>(pInput->MousePosition.y - prevy) * sensitivity;

		// Обновляем углы вращения, ограничивая pitch
		yaw -= deltaX;
		pitch -= deltaY;
		/*pitch = std::max(std::min(pitch, 89.0f), -89.0f); // Исправлено ограничение угла pitch */

		DirectX::XMVECTOR quatYaw = DirectX::XMQuaternionRotationAxis(DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), DirectX::XMConvertToRadians(yaw));

		// Создание кватерниона вращения вокруг оси X для pitch
		DirectX::XMVECTOR quatPitch = DirectX::XMQuaternionRotationAxis(DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), DirectX::XMConvertToRadians(pitch));

		localRotate = DirectX::XMQuaternionMultiply(quatPitch, quatYaw);

		pFrontVector = DirectX::XMVector3Rotate(pFrontVector, localRotate);

		pUpVector = DirectX::XMVector3Rotate(pUpVector, localRotate);

		leftButton = true;
	}

	DirectX::XMVECTOR right = DirectX::XMVector3Cross(pUpVector, pFrontVector);

	right = DirectX::XMVector3Normalize(right);
	// Обновление позиции камеры
	if (pInput->IsKeyDown(Keys::W)) {
	
		pPositionVector = DirectX::XMVectorAdd(pPositionVector, DirectX::XMVectorScale(pFrontVector, pCameraspeed * deltaTime));
	}
	if (pInput->IsKeyDown(Keys::S)) {
		pPositionVector = DirectX::XMVectorSubtract(pPositionVector, DirectX::XMVectorScale(pFrontVector, pCameraspeed * deltaTime));
	}
	if (pInput->IsKeyDown(Keys::A)) {
		pPositionVector = DirectX::XMVectorAdd(pPositionVector, DirectX::XMVectorScale(right, pCameraspeed * deltaTime)); // Исправлено направление для движения влево
	}
	if (pInput->IsKeyDown(Keys::D)) {
		pPositionVector = DirectX::XMVectorSubtract(pPositionVector, DirectX::XMVectorScale(right, pCameraspeed * deltaTime)); // Подтверждено правильное направление для движения вправо
	}
	if (pInput->IsKeyDown(Keys::Space)) {
		pPositionVector = DirectX::XMVectorAdd(pPositionVector, DirectX::XMVectorScale(pUpVector, pCameraspeed * deltaTime)); // Исправлено направление для движения вверх
	}
	if (pInput->IsKeyDown(Keys::X)) {
		pPositionVector = DirectX::XMVectorSubtract(pPositionVector, DirectX::XMVectorScale(pUpVector, pCameraspeed * deltaTime)); // Исправлено направление для движения вниз
	}

	prevx = pInput->MousePosition.x;
	prevy = pInput->MousePosition.y;
}