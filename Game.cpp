#include "Game.h"

Game::Game()
{
	pWindow = DisplayWin32(pWidth, pHeight);
	CreateDeviceAndSwapChain();
	CreateRenderTargetView();
	pGameComponents.push_back(new TriangleGameComponent(this));
	CreateInputLayout();
}

Game::Game(int Width, int Height) : pWidth(Width), pHeight(Height)
{
	pWindow = DisplayWin32(pWidth, pHeight);
	CreateDeviceAndSwapChain();
	CreateRenderTargetView();
	pGameComponents.push_back(new TriangleGameComponent(this));
	CreateInputLayout();
}

void Game::CreateDeviceAndSwapChain()
{
	D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_11_1 };
	DXGI_SWAP_CHAIN_DESC swapDesc;
	swapDesc.BufferCount = 2;
	swapDesc.BufferDesc.Width = static_cast<float>(pWidth);
	swapDesc.BufferDesc.Height = static_cast<float>(pHeight);
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.RefreshRate.Numerator = 144;
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = *pWindow.GetWindow();
	swapDesc.Windowed = true;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapDesc.Flags = 0;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;

	auto res = D3D11CreateDeviceAndSwapChain(
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
	if (FAILED(res))
	{
		// Well, that was unexpected
	}
}

void Game::CreateRenderTargetView()
{
	ID3D11Texture2D* colorBuffer;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&colorBuffer);
	if (FAILED(pDevice->CreateRenderTargetView(colorBuffer, nullptr, &pRenderTargetView)))
	{
		printf("FAILD TO CREATE RTV!!!!\n");
		abort();
	}
	else
	{
		printf("CREATE RTV SUCCES\n");
	}
}

void Game::CreateInputLayout()
{
	D3D11_INPUT_ELEMENT_DESC inputElements[] = {
	D3D11_INPUT_ELEMENT_DESC {
		"POSITION",
		0,
		DXGI_FORMAT_R32G32B32_FLOAT,
		0,
		0,
		D3D11_INPUT_PER_VERTEX_DATA,
		0}
	};

	pDevice->CreateInputLayout(inputElements, 1, pGameComponents[0]->GetVertexShaderBlob()->GetBufferPointer(), pGameComponents[0]->GetVertexShaderBlob()->GetBufferSize(), &pInputLayout);
}

Microsoft::WRL::ComPtr<ID3D11Device> Game::GetDevice()
{
	return pDevice;
}

Microsoft::WRL::ComPtr<ID3D11DeviceContext> Game::GetDeviceContext()
{
	return pDeviceContext;
}

void Game::Run()
{
	MSG msg = {};
	bool isExitRequested = false;

	for (auto object : pGameComponents)
	{
		object->Initialize();
	}

	while (!isExitRequested) {
		// Handle the windows messages.
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If windows signals to end the application then exit out.
		if (msg.message == WM_QUIT) {
			isExitRequested = true;
		}

		float clearColor[] = { 0.5, 0.5, 1, 1 };
		pDeviceContext->ClearRenderTargetView(pRenderTargetView.Get(), clearColor);

		pDeviceContext->OMSetRenderTargets(1, pRenderTargetView.GetAddressOf(), nullptr);
		for (auto object : pGameComponents)
		{
			pDeviceContext->VSSetShader(object->GetVertexShader().Get(), nullptr, 0);
			pDeviceContext->PSSetShader(object->GetPixelShader().Get(), nullptr, 0);

		}
		pDeviceContext->IASetInputLayout(pInputLayout.Get());
		pDeviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		D3D11_VIEWPORT viewport = {};
		viewport.Width = static_cast<float>(pWidth);
		viewport.Height = static_cast<float>(pHeight);
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.MinDepth = 0;
		viewport.MaxDepth = 1.0f;

		pDeviceContext->RSSetViewports(1, &viewport);

		for (auto object : pGameComponents)
		{
			object->Draw();
		}

		pSwapChain->Present(1, 0);
	}
}
