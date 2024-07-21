#pragma once
#include "Keys.h"
#include "Game.h"

class Game;

class GameComponent
{
public:
	virtual void Initialize() = 0;
	virtual void Draw() = 0;
	virtual void CreateShadersAndInputLayout() = 0;
	virtual void DestroyResources() = 0;
	virtual void Update() = 0;
	virtual Microsoft::WRL::ComPtr<ID3D11VertexShader>& GetVertexShader() = 0;

	virtual Microsoft::WRL::ComPtr<ID3D11PixelShader>& GetPixelShader() = 0;

	virtual Microsoft::WRL::ComPtr<ID3DBlob>& GetVertexShaderByteCode() = 0;

	virtual Microsoft::WRL::ComPtr<ID3DBlob>& GetPixelShaderByteCode() = 0;
};



class TriangleGameComponent : public GameComponent
{
public:

	TriangleGameComponent(Game* GameObject, std::vector<DirectX::XMFLOAT4> points, std::vector<int> indices, DirectX::XMFLOAT4 offset);

	void Initialize();

	void CreateShadersAndInputLayout();

	void Draw();

	void Update();

	void DestroyResources();

	~TriangleGameComponent();

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

	Game* GetGame()
	{
		return pGame;
	}
protected:
	std::vector<DirectX::XMFLOAT4> pPoints;
	std::vector<int> pIndices;
	DirectX::XMFLOAT4 pPosition = { 0.0f, 0.0f, 0.0f, 0.0f };
	ID3D11Buffer* VertexBuffer;
	ID3D11Buffer* IndexBuffer;
	Game* pGame;
private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
	Microsoft::WRL::ComPtr<ID3DBlob> pVertexShaderByteCode;
	Microsoft::WRL::ComPtr<ID3DBlob> pPixelShaderByteCode;
	ID3D11InputLayout* pInputLayout;
};