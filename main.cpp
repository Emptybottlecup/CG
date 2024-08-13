#include "DisplayWin32.h"
#include "Model.h"


int main()
{
	DisplayWin32 display(1280, 720);
	Game* game = new Game();
	game->Initialize(display.GetHInstance(), display.GetWindow(), display.GetInputDevice());
	Model* Bigel = new Model(game, "13041_Beagle_v1_L1.obj", L"13041_Beagle_diffuse.jpg", DirectX::XMFLOAT3(-10.0f, 0.0f, 0.0f), DirectX::XMFLOAT3(0.25f, 0.25f, 0.25f), DirectX::XMFLOAT3(-80.0f, -90.0f, 0.0f));
	Model* Spritz = new Model(game, "Pomeranian-bl.obj", L"Pomeranian_texture.png", DirectX::XMFLOAT3(10.0f, 0.0f, 0.0f), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
	game->PushGameComponents(Spritz);
	game->PushGameComponents(Bigel);
	game->Run();
}


