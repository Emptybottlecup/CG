#pragma once 
#include "Game.h"
#include "InputDevice.h"

class Camera
{
public:
	Camera(DirectX::XMFLOAT3 startPosition, HWND* hWnd, InputDevice* inputdevice);
	Camera(HWND* hwnd, InputDevice* input);
	~Camera() = default;

	DirectX::XMMATRIX GetViewMatrix();
	DirectX::XMMATRIX GetProjectionMatrix();

	void ProcessTransformPosition(float deltaTime);

private:
	float pCameraspeed = 2.0f;
	HWND* phWnd;
	InputDevice* pInput;

	DirectX::XMFLOAT3 pPosition;
	DirectX::XMFLOAT3 pFront;
	DirectX::XMFLOAT3 pUp;

	DirectX::XMVECTOR pPositionVector;
	DirectX::XMVECTOR pFrontVector;
	DirectX::XMVECTOR pUpVector;
	DirectX::XMVECTOR localRotate;

	float prevx;
	float prevy;
	float yaw = 0.0f;
	float pitch = 0.0f;

	float pWidth;
	float pHeight;
};