#include "DisplayWin32.h"
#include "Pong.h"
#include "Cube.h"
#include "Sphere.h"

int main()
{
	DisplayWin32 display(1280, 720);
	Game* game = new Game();
	game->Initialize(display.GetHInstance(), display.GetWindow(), display.GetInputDevice());

	Sphere* TheSun = new Sphere(game, 6, 50, 50, nullptr, { 0, 0, 0 }, 0, L"Sun.jpg");
	Sphere* Mercure = new Sphere(game, 2, 50, 50, TheSun, { -15, 0, 0 }, 15, L"Mercure.jpg");
	Sphere* Venus = new Sphere(game, 3, 50, 50, TheSun, { -22, 0, 0 }, 12, L"Venus.jpg");
	Sphere* Earth = new Sphere(game, 3, 50, 50, TheSun, { -29, 0, 0 }, 10, L"Earth.jpg");
	Sphere* Mars = new Sphere(game, 2, 50, 50, TheSun, { -36, 0, 0 }, 8, L"Mars.jpg");
	Sphere* Jupiter = new Sphere(game, 4, 50, 50, TheSun, { -50, 0, 0 }, 6, L"Jupiter.jpg");
	Sphere* Saturn = new Sphere(game, 4, 50, 50, TheSun, { -70,0,0 }, 4, L"Saturn.jpg");
	Sphere* Uranus = new Sphere(game, 2, 50, 50, TheSun, { -75,0,0 }, 2, L"Uranus.jpg");
	Sphere* Neptune = new Sphere(game, 2, 50, 50, TheSun, { -80,0,0 }, 1, L"Neptune.jpg");
	Sphere* Pluto = new Sphere(game, 1, 50, 50, TheSun, { -90,0,0 }, 1, L"Pluto.jpg");

	Sphere* Moon = new Sphere(game, 1, 50, 50, Earth, { -33,0,0 }, 20, L"TheMoon.jpg");
	Sphere* Fobos = new Sphere(game, 1, 50, 50, Mars, { -40,0,0 }, 20, L"TheMoon.jpg");
	Sphere* Deymos = new Sphere(game, 1, 50, 50, Mars, { -43,0,0 }, 15, L"TheMoon.jpg");

	game->PushGameComponents(TheSun);
	game->PushGameComponents(Mercure);
	game->PushGameComponents(Venus);
	game->PushGameComponents(Earth);
	game->PushGameComponents(Mars);
	game->PushGameComponents(Jupiter);
	game->PushGameComponents(Saturn);
	game->PushGameComponents(Uranus);
	game->PushGameComponents(Neptune);
	game->PushGameComponents(Moon);
	game->PushGameComponents(Fobos);
	game->PushGameComponents(Deymos);
	game->PushGameComponents(Pluto);
	game->Run();
}


