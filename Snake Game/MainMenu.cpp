#include "MainMenu.hpp"
#include "GamePlay.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp> 
#include <SFML/Window/Keyboard.hpp>


MainMenu::MainMenu(std::shared_ptr<Context>& context) : m_context(context), 
m_isPlayButtonSelected(true), m_isPlayButtonPressed(false),
m_isExitButtonPressed(false), m_isExitButtonSelected(false)
{
}
MainMenu::~MainMenu()
{
}
void MainMenu::Init()
{
	m_context->m_asset->AddFont(MAIN_FONT, "DynaPuff-Regular.ttf");
	//Title

	m_gameTitle=std::make_unique<sf::Text>(m_context->m_asset->GetFont(MAIN_FONT),"Snake Game",30);
	/*m_gameTitle->setString("MC Tattu");*/


	sf::FloatRect bounds = m_gameTitle->getLocalBounds();

	// Set origin to center of the text
	m_gameTitle->setOrigin(
		sf::Vector2f(bounds.position.x + bounds.size.x / 2.0f,
			bounds.position.y + bounds.size.y / 2.0f)
	);

	sf::Vector2u windowSize = m_context->m_window->getSize();
	m_gameTitle->setPosition(sf::Vector2f(windowSize.x / 2.0, windowSize.y / 2.0 - 150));

	// Play Button
	m_playButton = std::make_unique<sf::Text>(m_context->m_asset->GetFont(MAIN_FONT), "Play", 30);
	
	sf::FloatRect playBounds = m_playButton->getLocalBounds();

	m_playButton->setOrigin(
		sf::Vector2f(playBounds.position.x + playBounds.size.x / 2.0f,
			playBounds.position.y + playBounds.size.y / 2.0f)
	);


	m_playButton->setPosition(sf::Vector2f(windowSize.x / 2.0, windowSize.y / 2.0-30));

	//Exit Button
	m_exitButton = std::make_unique<sf::Text>(m_context->m_asset->GetFont(MAIN_FONT), "Exit", 30);
	
	sf::FloatRect exitBounds = m_exitButton->getLocalBounds();

	m_exitButton->setOrigin(
		sf::Vector2f(exitBounds.position.x + exitBounds.size.x / 2.0f,
			exitBounds.position.y + exitBounds.size.y / 2.0f)
	);

	m_exitButton->setPosition(sf::Vector2f(windowSize.x / 2.0, windowSize.y / 2.0+30));


}
void MainMenu::ProcessInput()
{
	while (const std::optional event = m_context->m_window->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			m_context->m_window->close();

		else if(event->is<sf::Event::KeyPressed>())
			if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
				switch (static_cast<sf::Keyboard::Key>(keyEvent->code)) {
				case sf::Keyboard::Key::Up:
				{
					if (!m_isPlayButtonSelected)
					{
						m_isPlayButtonSelected = true;
						m_isExitButtonSelected = false;
				}
					break;
				}
					
				case sf::Keyboard::Key::Down:
				{
					if (!m_isExitButtonSelected)
					{
						m_isPlayButtonSelected = false;
						m_isExitButtonSelected = true;
					}
					break;
				}

				case sf::Keyboard::Key::W:
				{
					if (!m_isPlayButtonSelected)
					{
						m_isPlayButtonSelected = true;
						m_isExitButtonSelected = false;
					}
					break;
				}

				case sf::Keyboard::Key::S:
				{
					if (!m_isExitButtonSelected)
					{
						m_isPlayButtonSelected = false;
						m_isExitButtonSelected = true;
					}
					break;
				}

				case sf::Keyboard::Key::Enter:
				{
					m_isPlayButtonPressed = false;
					m_isExitButtonPressed = false;
					if (m_isPlayButtonSelected)
					{
						m_isPlayButtonPressed = true;
					}
					else
					{
						m_isExitButtonPressed = true;
					}
					break;
				}

				default:
					break;
				}
		}
	}
}
void MainMenu::Update(sf::Time deltaTime)
{
	if (m_isPlayButtonSelected)
	{
		m_playButton->setFillColor(sf::Color(176,236,172));
		m_exitButton->setFillColor(sf::Color::White);
	}
	else
	{
		m_exitButton->setFillColor(sf::Color(176, 236, 172));
		m_playButton->setFillColor(sf::Color::White);
	}
	if (m_isPlayButtonPressed)
	{
		m_context->m_state->Add(std::make_unique<GamePlay>(m_context), true);
		/*m_isPlayButtonPressed = false;*/
	}
	else if (m_isExitButtonPressed)
	{
		m_context->m_window->close();
	}
}
void MainMenu::Draw()
{
	m_context->m_window->clear(sf::Color(0,158,164));
	m_context->m_window->draw(*(m_gameTitle));
	m_context->m_window->draw(*(m_playButton));
	m_context->m_window->draw(*(m_exitButton));
	m_context->m_window->display();
}