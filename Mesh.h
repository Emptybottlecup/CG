
#pragma once
#include "GameComponent.h"

struct VertexPos;

class Mesh : public GameComponent
{
public:
	Mesh(Game* GameInstance, std::vector<VertexPos>& vertices, std::vector<DWORD>& indices);

	void Initialize();

	void Update(float deltaTime);

	void Draw();

	void DestroyResources();

	~Mesh();
private:
	ID3D11VertexShader* pVertexShader;
	ID3D11PixelShader* pPixelShader;

	ID3D11InputLayout* pInputLayout;
	ID3D11Buffer* pVertexBuffer;
	ID3D11Buffer* pIndexBuffer;

	DirectX::XMFLOAT3 pPosition;
	DirectX::XMFLOAT3 pRotation;
	DirectX::XMFLOAT3 pScale;
	DirectX::XMVECTOR pQuaternion;
	std::vector <VertexPos> pVertices;
	std::vector <DWORD> pIndices;

	ID3D11ShaderResourceView* pTextureRV;
	ID3D11SamplerState* pSamplerLinear;
	const wchar_t* pTextureFilename;
};