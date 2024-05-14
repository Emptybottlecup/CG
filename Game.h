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
#include "GameComponent.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

class GameComponent;

class Game
{
public:

	Game();

	Game(int Width, int Height);

	void CreateDeviceAndSwapChain();

	void CreateRenderTargetView();

	void CreateInputLayout();

	void PushGameComponents(GameComponent* newGameComponent);

	Microsoft::WRL::ComPtr<ID3D11Device> GetDevice();

	Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetDeviceContext();

	void Run();

private:
	int pWidth = 800;
	int pHeight = 800;
	std::vector<GameComponent*> pGameComponents;
	DisplayWin32 pWindow;
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pDeviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
};