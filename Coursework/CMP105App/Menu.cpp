#include "Menu.h"

Menu::Menu(sf::RenderWindow& hwnd, Input& in, GameState& gs, AudioManager& aud) :
	Scene(hwnd, in, gs, aud), m_playButtonLabel(m_font), m_playButton2Label(m_font), m_playJungleButtonLabel(m_font), m_playJungle2ButtonLabel(m_font)
{
	
	if (!m_font.openFromFile("font/bitcount.ttf"))
		std::cerr << "failed to load bitcount font";

	// Button size - smaller to fit 4 in the window
	sf::Vector2f btnSize = { 216, 76 };
	sf::Color black = sf::Color::Black;

	// Level 1
	m_playButtonLabel.setCharacterSize(20);
	m_playButtonLabel.setPosition({ 172, 18 });
	m_playButtonLabel.setString("Level 1");
	m_playButtonLabel.setFillColor(black);
	m_playButton.setSize(btnSize);
	m_playButton.setPosition({ 108, 8 });
	m_playButton.setCollisionBox({ {0,0}, btnSize });
	m_playButton.setFillColor(m_defaultButtonColour);

	// Level 2
	m_playButton2Label.setCharacterSize(20);
	m_playButton2Label.setPosition({ 172, 112 });
	m_playButton2Label.setString("Level 2");
	m_playButton2Label.setFillColor(black);
	m_play2Button.setSize(btnSize);
	m_play2Button.setPosition({ 108, 102 });
	m_play2Button.setCollisionBox({ {0,0}, btnSize });
	m_play2Button.setFillColor(m_defaultButtonColour);

	// Jungle Level 1
	m_playJungleButtonLabel.setCharacterSize(20);
	m_playJungleButtonLabel.setPosition({ 148, 206 });
	m_playJungleButtonLabel.setString("Jungle Level 1");
	m_playJungleButtonLabel.setFillColor(black);
	m_playJungleButton.setSize(btnSize);
	m_playJungleButton.setPosition({ 108, 196 });
	m_playJungleButton.setCollisionBox({ {0,0}, btnSize });
	m_playJungleButton.setFillColor(m_defaultButtonColour);

	// Jungle Level 2
	m_playJungle2ButtonLabel.setCharacterSize(20);
	m_playJungle2ButtonLabel.setPosition({ 148, 300 });
	m_playJungle2ButtonLabel.setString("Jungle Level 2");
	m_playJungle2ButtonLabel.setFillColor(black);
	m_playJungle2Button.setSize(btnSize);
	m_playJungle2Button.setPosition({ 108, 290 });
	m_playJungle2Button.setCollisionBox({ {0,0}, btnSize });
	m_playJungle2Button.setFillColor(m_defaultButtonColour);

	if (!m_titleSplash.loadFromFile("gfx/title_splash.png")) std::cerr << "no splash found";
	m_titleImage.setTexture(&m_titleSplash);
	m_titleImage.setSize({ 432,432 });
}

void Menu::handleInput(float dt)
{
	sf::Vector2i mousePos{ m_input.getMouseX(), m_input.getMouseY()};
	if(m_input.isLeftMousePressed() && 
		Collision::checkBoundingBox(m_playButton, mousePos))
	{
		m_gameState.setCurrentState(State::LEVELONE);
	}
	if (m_input.isLeftMousePressed() &&
		Collision::checkBoundingBox(m_play2Button, mousePos))
	{
		m_gameState.setCurrentState(State::LEVELTWO);
	}
	if (m_input.isLeftMousePressed() &&
		Collision::checkBoundingBox(m_playJungleButton, mousePos))
	{
		m_gameState.setCurrentState(State::JUNGLEONE);
	}
	if (m_input.isLeftMousePressed() &&
		Collision::checkBoundingBox(m_playJungle2Button, mousePos))
	{
		m_gameState.setCurrentState(State::JUNGLETWO);
	}
}

void Menu::render()
{
	beginDraw();
	m_window.draw(m_titleImage);
	m_window.draw(m_playButton);
	m_window.draw(m_playButtonLabel);
	m_window.draw(m_play2Button);
	m_window.draw(m_playButton2Label);
	m_window.draw(m_playJungleButton);
	m_window.draw(m_playJungleButtonLabel);
	m_window.draw(m_playJungle2Button);
	m_window.draw(m_playJungle2ButtonLabel);
	endDraw();
}

void Menu::update(float dt)
{
	sf::Vector2i mousePos{ m_input.getMouseX(), m_input.getMouseY() };
	if (Collision::checkBoundingBox(m_playButton, mousePos))
	{
		m_playButton.setFillColor(m_hoverButtonColour);
	}
	else
	{
		m_playButton.setFillColor(m_defaultButtonColour);
	}
	if (Collision::checkBoundingBox(m_play2Button, mousePos))
	{
		m_play2Button.setFillColor(m_hoverButtonColour);

	}
	else
	{
		m_play2Button.setFillColor(m_defaultButtonColour);

	}
	if (Collision::checkBoundingBox(m_playJungleButton, mousePos))
		m_playJungleButton.setFillColor(m_hoverButtonColour);
	else
		m_playJungleButton.setFillColor(m_defaultButtonColour);

	if (Collision::checkBoundingBox(m_playJungle2Button, mousePos))
		m_playJungle2Button.setFillColor(m_hoverButtonColour);
	else
		m_playJungle2Button.setFillColor(m_defaultButtonColour);
}


void Menu::onBegin()
{
	std::cout << "starting menu\n";
	auto view = m_window.getDefaultView();
	view.setCenter({ 216, 216 });
	m_window.setView(view);
	m_audio.playMusicbyName("bgm2");
}

void Menu::onEnd()
{
	std::cout << "leaving menu\n";
	m_audio.stopAllMusic();
}