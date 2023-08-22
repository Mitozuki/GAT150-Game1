#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"

#include "Framework/Framework.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/Model.h"
#include "Renderer/Emitter.h"

bool SpaceGame::Initialize()
{
	// create font / text objects
	//m_font = std::make_shared<kiko::Font>("Vendetta.ttf", 24);
	//m_font = kiko::ResourceManager::Instance().Get<kiko::Font>("Vendetta.ttf", 24);
	m_font = GET_RESOURCE(kiko::Font, "Vendetta.ttf", 24);

	m_scoreText = std::make_unique<kiko::Text>(m_font);
	m_scoreText->Create(kiko::g_renderer, "SCORE", kiko::Color{ 1, 1, 1, 1 });

	m_titleText = std::make_unique<kiko::Text>(m_font);
	m_titleText->Create(kiko::g_renderer, "ASTEROIDS", kiko::Color{ 1, 1, 1, 1});

	m_gameoverText = std::make_unique<kiko::Text>(m_font);
	m_gameoverText->Create(kiko::g_renderer, "Game Over", kiko::Color{ 1, 1, 1, 1});


	// load audio
	kiko::g_audioSystem.AddAudio("jump", "Jump.wav");

	m_scene = std::make_unique<kiko::Scene>();
	m_scene->Load("scene.json");
	m_scene->Initialize();
	
	// add events
	EVENT_SUBSCRIBE("AddPoints", SpaceGame::AddPoints);
	EVENT_SUBSCRIBE("OnPlayerDead", SpaceGame::OnPlayerDead);
	//kiko::EventManager::Instance().Subscribe("AddPoints", this, std::bind(&SpaceGame::AddPoints, this, std::placeholders::_1));
	//kiko::EventManager::Instance().Subscribe("OnPlayerDead", this, std::bind(&SpaceGame::OnPlayerDead, this, std::placeholders::_1));

	return true;
}

void SpaceGame::Shutdown()
{
}

void SpaceGame::Update(float dt)
{
	switch (m_state)
	{
	case SpaceGame::eState::Title:
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
			m_scene->GetActorByName("Background")->active = false;
		}
		break;
	case SpaceGame::eState::StartGame:
		m_score = 0;
		m_lives = 0;
		m_state = eState::StartLevel;
		break;
	case SpaceGame::eState::StartLevel:
		m_scene->RemoveAll();
	{
		// Create Player
		std::unique_ptr<Player> player = std::make_unique<Player>(10.0f, kiko::pi, kiko::Transform{ { 400, 300 }, 0, 0.8f });
		player->tag = "Player";
		player->m_game = this;

		// Create Components
		auto component = CREATE_CLASS(SpriteComponent)
		component->m_texture = GET_RESOURCE(kiko::Texture, "Ship_1_B_Small.png", kiko::g_renderer);
		player->AddComponent(std::move(component));

		auto physicsComponent = CREATE_CLASS(EnginePhysicsComponent)
		physicsComponent->m_damping = 0.5f;
		player->AddComponent(std::move(physicsComponent));

		auto collisionComponent = CREATE_CLASS(CircleCollisionComponent)
		collisionComponent->m_radius = 30.0f;
		player->AddComponent(std::move(collisionComponent));

		player->Initialize();

		m_scene->Add(std::move(player));
	}
	m_state = eState::Game;
		break;
	case SpaceGame::eState::Game:
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime)
		{
			m_spawnTimer = 0;
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(kiko::randomf(75.0f, 150.0f), kiko::pi, kiko::Transform{ { kiko::random(800), kiko::random(600) }, kiko::randomf(kiko::twoPi), 0.8f});
			enemy->tag = "Enemy";
			enemy->m_game = this;
			//create components
			std::unique_ptr<kiko::SpriteComponent> component = std::make_unique<kiko::SpriteComponent>();
			component->m_texture = GET_RESOURCE(kiko::Texture, "Ship_2_D_Small.png", kiko::g_renderer);
			enemy->AddComponent(std::move(component));

			auto collisionComponent = std::make_unique<kiko::CircleCollisionComponent>();
			collisionComponent->m_radius = 30.0f;
			enemy->AddComponent(std::move(collisionComponent));

			enemy->Initialize();

			m_scene->Add(std::move(enemy));
			if (kiko::random(0, 9) == 0)
			{
				std::unique_ptr<Enemy> enemy2 = std::make_unique<Enemy>(kiko::randomf(5.0f, 15.0f), kiko::pi, kiko::Transform{ { kiko::random(800), kiko::random(600) }, 0.08f});
				enemy2->tag = "Enemy";
				enemy2->m_game = this;

				auto collisionComponent = std::make_unique<kiko::CircleCollisionComponent>();
				collisionComponent->m_radius = 30.0f;
				enemy->AddComponent(std::move(collisionComponent));

				enemy->Initialize();
				m_scene->Add(std::move(enemy2));
			}
		}
		break;
	case SpaceGame::eState::PlayerDeadStart:
		m_stateTimer = 3;
		if (m_lives <= 0) m_state = eState::GameOver;
		else m_state = eState::PlayerDead;

		break;
	case SpaceGame::eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_state = eState::StartLevel;
		}
		break;
	case SpaceGame::eState::GameOver:
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

	m_scoreText->Create(kiko::g_renderer, "SCORE " + std::to_string(m_score), {1, 1, 1, 1});
	m_scene->Update(dt);
}

void SpaceGame::Draw(kiko::Renderer& renderer)
{
	m_scene->Draw(renderer);
	if (m_state == eState::Title)
	{
		//m_titleText->Draw(renderer, 400, 300);
		m_scene->GetActorByName("Title")->active = true;
	}
	if (m_state == eState::GameOver)
	{
		m_gameoverText->Draw(renderer, 400, 300);
	}

	m_scoreText->Draw(renderer, 100, 100);
}

void SpaceGame::AddPoints(const kiko::Event& event)
{
	m_score += std::get<int>(event.data);

}

void SpaceGame::OnPlayerDead(const kiko::Event event)
{
	m_lives--;
	m_state = eState::PlayerDeadStart;
}
