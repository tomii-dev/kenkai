#pragma once

#include "GameWorld.hpp"
#include "Entity.hpp"
#include "AnimatedEntity.hpp"
#include "UIElements/Cursor.hpp"
#include "Camera.hpp"
#include "Menu.hpp"

class Player;

enum GameState { MENU, PLAYING };

class Game{
	static Game* s_instance;
	bool m_ready;
	int m_frame;
	int m_totalFrame;
	GameState m_state;
	sf::RenderWindow m_window;
	Camera m_camera;
	GameWorld m_world;
	Cursor m_cursor;
	Menu* m_currentMenu;
public:
	Game();
	static Game& getInstance();
	void RunGame();
	sf::RenderWindow& getWindow();
	int getFrame();
	int getTotalFrame();
	GameState getState();
	void setState(GameState state);
	void ChangeMenu(Menu* menu);
	bool isReady();
	Player* player;
};
