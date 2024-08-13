#pragma once
#include "DisplayWin32.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <wrl.h>
#include <stdio.h>
#include <vector>
#include "GameComponent.h"
#include <fstream>
#include <sstream>
#include "InputDevice.h"
#include "Camera.h"
#include <WICTextureLoader.h>


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "DirectXTK.lib")

class GameComponent;
class GameStick;
class Camera;

class Game
{
public:

	Game();

	void Initialize(HINSTANCE hInstance, HWND hwnd, InputDevice* InputDevice);

	void PushGameComponents(GameComponent* newGameComponent);

	void ChangeConstantBuffer(DirectX::XMMATRIX worldMatrix, DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX projMatrix);

	virtual void Run();
	ID3D11Device* GetDevice();

	ID3D11DeviceContext* GetDeviceContext();

	IDXGISwapChain* GetSwapChain();

	HWND& GetWindowHandle();

	Camera* GetCamera();

	void DeleteResources();

	~Game();

protected:
	HINSTANCE phInstance;
	HWND pWindow;
	InputDevice* pInputDevice;
	Camera* pCamera;

	ID3D11Device* pDevice;
	ID3D11DeviceContext* pDeviceContext;
	IDXGISwapChain* pSwapChain;

	ID3D11RenderTargetView* pBackBufferTarget;
	ID3D11Buffer* pConstantBuffer;
	ID3D11RasterizerState* pRasterizerState;

	std::vector<GameComponent*> pGameComponents;

	ID3D11Texture2D* pDepthTexture;
	ID3D11DepthStencilView* pDepthStencilView;
	ID3D11DepthStencilState* pDSState;
};