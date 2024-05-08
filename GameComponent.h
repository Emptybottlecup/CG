#pragma once

#include "Game.h"

class Game;

class GameComponent
{
public:
	virtual void Initialize() = 0;
	virtual void Draw() = 0;
	virtual void CreateShaders() = 0;

	virtual Microsoft::WRL::ComPtr<ID3D11VertexShader>& GetVertexShader() = 0;

	virtual Microsoft::WRL::ComPtr<ID3D11PixelShader>& GetPixelShader() = 0;

	virtual Microsoft::WRL::ComPtr<ID3DBlob>& GetVertexShaderBlob() = 0;

	virtual Microsoft::WRL::ComPtr<ID3DBlob>& GetPixelShaderBlob() = 0;
};

class TriangleGameComponent : public GameComponent
{
public:

	TriangleGameComponent(Game* GameObject);

	void Initialize();

	void CreateShaders();

	void Draw();

	Microsoft::WRL::ComPtr<ID3D11VertexShader>& GetVertexShader()
	{
		return pVertexShader;
	}

	Microsoft::WRL::ComPtr<ID3D11PixelShader>& GetPixelShader()
	{
		return pPixelShader;
	}

	Microsoft::WRL::ComPtr<ID3DBlob>& GetVertexShaderBlob()
	{
		return pVertexShaderBlob;
	}

	Microsoft::WRL::ComPtr<ID3DBlob>& GetPixelShaderBlob()
	{
		return pPixelShaderBlob;
	}

private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
	Microsoft::WRL::ComPtr<ID3DBlob> pVertexShaderBlob;
	Microsoft::WRL::ComPtr<ID3DBlob> pPixelShaderBlob;
	D3D11_BUFFER_DESC vertexBufDesc;
	D3D11_SUBRESOURCE_DATA vertexData;
	ID3D11Buffer* vb;
	D3D11_BUFFER_DESC indexBufDesc;
	D3D11_SUBRESOURCE_DATA indexData;
	ID3D11Buffer* ib;
	Game* pGame;
};