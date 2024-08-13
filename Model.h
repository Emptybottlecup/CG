#pragma once
#include "Mesh.h"

class Model: public GameComponent
{
public:

	Model(Game* GameInstance, const std::string& filenamel, const wchar_t* textureFilename);

	Model(Game* GameInstance, const std::string& filenamel, const wchar_t* textureFilename, const DirectX::XMFLOAT3& position, const DirectX::XMFLOAT3& scale, const DirectX::XMFLOAT3& rotation);
	void Initialize();

	void Update(float deltaTime);

	void Draw();

	void DestroyResources();

	~Model();

private:

	bool LoadModel(const std::string& filename);

	void ProcessNode(aiNode* node, const aiScene* scene);

	Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);


	ID3D11VertexShader* pVertexShader;
	ID3D11PixelShader* pPixelShader;
	ID3D11InputLayout* pInputLayout;

	ID3D11ShaderResourceView* pTextureRV;
	ID3D11SamplerState* pSamplerLinear;
	const wchar_t* pTextureFilename;

	DirectX::XMFLOAT3 pPosition;
	DirectX::XMFLOAT3 pRotation;
	DirectX::XMFLOAT3 pScale;
	DirectX::XMVECTOR pQuaternion;

	std::vector<Mesh*> pMeshes;
	const std::string pFilename;
};