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

	unique_ptr<Platformer> game = make_unique<Platformer>();
	game->Initialize();

	// main game loop
	kiko::g_audioSystem.PlayOneShot("background", true);
	bool quit = false;
	while (!quit)
	{

		kiko::g_time.Tick();
		kiko::g_inputSystem.Update();
		kiko::g_audioSystem.Update();
		kiko::g_particleSystem.Update(kiko::g_time.GetDeltaTime());
		kiko::PhysicsSystem::Instance().Update(kiko::g_time.GetDeltaTime());

		// escape
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		//update
		game->Update(kiko::g_time.GetDeltaTime());

		//draw
		kiko::g_renderer.SetColor(0, 0, 0, 255);
		kiko::g_renderer.BeginFrame();

		game->Draw(kiko::g_renderer);
		kiko::g_particleSystem.Draw(kiko::g_renderer);

		kiko::g_renderer.EndFrame();
	}

	return 0;
}
