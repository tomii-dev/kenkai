#pragma once

#include "GameWorld.hpp"
#include "Entity.hpp"
#include "AnimatedEntity.hpp"
#include "UIElements/Cursor.hpp"
#include "Camera.hpp"

class Player;

class Game{
	static Game* s_instance;
	bool m_ready;
	int m_frame;
	int m_totalFrame;
	sf::RenderWindow m_window;
	Camera m_camera;
	GameWorld m_world;
	Cursor* m_cursor;
public:
	Game();
	static Game& getInstance();
	void RunGame();
	sf::RenderWindow& getWindow();
	int getFrame();
	int getTotalFrame();
	bool isReady();
	Player* player;
};
