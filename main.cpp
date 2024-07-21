#include "Game.h"
#include <iostream>

std::vector<int> GameStickIndices = { 0, 1, 2};
std::vector<DirectX::XMFLOAT4> GameStickPoints =
{
	DirectX::XMFLOAT4(-0.5f, 0.0f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
	DirectX::XMFLOAT4(0.0f, 0.5f, 0.5f,1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
	DirectX::XMFLOAT4(0.5f, 0.0f, 0.5f, 1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
};
int main()
{
	Game* game = new Game(800,800);
	TriangleGameComponent* triangle_1 = new TriangleGameComponent(game, GameStickPoints, GameStickIndices, DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	TriangleGameComponent* triangle_2 = new TriangleGameComponent(game, GameStickPoints, GameStickIndices, DirectX::XMFLOAT4(0.5f, -0.5f, 0.0f, 1.0f));
	TriangleGameComponent* triangle_3 = new TriangleGameComponent(game, GameStickPoints, GameStickIndices, DirectX::XMFLOAT4(-0.5f, -0.5f, 0.0f, 1.0f));
	game->PushGameComponents(triangle_1);
	game->PushGameComponents(triangle_2);
	game->PushGameComponents(triangle_3);
	game->Run();
	delete game; 
}