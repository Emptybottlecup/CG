#include "DisplayWin32.h"
#include "Model.h"
#include "random"
#include "CharacterBall.h"

float getRandomCoordinate(float min, float max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}

bool checkOverlap(DirectX::XMFLOAT3 pos1, DirectX::XMFLOAT3 pos2) {
    float distance = sqrt(pow(pos2.x - pos1.x, 2) + pow(pos2.y - pos1.y, 2) + pow(pos2.z - pos1.z, 2));
    return distance < 10.0f;
}

int main()
{
	DisplayWin32 display(1280, 720);
	Game* game = new Game();

    for (int i = 0; i < 5; ++i) {
        DirectX::XMFLOAT3 BigelPos(getRandomCoordinate(-50.0f, 50.0f), 0, getRandomCoordinate(-50.0f, 50.0f));
        DirectX::XMFLOAT3 SpritzPos(getRandomCoordinate(-50.0f, 50.0f), 0, getRandomCoordinate(-50.0f, 50.0f));

        while (checkOverlap(BigelPos, SpritzPos)) {
            SpritzPos.x += getRandomCoordinate(-5.0f, 5.0f);
            SpritzPos.z += getRandomCoordinate(-5.0f, 5.0f);
        }

        Model* Bigel = new Model(game, "Models/Beagle/13041_Beagle_v1_L1.obj", BigelPos, DirectX::XMFLOAT3(0.1f, 0.1f, 0.1f), DirectX::XMFLOAT3(-80.0f, -90.0f, 0.0f));
        Model* Spritz = new Model(game, "Models/Spritz/Pomeranian-bl.obj", SpritzPos, DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));

        game->PushGameComponents(Bigel);
        game->PushGameComponents(Spritz);
        game->PushCollisions(Bigel);
        game->PushCollisions(Spritz);
    }
    Model* Road = new Model(game, "Models/Road/detailed_road_03_obj.obj",DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f), DirectX::XMFLOAT3(0.05f, 0.05f, 0.05f), DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
	game->PushGameComponents(Road);

	game->Initialize(display.GetHInstance(), display.GetWindow(), display.GetInputDevice(), new CharacterBall(game, 2, 100, 100, L"Pluto.jpg", DirectX::XMFLOAT3(0, 2, 0), DirectX::XMFLOAT3(1, 1, 1), DirectX::XMFLOAT3(0, 0, 0)));
	game->Run();
}


