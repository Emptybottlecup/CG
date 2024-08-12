#include "DisplayWin32.h"
#include "Pong.h"
#include "Cube.h"
#include "Sphere.h"

int main()
{
	DisplayWin32 display(1280, 720);
	Game* game = new Game();
	game->Initialize(display.GetHInstance(), display.GetWindow(), display.GetInputDevice());
	game->LoadModel("Engine.obj");
	game->Run();
}


