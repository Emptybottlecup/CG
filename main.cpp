#include "DisplayWin32.h"
#include "Pong.h"
#include "Cube.h"
#include "Sphere.h"

int main()
{
	DisplayWin32 display(1280,720);
	Game* game = new Game();
	game->Initialize(display.GetHInstance(), display.GetWindow(), display.GetInputDevice());

	Sphere* TheSun = new Sphere(game, 6, 50, 50, nullptr, {0, 0, 0}, 0);
	Sphere* Mercure = new Sphere(game, 2, 50, 50, TheSun, {-15, 0, 0}, 15);
	Sphere* Venus = new Sphere(game, 3, 50, 50, TheSun, { -22, 0, 0 }, 12);
	Sphere* Earth = new Sphere(game, 3, 50, 50, TheSun, { -29, 0, 0 }, 10);
	Sphere* Mars = new Sphere(game, 2, 50, 50, TheSun, { -36, 0, 0 }, 8);
	Sphere* Jupiter = new Sphere(game, 4, 50, 50, TheSun, { -50, 0, 0 }, 6);
	Sphere* Saturn = new Sphere(game, 4, 50, 50, TheSun, { -70,0,0 }, 4);
	Sphere* Uranus = new Sphere(game, 2, 50, 50, TheSun, { -75,0,0 }, 2);
	Sphere* Neptune = new Sphere(game, 2, 50, 50, TheSun, { -80,0,0 }, 1);

	Sphere* Moon = new Sphere(game, 1, 50, 50, Earth, { -33,0,0 }, 20);
	Sphere* Fobos = new Sphere(game, 1, 50, 50, Mars, { -40,0,0 }, 20);
	Sphere* Deymos = new Sphere(game, 1, 50, 50, Mars, { -43,0,0 }, 15);


	Cube* MotherCube = new Cube(game, nullptr, {0,20,0}, {5,5,5}, {0,0,0}, 0);
	Cube* ChildCube = new Cube(game, MotherCube, {-10,20,0}, {1,1,1}, {0,0,0}, 15);


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

	game->PushGameComponents(MotherCube);
	game->PushGameComponents(ChildCube);
	game->Run();
}


