#include "Platformer.h"

#include "Framework/Framework.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/Model.h"
#include "Renderer/Emitter.h"

bool Platformer::Initialize()
{
	// load audio
	kiko::g_audioSystem.AddAudio("jump", "Jump.wav");

	m_scene = std::make_unique<kiko::Scene>();
	m_scene->Load("scene.json");
	m_scene->Initialize();

	// add events
	EVENT_SUBSCRIBE("AddPoints", Platformer::AddPoints);
	EVENT_SUBSCRIBE("OnPlayerDead", Platformer::OnPlayerDead);
	//kiko::EventManager::Instance().Subscribe("AddPoints", this, std::bind(&Platformer::AddPoints, this, std::placeholders::_1));
	//kiko::EventManager::Instance().Subscribe("OnPlayerDead", this, std::bind(&Platformer::OnPlayerDead, this, std::placeholders::_1));

	return true;
}

void Platformer::Shutdown()
{
}

void Platformer::Update(float dt)
{
	switch (m_state)
	{
	case Platformer::eState::Title:
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
			m_scene->GetActorByName("Background")->active = false;
		}
		break;
	case Platformer::eState::StartGame:
		m_score = 0;
		m_lives = 0;
		m_state = eState::StartLevel;
		break;
	case Platformer::eState::StartLevel:
		m_scene->RemoveAll();
		{
		}
		m_state = eState::Game;
		break;
	case Platformer::eState::Game:
		break;
	case Platformer::eState::PlayerDeadStart:
		m_stateTimer = 3;
		if (m_lives <= 0) m_state = eState::GameOver;
		else m_state = eState::PlayerDead;

		break;
	case Platformer::eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_state = eState::StartLevel;
		}
		break;
	case Platformer::eState::GameOver:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_scene->RemoveAll();
			m_state = eState::Title;
		}
		break;
	default:
		break;
	}

	m_scene->Update(dt);
}

void Platformer::Draw(kiko::Renderer& renderer)
{
	m_scene->Draw(renderer);
}

void Platformer::AddPoints(const kiko::Event& event)
{
	m_score += std::get<int>(event.data);

}

void Platformer::OnPlayerDead(const kiko::Event event)
{
	m_lives--;
	m_state = eState::PlayerDeadStart;
}