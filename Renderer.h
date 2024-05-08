#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <wrl.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

class Renderer
{
public:
	Renderer(HWND* pWindow, int ScreenWidth, int ScreenHeight);
	~Renderer() = default;

	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void CreateShaders();
	void CreateInputLayout();

	void SetPipeline();



	Microsoft::WRL::ComPtr<ID3D11Device> GetDevice()
	{
		return mDevice;
	}
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetDeviceContext()
	{
		return mDeviceContext;
	}
	Microsoft::WRL::ComPtr<ID3D11InputLayout> GetInputLayout()
	{
		return mInputLayout;
	}
	Microsoft::WRL::ComPtr<ID3D11VertexShader> GetShaderVertex()
	{
		return mVertexShader;
	}
	Microsoft::WRL::ComPtr<ID3D11PixelShader> GetShaderPixel()
	{
		return mPixelShader;
	}
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetRenderTarget()
	{
		return mRenderTargetView;
	}
	void Draw(uint32_t indexCount);
	void ClearColor(DirectX::XMFLOAT4 color);
	void Present();
	HWND* mWindow;
	int width;
	int height;
	Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> mDeviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;

	Microsoft::WRL::ComPtr<ID3D11VertexShader> mVertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> mPixelShader;
	Microsoft::WRL::ComPtr<ID3DBlob> mVertexShaderBlob;
	Microsoft::WRL::ComPtr<ID3DBlob> mPixelShaderBlob;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> mInputLayout;
};