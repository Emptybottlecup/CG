#include "Game.h"

int main()
{
	Game* game = new Game();
	std::vector<int> indices_1 = { 0, 1, 2,2,1,3};
	std::vector<DirectX::XMFLOAT4> points_1 = 
	{ 
		DirectX::XMFLOAT4(-0.05f, 0.3f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
		DirectX::XMFLOAT4(0.05f, 0.3f, 0.5f,1.0f),	DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f),
		DirectX::XMFLOAT4(-0.05f, -0.3f, 0.5f, 1.0f),	DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f),
		DirectX::XMFLOAT4(0.05f, -0.3f, 0.5f, 1.0f),	DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)
	};
	TriangleGameComponent* Triangle_1 = new TriangleGameComponent(game, points_1, indices_1);
	game->PushGameComponents(Triangle_1);
	game->Run();
	delete game;
}