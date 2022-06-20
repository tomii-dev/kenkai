#include <iostream>
#include <vector>

#include "Setup.hpp"
#include "Game.hpp"
#include "GameWorld.hpp"
#include "Control.hpp"
#include "Properties.hpp"
#include "Tools.hpp"
#include "Events.hpp"
#include "Entity.hpp"
#include "Entities/Player.hpp"
#include "Entities/Enemy.hpp"
#include "AnimatedEntity.hpp"
#include "UIElements/Cursor.hpp"
#include "Menu.hpp"
#include "SFML/Graphics.hpp"
#include "Assets.hpp"

using namespace Control;

Setup setup;
Game *Game::s_instance = nullptr;

Game::Game()
	: m_ready		(false),
	  m_frame		(0),
	  m_totalFrame	(0),
	  m_window		(sf::VideoMode(800, 600), "kenkai", sf::Style::Close),
	  m_world		(GameWorld(m_window)),
	  m_camera		(m_window, DEFAULT_MODE),
	  player		(nullptr),
	  m_cursor		(15, 15),
	  m_currentMenu	(nullptr)
{
	s_instance = this;
}

void Game::ChangeMenu(Menu *menu){
	delete m_currentMenu;
	m_currentMenu = menu;
}

Game &Game::getInstance(){
	return *s_instance;
}

void Game::RunGame(){
	m_window.setFramerateLimit(144);

	sf::Event e;

	player = new Player(Tools::PlayerConfig("balls"));
	m_world.AddEntity(player);
	m_world.AddUIElement(&m_cursor);

	sf::VideoMode res = sf::VideoMode::getDesktopMode();
	sf::Vector2u windowRes = sf::Vector2u(res.width / 2.4, res.height / 1.8);

	m_window.setSize(windowRes);
	Properties::screenCenter = sf::Vector2f(windowRes / 2u);

	m_state = MENU;
	m_currentMenu = new Menu(&m_window, MenuId::Main);

	m_ready = true;
	Events::Fire(GameReady);

	// main loop
	while (m_window.isOpen()){
		while (m_window.pollEvent(e)){
			switch (e.type){
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::KeyPressed:
				HandleControl(e.key.code, true);
				break;
			case sf::Event::KeyReleased:
				HandleControl(e.key.code, false);
				break;
			case sf::Event::MouseButtonPressed:
				if (e.mouseButton.button == sf::Mouse::Left)
					Events::Fire(MousePressed);
				break;
			case sf::Event::MouseMoved:
				Events::Fire(MouseMoved);
				break;
			}
		}
		m_window.clear(sf::Color::Blue);
		switch (m_state){
		case MENU:
			m_currentMenu->Render();
			break;
		case PLAYING:
			m_world.WorldPhysics();
			Tools::LogicUpdate();
			m_world.Render();
			m_camera.Update(player->getPosition(), sf::Vector2f(0, -200), player->moveSpeed);
			++m_frame;
			++m_totalFrame;
			if (m_frame == Properties::frameRate - 1)
				m_frame = 0;
			break;
		}
		m_window.display();
	}
}

GameState Game::getState(){
	return m_state;
}

void Game::setState(GameState state){
	m_state = state;
}

sf::RenderWindow &Game::getWindow(){
	return m_window;
}

int Game::getFrame(){
	return m_frame;
}

int Game::getTotalFrame(){
	return m_totalFrame;
}

bool Game::isReady(){
	return m_ready;
}