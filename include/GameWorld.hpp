#pragma once

#include "SFML/Graphics.hpp"
#include <list>
#include <vector>
#include "Camera.hpp"

class Entity;
class UIElement;

enum WorldState { HOME, RUN };

class GameWorld {
	sf::RenderWindow& window;
	sf::Texture backgroundTex;
	sf::Texture groundTex;
	sf::Sprite ground;
	std::list<Entity*> entities;
	std::vector<UIElement*> uiElements;
	std::vector<Entity*> purgeEntities;
	float groundHeight;
	bool mouseVisible;
	bool mouseGrabbed;
	enum Biome { plains, desert, dungeon, forest, jungle, theVoid, 
		biomeMAX = theVoid };
	enum RoomType { standard, boss, 
		roomTypeMAX = boss };
	struct Room {
		unsigned int enemyCount;
		unsigned int length;
		Biome biome;
		RoomType type;
		std::string bossId;
	};
	struct Stage {
		unsigned int num;
		std::vector<Room> rooms;
	};
	struct BossStage : Stage{
		
	};
	struct Sekai {
		std::vector<Stage> stages;
	};
	Room m_currentRoom;
	Stage m_currentStage;
	Sekai m_currentSekai;
public:
	GameWorld(sf::RenderWindow& _window);
	Room GenerateRoom(RoomType type);
	Stage GenerateStage();
	Sekai GenerateSekai();
	void WorldPhysics();
	void Render();
	void RenderEntities();
	void RenderUI();
	void PurgeEntities();
	void AddEntity(Entity *entity);
	void RemoveEntity(Entity *entity);
	void AddUIElement(UIElement* element);
	void RemoveUIElement(UIElement* element);
	void setMouseVisible(bool visible);
};