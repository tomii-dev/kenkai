#include <iostream>

#include "GameWorld.hpp"
#include "Entities/Player.hpp"
#include "Entity.hpp"
#include "Engine.hpp"
#include "AnimatedEntity.hpp"
#include "Events.hpp"
#include "UIElement.hpp"

GameWorld::GameWorld(sf::RenderWindow& window) : m_window(window) {
	backgroundTex.loadFromFile("assets/textures/environment/background.png");
	groundHeight = 500;
	mouseVisible = false;
	mouseGrabbed = true;
	m_window.setMouseCursorVisible(false);
	m_window.setMouseCursorGrabbed(true);
	Events::HookTo(EscPressed, [this]()->void {
		m_window.setMouseCursorVisible(!mouseVisible);
		mouseVisible = !mouseVisible; 
		m_window.setMouseCursorGrabbed(!mouseGrabbed);
		mouseGrabbed = !mouseGrabbed;
	});
}

GameWorld::Room GameWorld::GenerateRoom(RoomType type=standard) {
	Room room;
	room.biome = Biome(Tools::RandomInt(0, biomeMAX));
	room.length = Tools::RandomInt(5, 10);
	room.type = type;
	room.enemyCount = Tools::RandomInt(room.length, room.length * 5);
	return room;
}

GameWorld::Stage GameWorld::GenerateStage() {
	Stage stage;
	for(int i = 0; i < 4; i++)
		stage.rooms.push_back(GenerateRoom());
	stage.rooms.push_back(GenerateRoom(boss));
	return stage;
}

GameWorld::Sekai GameWorld::GenerateSekai(){
	Sekai sekai;
	for(int i = 0; i < 4; i++)
		sekai.stages.push_back(GenerateStage());
	BossStage bossStage;
	sekai.stages.push_back(bossStage);
	return sekai;
}

void GameWorld::LoadSekai(Sekai& sekai){
	m_currentSekai = sekai;
	m_currentStage = sekai.stages[0];
	m_currentRoom = m_currentStage.rooms[0];
	m_state = RUN;
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
	m_window.draw(worldBackground);
	m_window.draw(worldBackground);

	RenderEntities();
	RenderUI();
	if (purgeEntities.size()) PurgeEntities();
}

void GameWorld::RenderEntities() {
	std::list<Entity*>::iterator it;
	for (it = entities.begin(); it != entities.end(); it++) {
		(*it)->Update();
		(*it)->DrawTo(m_window);
	}
}

void GameWorld::RenderUI() {
	std::vector<UIElement*>::iterator vIt;
	for (vIt = uiElements.begin(); vIt != uiElements.end(); vIt++) {
		(*vIt)->Update();
		(*vIt)->DrawTo(&m_window);
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