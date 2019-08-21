#include "game.h"
#include "..\\engine\scene.h"
#include "..\\engine\text_component.h"
#include <iostream>

bool Game::Startup()
{
	bool success = m_engine->Startup();

	m_score_event = m_engine->GetSystem<EntityEventDispatcher>()->Subscribe("score", std::bind(&Game::OnScore, this, std::placeholders::_1));

	m_state_machine = new StateMachine<Game>(this);

	{
		State state;
		state.Enter = std::bind(&Game::TitleState_Enter, this);
		state.Update = std::bind(&Game::TitleState_Update, this);
		state.Exit = std::bind(&Game::TitleState_Exit, this);
		m_state_machine->AddState("title", state);
	}
	{
		State state;
		state.Enter = std::bind(&Game::StartState_Enter, this);
		state.Update = std::bind(&Game::StartState_Update, this);
		m_state_machine->AddState("start", state);
	}

	m_state_machine->SetState("title");

	return success;
}

void Game::Shutdown()
{
	delete m_state_machine;

	m_engine->Shutdown();
	delete m_engine;
}

void Game::Update()
{
	m_engine->Update();
	m_quit = m_engine->Quit();

	m_state_machine->Update();
}

void Game::TitleState_Enter()
{
	m_engine->LoadScene("scenes/title.txt");
}

void Game::TitleState_Update()
{
	if (m_engine->GetSystem<InputSystem>()->GetKey(SDL_SCANCODE_SPACE)) {
		m_state_machine->SetState("start");
	}
}

void Game::TitleState_Exit()
{
	m_engine->DestroyScene();
}

void Game::StartState_Enter()
{
	m_engine->LoadScene("scenes/scene.txt");

	for (size_t i = 0; i < 10; i++) {
		Entity* entity = m_engine->GetScene()->GetObjectFactory()->Create<Entity>("asteroid");
		entity->m_transform.translation = vector2(g_random(800.0f), g_random(600.0f));

		m_engine->GetScene()->Add(entity);
	}
}

void Game::StartState_Update()
{
}

bool Game::OnScore(const Event<Entity>& event)
{
	m_score += event.data[0].as_int;
	Entity* entity = m_engine->GetScene()->GetEntityWithName("total_score");
	std::string score = std::to_string(m_score);
	entity->GetComponent<TextComponent>()->SetText(score.c_str());

	return true;
}
