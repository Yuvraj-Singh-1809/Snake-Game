#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Event.hpp>

#include "MainMenu.hpp"
#include "Game.hpp"

Game::Game() : m_context(std::make_shared<Context>())
{
	m_context->m_window->create(sf::VideoMode({ 640, 384 }), "Snake Game",sf::Style::Close);
	m_context->m_state->Add(std::make_unique<MainMenu>(m_context), true);
}

Game::~Game()
{
}

void Game::Run()
{
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

	/*sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;*/

    while (m_context->m_window->isOpen())
    {
		/*timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TIME_PER_FRAME)
        {  
			timeSinceLastUpdate -= TIME_PER_FRAME;*/

			m_context->m_state->ProcessStateChanges();
			m_context->m_state->GetCurrent()->ProcessInput();
			m_context->m_state->GetCurrent()->Update(TIME_PER_FRAME);
			m_context->m_state->GetCurrent()->Draw(); 
        //}
    }
}