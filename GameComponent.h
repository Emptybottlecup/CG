#pragma once

#include "Game.h"

class Game;

class GameComponent
{
public:
	virtual void Initialize() = 0;
	virtual void Draw() = 0;
	virtual void CreateShaders() = 0;
	virtual void DestroyResources() = 0;
	virtual void Reload() = 0;
	virtual void Update() = 0;

	virtual Microsoft::WRL::ComPtr<ID3D11VertexShader>& GetVertexShader() = 0;

	virtual Microsoft::WRL::ComPtr<ID3D11PixelShader>& GetPixelShader() = 0;

	virtual Microsoft::WRL::ComPtr<ID3DBlob>& GetVertexShaderByteCode() = 0;

	virtual Microsoft::WRL::ComPtr<ID3DBlob>& GetPixelShaderByteCode() = 0;
};

class TriangleGameComponent : public GameComponent
{
public:

	TriangleGameComponent(Game* GameObject, std::vector<DirectX::XMFLOAT3> points, std::vector<int> indices);

	void Initialize();

	void CreateShaders();

	void Draw();

	void Reload();

	void Update();

	void DestroyResources();

	Microsoft::WRL::ComPtr<ID3D11VertexShader>& GetVertexShader()
	{
		return pVertexShader;
	}

	Microsoft::WRL::ComPtr<ID3D11PixelShader>& GetPixelShader()
	{
		return pPixelShader;
	}

	Microsoft::WRL::ComPtr<ID3DBlob>& GetVertexShaderByteCode()
	{
		return pVertexShaderByteCode;
	}

	Microsoft::WRL::ComPtr<ID3DBlob>& GetPixelShaderByteCode()
	{
		return pPixelShaderByteCode;
	}

private:
	std::vector<DirectX::XMFLOAT3> pPoints;
	std::vector<int> pIndices;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
	Microsoft::WRL::ComPtr<ID3DBlob> pVertexShaderByteCode;
	Microsoft::WRL::ComPtr<ID3DBlob> pPixelShaderByteCode;
	Game* pGame;
};

