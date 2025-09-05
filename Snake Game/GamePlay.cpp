#include "GamePlay.hpp"
#include "GameOver.hpp"
#include "PauseGame.hpp"

#include <SFML/Window/Event.hpp>

#include<stdlib.h>
#include<time.h>


GamePlay::GamePlay(std::shared_ptr<Context>& context) : m_context(context), m_snakeDirection(16.f, 0.f), 
                                                         m_elapsedTime(sf::Time::Zero),m_score(0),m_isPaused(false)
{
	srand(time(nullptr));
}
GamePlay::~GamePlay()
{

}

void GamePlay::Init()
{
	m_context->m_asset->AddTexture(GRASS, "grass.png",true);
	m_context->m_asset->AddTexture(FOOD, "food.png");
	m_context->m_asset->AddTexture(WALL, "wall.png",true);
	m_context->m_asset->AddTexture(SNAKE, "snake.png");

	m_context->m_asset->AddFont(MAIN_FONT, "DynaPuff-Regular.ttf");

	m_grass = std::make_unique<sf::Sprite>(m_context->m_asset->GetTexture(GRASS));
	m_grass->setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));

	sf::Vector2u windowSize = m_context->m_window->getSize();
	for (auto& wall: m_walls)
	{
		wall= std::make_unique<sf::Sprite>(m_context->m_asset->GetTexture(WALL));
	}
	m_walls[0]->setTextureRect({{0,0},{static_cast<int>(windowSize.x),16}}); // Top wall

	m_walls[1]->setTextureRect({ {0,0},{static_cast<int>(windowSize.x),16} }); // Bottom wall
	m_walls[1]->setPosition(sf::Vector2f(0, static_cast<int>(windowSize.y)-16));

	m_walls[2]->setTextureRect({ {0,0},{16,static_cast<int>(windowSize.y)} }); // Left wall

	m_walls[3]->setTextureRect({ {0,0},{16,static_cast<int>(windowSize.y)} }); // Right wall
	m_walls[3]->setPosition(sf::Vector2f(static_cast<int>(windowSize.x) - 16 ,0));

	m_food = std::make_unique<sf::Sprite>(m_context->m_asset->GetTexture(FOOD));
	m_food->setPosition(sf::Vector2f(windowSize.x/2, windowSize.y/2));

	m_snake.Init(m_context->m_asset->GetTexture(SNAKE));

	m_scoreText = std::make_unique<sf::Text>(m_context->m_asset->GetFont(MAIN_FONT), "Score: "+std::to_string(m_score), 16);
	m_scoreText->setPosition(sf::Vector2f(0, 0));


}
void GamePlay::ProcessInput()
{
	while (const std::optional event = m_context->m_window->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			m_context->m_window->close();
		else if (event->is<sf::Event::KeyPressed>())
			if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {

				sf::Vector2f newDirection = m_snakeDirection;

				switch (static_cast<sf::Keyboard::Key>(keyEvent->code)) {
				case sf::Keyboard::Key::Up:
				{
					newDirection = sf::Vector2f(0.f, -16.f);
					break;
				}

				case sf::Keyboard::Key::Down:
				{
					newDirection = sf::Vector2f(0.f, 16.f);
					break;
				}

				case sf::Keyboard::Key::Left:
				{
					newDirection = sf::Vector2f(-16.f, 0.f);
					break;
				}
				case sf::Keyboard::Key::Right:
				{
					newDirection = sf::Vector2f(16.f, 0.f);
					break;
				}
				case sf::Keyboard::Key::W:
				{
					newDirection = sf::Vector2f(0.f, -16.f);
					break;
				}

				case sf::Keyboard::Key::S:
				{
					newDirection = sf::Vector2f(0.f, 16.f);
					break;
				}

				case sf::Keyboard::Key::A:
				{
					newDirection = sf::Vector2f(-16.f, 0.f);
					break;
				}
				case sf::Keyboard::Key::D:
				{
					newDirection = sf::Vector2f(16.f, 0.f);
					break;
				}
				case sf::Keyboard::Key::Escape:
				{
					m_context->m_state->Add(std::make_unique<PauseGame>(m_context));
					break;
				}
				default:
					break;
				}
				if (std::abs(m_snakeDirection.x) != std::abs(newDirection.x) || std::abs(m_snakeDirection.y) != std::abs(newDirection.y))
				{
					m_snakeDirection = newDirection;
				}
			}
	}

}
void GamePlay::Update(sf::Time deltaTime)
{ 
	if (!m_isPaused)
	{

	m_elapsedTime += deltaTime;
	if (m_elapsedTime.asSeconds()> 30.f)
	{
		bool isOnWall = false;
		for(auto & wall : m_walls)
		{
			if(m_snake.IsOn(*wall))
			{   
				isOnWall = true;
				m_context->m_state->Add(std::make_unique<GameOver>(m_context),isOnWall);
				break;
			}
		}
		if(m_snake.IsOn(*m_food))
		{
			m_snake.Grow(m_snakeDirection);

			int x = 0;
			int y = 0;

			x = rand() % (m_context->m_window->getSize().x);
			y = rand() % (m_context->m_window->getSize().y);

			x = std::clamp<int>(x, 16, m_context->m_window->getSize().x - 32);
			y = std::clamp<int>(y, 16, m_context->m_window->getSize().y - 32);

			m_food->setPosition(sf::Vector2f(x - x % 16, y - y % 16));

			m_score += 1;
			m_scoreText->setString("Score: " + std::to_string(m_score));
		}
		else if (m_snake.isFoodSnakeIntersecting(*m_food))
		{
			int x = 0;
			int y = 0;

			x = rand() % (m_context->m_window->getSize().x);
			y = rand() % (m_context->m_window->getSize().y);

			x = std::clamp<int>(x, 16, m_context->m_window->getSize().x - 32);
			y = std::clamp<int>(y, 16, m_context->m_window->getSize().y - 32);

			m_food->setPosition(sf::Vector2f(x - x % 16, y - y % 16));
		}
		else
		{
            m_snake.Move(m_snakeDirection);
		}
		m_elapsedTime = sf::Time::Zero;
	}
	if(m_snake.isSelfIntersecting())
	{
		m_context->m_state->Add(std::make_unique<GameOver>(m_context),true);
	}

	}
}


void GamePlay::Draw()
{
	m_context->m_window->clear();
	m_context->m_window->draw(*m_grass);
	m_context->m_window->draw(*m_food);
	for (auto& wall : m_walls)
	{
		m_context->m_window->draw(*wall);
	}
	m_context->m_window->draw(m_snake);
	m_context->m_window->draw(*m_scoreText);
	m_context->m_window->display();
	
}
void GamePlay::Pause()
{
	m_isPaused = true;
}
void GamePlay::Start()
{
	m_isPaused = false;
}
