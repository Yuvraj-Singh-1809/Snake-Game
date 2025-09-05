#include "GameOver.hpp"
#include "GamePlay.hpp"

GameOver::GameOver(std::shared_ptr<Context>& context) : m_context(context),
m_isRetryButtonSelected(true), m_isRetryButtonPressed(false),
m_isExitButtonPressed(false), m_isExitButtonSelected(false)
{
}
GameOver::~GameOver()
{
}

void GameOver::Init()
{

	//Title
	m_gameOverTitle = std::make_unique<sf::Text>(m_context->m_asset->GetFont(MAIN_FONT), "Game Over", 30);
	/*m_gameTitle->setString("MC Tattu");*/

	sf::FloatRect bounds = m_gameOverTitle->getLocalBounds();
	// Set origin to center of the text
	m_gameOverTitle->setOrigin(
		sf::Vector2f(bounds.position.x + bounds.size.x / 2.0f,
			bounds.position.y + bounds.size.y / 2.0f)
	);
	sf::Vector2u windowSize = m_context->m_window->getSize();
	m_gameOverTitle->setPosition(sf::Vector2f(windowSize.x / 2.0, windowSize.y / 2.0 - 150));
	// Retry Button
	m_retryButton = std::make_unique<sf::Text>(m_context->m_asset->GetFont(MAIN_FONT), "Retry", 30);
	sf::FloatRect retryBounds = m_retryButton->getLocalBounds();
	m_retryButton->setOrigin(
		sf::Vector2f(retryBounds.position.x + retryBounds.size.x / 2.0f,
			retryBounds.position.y + retryBounds.size.y / 2.0f)
	);
	m_retryButton->setPosition(sf::Vector2f(windowSize.x / 2.0, windowSize.y / 2.0 - 30));
	// Exit Button
	m_exitButton = std::make_unique<sf::Text>(m_context->m_asset->GetFont(MAIN_FONT), "Exit", 30);
	sf::FloatRect exitBounds = m_exitButton->getLocalBounds();
	m_exitButton->setOrigin(
		sf::Vector2f(exitBounds.position.x + exitBounds.size.x / 2.0f,
			exitBounds.position.y + exitBounds.size.y / 2.0f)
	);
	m_exitButton->setPosition(sf::Vector2f(windowSize.x / 2.0, windowSize.y / 2.0 + 30));

}

void GameOver::ProcessInput()
{
	while (const std::optional event = m_context->m_window->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			m_context->m_window->close();

		else if (event->is<sf::Event::KeyPressed>())
			if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
				switch (static_cast<sf::Keyboard::Key>(keyEvent->code)) {
				case sf::Keyboard::Key::Up:
				{
					if (!m_isRetryButtonSelected)
					{
						m_isRetryButtonSelected = true;
						m_isExitButtonSelected = false;
					}
					break;
				}

				case sf::Keyboard::Key::Down:
				{
					if (!m_isExitButtonSelected)
					{
						m_isRetryButtonSelected = false;
						m_isExitButtonSelected = true;
					}
					break;
				}

				case sf::Keyboard::Key::Enter:
				{
					m_isRetryButtonPressed = false;
					m_isExitButtonPressed = false;
					if (m_isRetryButtonSelected)
					{
						m_isRetryButtonPressed = true;
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
void GameOver::Update(sf::Time deltaTime)
{
	if (m_isRetryButtonSelected)
	{
		m_retryButton->setFillColor(sf::Color(176, 236, 172));
		m_exitButton->setFillColor(sf::Color::White);
	}
	else
	{
		m_exitButton->setFillColor(sf::Color(176, 236, 172));
		m_retryButton->setFillColor(sf::Color::White);
	}
	if (m_isRetryButtonPressed)
	{
		m_context->m_state->Add(std::make_unique<GamePlay>(m_context), true);
		/*m_isPlayButtonPressed = false;*/
	}
	else if (m_isExitButtonPressed)
	{
		m_context->m_window->close();
	}
}
void GameOver::Draw()
{
	m_context->m_window->clear(sf::Color(0, 158, 164));
	m_context->m_window->draw(*(m_gameOverTitle));
	m_context->m_window->draw(*(m_retryButton));
	m_context->m_window->draw(*(m_exitButton));
	m_context->m_window->display();
}