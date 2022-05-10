#pragma once

#include "SFML/Graphics.hpp"
#include <list>
#include <vector>
#include "Camera.hpp"

class Entity;
class UIElement;

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
public:
	GameWorld(sf::RenderWindow& _window);
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