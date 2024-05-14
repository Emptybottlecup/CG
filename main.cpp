#include "Game.h"



int main()
{
	std::vector<int> indices_1 = { 0,1,2 };
	std::vector<DirectX::XMFLOAT3> points_1 = { {-0.3, 0.0, 1.0},{0, 0.3, 1.0},{0.3, 0.0, 1.0} };
	std::vector<int> indices_2 = { 0,1,2 };
	std::vector<DirectX::XMFLOAT3> points_2 = { {-0.3, 0.3, 1.0},{0, 0.6, 1.0},{0.3, 0.3, 1.0} };
	std::vector<int> indices_3 = { 0,1,2 };
	std::vector<DirectX::XMFLOAT3> points_3 = { {-0.3, -0.3, 1.0},{0.0, 0.0, 1.0},{0.3, -0.3, 1.0} };
	std::vector<int> indices_4 = { 0,1,2 };
	std::vector<DirectX::XMFLOAT3> points_4 = { {-1.0, 1.0, 1.0},{-0.3, 0.0, 1.0},{-1.0, -1.0, 1.0} };
	std::vector<int> indices_5 = { 0,2,1 };
	std::vector<DirectX::XMFLOAT3> points_5 = { {1.0, 1.0, 1.0},{0.3, 0.0, 1.0},{1.0, -1.0, 1.0} };
	Game game;
	TriangleGameComponent* Triangle_1 = new TriangleGameComponent(&game, points_1, indices_1);
	TriangleGameComponent* Triangle_2 = new TriangleGameComponent(&game, points_2, indices_2);
	TriangleGameComponent* Triangle_3 = new TriangleGameComponent(&game, points_3, indices_3);
	TriangleGameComponent* Triangle_4 = new TriangleGameComponent(&game, points_4, indices_4);
	TriangleGameComponent* Triangle_5 = new TriangleGameComponent(&game, points_5, indices_5);
	game.PushGameComponents(Triangle_1);
	game.PushGameComponents(Triangle_2);
	game.PushGameComponents(Triangle_3);
	game.PushGameComponents(Triangle_4);
	game.PushGameComponents(Triangle_5);
	game.Run();
}