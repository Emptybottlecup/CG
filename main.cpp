#include "Game.h"

int main()
{
	Game* game = new Game();
	std::vector<int> indices_1 = { 0, 1, 2};
	std::vector<DirectX::XMFLOAT4> points_1 = { {-0.3, 0.0, 1.0,1.0},{0.0, 0.3, 1.0,1.0},{0.3, 0.0, 1.0, 1.0}};
	TriangleGameComponent* Triangle_1 = new TriangleGameComponent(game, points_1, indices_1);
	game->PushGameComponents(Triangle_1);
	game->Run();
	delete game;
}