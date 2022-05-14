#include <iostream>

#include "GameWorld.hpp"
#include "Entities/Player.hpp"
#include "Entity.hpp"
#include "Engine.hpp"
#include "AnimatedEntity.hpp"
#include "Events.hpp"
#include "UIElement.hpp"

GameWorld::GameWorld(sf::RenderWindow& _window) : window(_window) {
	backgroundTex.loadFromFile("assets/textures/environment/background.png");
	groundHeight = 500;
	mouseVisible = false;
	mouseGrabbed = true;
	window.setMouseCursorVisible(false);
	window.setMouseCursorGrabbed(true);
	Events::HookTo("EscPressed", [this]()->void {
		window.setMouseCursorVisible(!mouseVisible);
		mouseVisible = !mouseVisible; 
		window.setMouseCursorGrabbed(!mouseGrabbed);
		mouseGrabbed = !mouseGrabbed;
	});
}

GameWorld::Room GameWorld::GenerateRoom() {
	Room room;
	room.biome = Biome(Tools::RandomInt(0, biomeMAX));
	room.length = Tools::RandomInt(5, 10);
	room.type = RoomType(Tools::RandomInt(0, roomTypeMAX));
	room.enemyCount = Tools::RandomInt(room.length, room.length * 5);
	return room;
}

void GameWorld::WorldPhysics() {
	std::list<Entity*>::iterator it;
	for (it = entities.begin(); it != entities.end(); it++) {
		if ((*it)->jumping) continue;
		if ((*it)->getY() >= groundHeight) {
			(*it)->inAir = false;
			continue;
		}
		else (*it)->inAir = true;
		Engine::ApplyGravity(*it);
	}
}

void GameWorld::Render() {
	sf::Sprite worldBackground;
	worldBackground.setTexture(backgroundTex);
	window.draw(worldBackground);
	window.draw(worldBackground);

	RenderEntities();
	RenderUI();
	if (purgeEntities.size()) PurgeEntities();
}

void GameWorld::RenderEntities() {
	std::list<Entity*>::iterator it;
	for (it = entities.begin(); it != entities.end(); it++) {
		(*it)->Update();
		(*it)->DrawTo(window);
	}
}

void GameWorld::RenderUI() {
	std::vector<UIElement*>::iterator vIt;
	for (vIt = uiElements.begin(); vIt != uiElements.end(); vIt++) {
		(*vIt)->Update();
		(*vIt)->DrawTo(window);
	}
}

void GameWorld::PurgeEntities() {
	std::vector<Entity*>::iterator vIt = purgeEntities.begin();
	while (vIt != purgeEntities.end()) {

		entities.remove(*vIt);
		vIt = purgeEntities.erase(vIt);
	}
}

void GameWorld::AddEntity(Entity *entity) {
	entities.push_back(entity);
}

void GameWorld::RemoveEntity(Entity* entity) {
	purgeEntities.push_back(entity);
}

void GameWorld::AddUIElement(UIElement* element) {
	uiElements.push_back(element);
}

void GameWorld::RemoveUIElement(UIElement* element) {

}

void GameWorld::setMouseVisible(bool visible) { mouseVisible = visible; }