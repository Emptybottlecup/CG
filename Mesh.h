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

	ID3D11Buffer* pVertexBuffer;
	ID3D11Buffer* pIndexBuffer;

	std::vector <VertexPos> pVertices;
	std::vector <DWORD> pIndices;
};