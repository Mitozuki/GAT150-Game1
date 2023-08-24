#include "Platformer.h"

#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Renderer/ParticleSystem.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Framework.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"
#include "Renderer/Texture.h"
#include "Physics/PhysicsSystem.h"

#include <iostream>
#include <vector>
#include <thread>
#include <array>
#include <map>
#include <functional>

using namespace std;



int main(int argc, char* argv[])
{
	INFO_LOG("Initialize Engine");

	kiko::MemoryTracker::Initialize();
	
	kiko::seed_random((unsigned int)time(nullptr));
	kiko::setFilePath("Assets");

	kiko::g_renderer.Initialize();
	kiko::g_renderer.CreateWindow("CSC195", 800, 600);

	kiko::g_audioSystem.Initialize();
	kiko::g_inputSystem.Initialize();
	kiko::PhysicsSystem::Instance().Initialize();


	kiko::vec2 v{5, 5};
	v.Normalize();

	kiko::g_renderer.SetColor(0, 0, 0, 0);
	kiko::g_renderer.BeginFrame();

	kiko::Transform transform{ { 400, 300 }, 0, 3 };

	kiko::vec2 position{ 400, 300 };
	float speed = 100;
	constexpr float turnRate = kiko::DegreesToRad(180);


	// create texture
	//kiko::res_t<kiko::Texture> texture = kiko::g_resources.Get<kiko::Texture>("Ship_1_B_Small.png", kiko::g_renderer);

	// main game loop
	kiko::g_audioSystem.PlayOneShot("background", true);
	bool quit = false;
	while (!quit)
	{

		kiko::g_time.Tick();
		kiko::g_inputSystem.Update();
		kiko::g_audioSystem.Update();
		//cout << kiko::g_inputSystem.GetMousePosition().x << " " << kiko::g_inputSystem.GetMousePosition().y << endl;
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}
		kiko::PhysicsSystem::Instance().Update(kiko::g_time.GetDeltaTime());

		//update
		//game->Update(kiko::g_time.GetDeltaTime());
		kiko::g_particleSystem.Update(kiko::g_time.GetDeltaTime());
		//draw


		//kiko::vec2 direction;
		//if (inputSystem.GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
		//if(inputSystem.GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
		//if(inputSystem.GetKeyDown(SDL_SCANCODE_S)) direction.y = 1;
		//if(inputSystem.GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;

		//position += direction * speed * kiko::g_time.GetDeltaTime();

		//draw
		kiko::Vector2 velocity(1.0f, 0.3f);
		kiko::g_renderer.SetColor(0, 0, 0, 255);
		kiko::g_renderer.BeginFrame(); // confirm with Maple this is how we do it

		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) || kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_B))
		{
			kiko::g_audioSystem.PlayOneShot("jump");
		}

		kiko::g_particleSystem.Draw(kiko::g_renderer);

		//kiko::g_renderer.DrawTexture(texture.get(), 200.0f, 200.0f, 0.0f);

		//game->Draw(kiko::g_renderer);

		kiko::g_renderer.EndFrame();

		//this_thread::sleep_for(chrono::milliseconds(100));
	}
	//scene.RemoveAll();
	//kiko::g_memoryTracker.DisplayInfo(); does not exist anymore

	return 0;
}
