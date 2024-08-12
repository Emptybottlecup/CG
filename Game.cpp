#include "Game.h"
#include <iostream>
#include <chrono>
#include "GameStick.h"
#include "Mesh.h"

struct ConstantBuffer
{
	DirectX::XMMATRIX worldMatrix;
	DirectX::XMMATRIX viewMatrix;
	DirectX::XMMATRIX projMatrix;
};

struct VertexPos
{
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT2 TexCoord;
};

Game::Game()
{

}

ID3D11Device* Game::GetDevice()
{
	return pDevice;
}

ID3D11DeviceContext* Game::GetDeviceContext()
{
	return pDeviceContext;
}

IDXGISwapChain* Game::GetSwapChain()
{
	return pSwapChain;
}

HWND& Game::GetWindowHandle()
{
	return pWindow;
}

Camera* Game::GetCamera()
{
	return pCamera;
}

void Game::Initialize(HINSTANCE hInstance, HWND hwnd, InputDevice* InputDevice)
{
	phInstance = hInstance;
	pWindow = hwnd;
	pInputDevice = InputDevice;
	pCamera = new Camera(&hwnd, InputDevice);

	RECT dimensions;
	GetClientRect(hwnd, &dimensions);
	unsigned int width = dimensions.right - dimensions.left;
	unsigned int height = dimensions.bottom - dimensions.top;

	D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_11_1 };
	unsigned int totalFeatureLevels = ARRAYSIZE(featureLevel);
	DXGI_SWAP_CHAIN_DESC swapDesc;
	ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapDesc.BufferCount = 2;
	swapDesc.BufferDesc.Width = width;
	swapDesc.BufferDesc.Height = height;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.RefreshRate.Numerator = 144;
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = pWindow;
	swapDesc.Windowed = true;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapDesc.Flags = 0;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;


	HRESULT result;

	result = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		featureLevel,
		1,
		D3D11_SDK_VERSION,
		&swapDesc,
		&pSwapChain,
		&pDevice,
		nullptr,
		&pDeviceContext);
	if (FAILED(result))
	{
		OutputDebugString(L"Failed to create D3D11 Device!\n");
		return;
	}

	ID3D11Texture2D* backBufferTexture;
	result = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);
	if (FAILED(result))
	{
		OutputDebugString(L"Failed to get back buffer texture!\n");
		return;
	}
	result = pDevice->CreateRenderTargetView(backBufferTexture, 0, &pBackBufferTarget);
	if (backBufferTexture) backBufferTexture->Release();
	pDeviceContext->OMSetRenderTargets(1, &pBackBufferTarget, 0);

	D3D11_DEPTH_STENCIL_DESC dsDesc;
	ZeroMemory(&dsDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	result = pDevice->CreateDepthStencilState(&dsDesc, &pDSState);
	if (FAILED(result))
	{
		OutputDebugString(L"Failed to create depth state!\n");
		return;
	}
	pDeviceContext->OMSetDepthStencilState(pDSState, 1);


	D3D11_TEXTURE2D_DESC depthTexDesc;
	ZeroMemory(&depthTexDesc, sizeof(depthTexDesc));
	depthTexDesc.Width = width;
	depthTexDesc.Height = height;
	depthTexDesc.MipLevels = 1;
	depthTexDesc.ArraySize = 1;
	depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthTexDesc.SampleDesc.Count = 1;
	depthTexDesc.SampleDesc.Quality = 0;
	depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
	depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthTexDesc.CPUAccessFlags = 0;
	depthTexDesc.MiscFlags = 0;
	result = pDevice->CreateTexture2D(&depthTexDesc, 0, &pDepthTexture);
	if (FAILED(result))
	{
		OutputDebugString(L"Failed to create depth texture!\n");
		return;
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = depthTexDesc.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	result = pDevice->CreateDepthStencilView(pDepthTexture, &descDSV, &pDepthStencilView);
	if (FAILED(result))
	{
		OutputDebugString(L"Failed to create depth stencil view!\n");
		return;
	}
	pDeviceContext->OMSetRenderTargets(1, &pBackBufferTarget, pDepthStencilView);

	D3D11_VIEWPORT viewport; viewport.Width = static_cast<float>(width);
	viewport.Height = static_cast<float>(height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	pDeviceContext->RSSetViewports(1, &viewport);

	ConstantBuffer constantBufferPoints = { DirectX::XMMatrixIdentity(),DirectX::XMMatrixIdentity() , DirectX::XMMatrixIdentity() };
	D3D11_BUFFER_DESC constantBufDesc;
	constantBufDesc.Usage = D3D11_USAGE_DYNAMIC;
	constantBufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constantBufDesc.MiscFlags = 0;
	constantBufDesc.StructureByteStride = 0;
	constantBufDesc.ByteWidth = sizeof(ConstantBuffer);
	D3D11_SUBRESOURCE_DATA constantData;
	constantData.pSysMem = &constantBufferPoints;
	constantData.SysMemPitch = 0;
	constantData.SysMemSlicePitch = 0;
	result = pDevice->CreateBuffer(&constantBufDesc, &constantData, &pConstantBuffer);
	if (FAILED(result))
	{
		OutputDebugString(L"Failed to create constant buffer!\n");
		return;
	}
	pDeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);

	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	rasterizerDesc.FrontCounterClockwise = false;
	rasterizerDesc.DepthClipEnable = true;
	result = pDevice->CreateRasterizerState(&rasterizerDesc, &pRasterizerState);
	if (FAILED(result))
	{
		OutputDebugString(L"Failed to create rasterizer state!\n");
		return;
	}
	pDeviceContext->RSSetState(pRasterizerState); 
}

void Game::PushGameComponents(GameComponent* newGameComponent)
{
	pGameComponents.push_back(newGameComponent);
}

void Game::ChangeConstantBuffer(DirectX::XMMATRIX worldMatrix, DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX projMatrix)
{
	ConstantBuffer constBuf = { worldMatrix, viewMatrix, projMatrix };

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	pDeviceContext->Map(pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	memcpy(mappedResource.pData, &constBuf, sizeof(ConstantBuffer));
	pDeviceContext->Unmap(pConstantBuffer, 0);
}

void Game::Run()
{
	MSG msg = {};

	bool isExitRequested = false;

	std::chrono::time_point<std::chrono::steady_clock> PrevTime = std::chrono::steady_clock::now();

	for (auto object : pGameComponents)
	{
		object->Initialize();
	}

	while (!isExitRequested) {

		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT) {
			isExitRequested = true;
		}

		float clearColor[] = { 0.0, 0.0, 0.0, 1 };
		pDeviceContext->ClearDepthStencilView(pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
		pDeviceContext->ClearRenderTargetView(pBackBufferTarget, clearColor);

		auto curTime = std::chrono::steady_clock::now();
		float deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(curTime - PrevTime).count() / 100000.0f;
		PrevTime = curTime;

		pDeviceContext->OMSetRenderTargets(1, &pBackBufferTarget, pDepthStencilView);

		pCamera->ProcessTransformPosition(deltaTime);

		for (auto object : pGameComponents)
		{
			object->Update(deltaTime);
			object->Draw();
		}

		pSwapChain->Present(1, 0);
	}
}


void Game::DeleteResources()
{
	if (pRasterizerState) pRasterizerState->Release();
	if (pDepthTexture) pDepthTexture->Release();
	if (pDepthStencilView) pDepthStencilView->Release();
	if (pBackBufferTarget) pBackBufferTarget->Release();
	if (pConstantBuffer) pConstantBuffer->Release();
	if (pSwapChain) pSwapChain->Release();
	if (pDeviceContext) pDeviceContext->Release();
	if (pDevice) pDevice->Release();

	pRasterizerState = 0;
	pDepthTexture = 0;
	pDepthStencilView = 0;
	pDeviceContext = 0;
	pDevice = 0;
	pSwapChain = 0;
	pBackBufferTarget = 0;
	pConstantBuffer = 0;
}

Game::~Game()
{
	DeleteResources();
}


bool Game::LoadModel(const std::string& filename)
{
	Assimp::Importer importer;

	const aiScene* pScene = importer.ReadFile(filename, aiProcess_Triangulate);

	if (pScene == NULL)
	{
		return false;
	}

	ProcessNode(pScene->mRootNode, pScene);

	return true;
}

void Game::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		pGameComponents.push_back(ProcessMesh(mesh, scene));
	}

	for (int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

GameComponent* Game::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<VertexPos> vertices;
	std::vector<DWORD> indices;

	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		VertexPos vertex;

		vertex.Pos.x = mesh->mVertices[i].x;
		vertex.Pos.y = mesh->mVertices[i].y;
		vertex.Pos.z = mesh->mVertices[i].z;

		if (mesh->mTextureCoords[0])
		{
			vertex.TexCoord.x = mesh->mTextureCoords[0][i].x;
			vertex.TexCoord.y = mesh->mTextureCoords[0][i].y;
		}

		vertices.push_back(vertex);
	}

	for (int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	return new Mesh(this, vertices, indices);
}
