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

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	prevx = screenWidth / 2;
	prevy = screenHeight / 2;

}

Camera::Camera(HWND* hWnd, InputDevice* inputdevice) : phWnd(hWnd), pInput(inputdevice)
{
	pPosition = DirectX::XMFLOAT3(0.0f, 0.0f, -100.0f);
	pFront = DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f);
	pUp = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);

	pPositionVector = DirectX::XMLoadFloat3(&pPosition);
	pFrontVector = DirectX::XMLoadFloat3(&pFront);
	pUpVector = DirectX::XMLoadFloat3(&pUp);

	yaw = 0.0f;
	pitch = 0.0f;

	localRotate = DirectX::XMQuaternionIdentity();

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	prevx = screenWidth / 2;
	prevy = screenHeight / 2;
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
	ShowCursor(false);


	pFrontVector = DirectX::XMLoadFloat3(&pFront);
	pUpVector = DirectX::XMLoadFloat3(&pUp);

	float sensitivity = 0.1f;

	POINT cursorPos;
	GetCursorPos(&cursorPos);

	float deltaX = static_cast<float>(cursorPos.x - prevx) * sensitivity;
	float deltaY = static_cast<float>(cursorPos.y - prevy) * sensitivity;

	yaw -= deltaX;
	pitch -= deltaY;

	DirectX::XMVECTOR quatYaw = DirectX::XMQuaternionRotationAxis(DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), DirectX::XMConvertToRadians(yaw));

	DirectX::XMVECTOR quatPitch = DirectX::XMQuaternionRotationAxis(DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), DirectX::XMConvertToRadians(pitch));

	localRotate = DirectX::XMQuaternionMultiply(quatPitch, quatYaw);

	pFrontVector = DirectX::XMVector3Rotate(pFrontVector, localRotate);

	pUpVector = DirectX::XMVector3Rotate(pUpVector, localRotate);

	DirectX::XMVECTOR right = DirectX::XMVector3Cross(pUpVector, pFrontVector);

	right = DirectX::XMVector3Normalize(right);

	if (pInput->IsKeyDown(Keys::W)) {
	
		pPositionVector = DirectX::XMVectorAdd(pPositionVector, DirectX::XMVectorScale(pFrontVector, pCameraspeed * deltaTime));
	}
	if (pInput->IsKeyDown(Keys::S)) {
		pPositionVector = DirectX::XMVectorSubtract(pPositionVector, DirectX::XMVectorScale(pFrontVector, pCameraspeed * deltaTime));
	}
	if (pInput->IsKeyDown(Keys::A)) {
		pPositionVector = DirectX::XMVectorAdd(pPositionVector, DirectX::XMVectorScale(right, pCameraspeed * deltaTime)); // »справлено направление дл€ движени€ влево
	}
	if (pInput->IsKeyDown(Keys::D)) {
		pPositionVector = DirectX::XMVectorSubtract(pPositionVector, DirectX::XMVectorScale(right, pCameraspeed * deltaTime)); // ѕодтверждено правильное направление дл€ движени€ вправо
	}
	if (pInput->IsKeyDown(Keys::Space)) {
		pPositionVector = DirectX::XMVectorAdd(pPositionVector, DirectX::XMVectorScale(pUpVector, pCameraspeed * deltaTime)); // »справлено направление дл€ движени€ вверх
	}
	if (pInput->IsKeyDown(Keys::X)) {
		pPositionVector = DirectX::XMVectorSubtract(pPositionVector, DirectX::XMVectorScale(pUpVector, pCameraspeed * deltaTime)); // »справлено направление дл€ движени€ вниз
	}


	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	prevx = screenWidth / 2;
	prevy = screenHeight / 2;

	SetCursorPos(screenWidth / 2, screenHeight / 2);
}